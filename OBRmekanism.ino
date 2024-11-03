#include movimento.h
#include cor.h
#include radar.h
#include <Arduino.h>

//motores
#define motor1 6
#define motor2 10
#define motor1_inverso 5
#define motor2_inverso 9
#define motor3 3
#define motor4 11
#define motor3_inverso 2
#define motor4_inverso 12

//sensores de linha
#define sensorlinha1 7
#define sensorlinhaanalogico1 A0
#define sensorlinha2 8
#define sensorlinhaanalogico2 A1
#define sensorlinha3 4
#define sensorlinhaanalogico3 A2
#define sensorlinha4 13
#define sensorlinhaanalogico4 A3

//sensores de cor
#define sensorrgb 20
#define sensorrgb2 21
#define sensorrgb3 22

//ultrassonicos
#define ultrassonicotrig 1
#define ultrassonicoecho 23
#define ultrassonicotrig2 0
#define ultrassonicoecho2 24
#define ultrassonicotrig3 15
#define ultrassonicoecho3 25

//servos
#define motorservo 14
#define motorservo2 16
#define motorservo3 17
#define motorservo4 18
#define motorservo5 19

void setup() {
  // Inicializa a comunicação serial 
  Serial.begin(9600);
  
  // Motores
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor1_inverso, OUTPUT);
  pinMode(motor2_inverso, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  pinMode(motor3_inverso, OUTPUT);
  pinMode(motor4_inverso, OUTPUT);
  
  // Sensores de linha
  pinMode(sensorlinha1, INPUT);
  pinMode(sensorlinhaanalogico1, INPUT);
  pinMode(sensorlinha2, INPUT);
  pinMode(sensorlinhaanalogico2, INPUT);
  pinMode(sensorlinha3, INPUT);
  pinMode(sensorlinhaanalogico3, INPUT);
  pinMode(sensorlinha4, INPUT);
  pinMode(sensorlinhaanalogico4, INPUT);
  
  // Sensores de cor
  pinMode(sensorrgb, INPUT);
  pinMode(sensorrgb2, INPUT);
  pinMode(sensorrgb3, INPUT);
  
  // Sensores ultrassônicos
  pinMode(ultrassonicotrig, OUTPUT);  // deve ser OUTPUT para o trigger
  pinMode(ultrassonicoecho, INPUT);
  pinMode(ultrassonicotrig2, OUTPUT); // deve ser OUTPUT para o trigger
  pinMode(ultrassonicoecho2, INPUT);
  pinMode(ultrassonicotrig3, OUTPUT); // deve ser OUTPUT para o trigger
  pinMode(ultrassonicoecho3, INPUT);
  
  // Servos
  pinMode(motorservo, OUTPUT);
  pinMode(motorservo2, OUTPUT);
  pinMode(motorservo3, OUTPUT);
  pinMode(motorservo4, OUTPUT);
  pinMode(motorservo5, OUTPUT);

  // Inicializa os sensores de radar (substitua os parâmetros pelos valores corretos)
  inicializarRadar(ultrassonicotrig, ultrassonicoecho, motor1); // Exemplo de parâmetros
}


void loop() {
  seguelinha();
  verificaVerde();
  verificaObstaculo();
  verificaEntradaResgate();
  verificaVermelho();
}

void seguelinha() {
  // Linha centralizada, segue em frente
  if (digitalRead(sensorlinha1) == 0 && digitalRead(sensorlinha2) == 1 && digitalRead(sensorlinha3) == 1 && digitalRead(sensorlinha4) == 0) {
    frente();
  } 
  // Ajuste para a esquerda (linha detectada nos sensores 1 e 2)
  else if (digitalRead(sensorlinha1) == 1 && digitalRead(sensorlinha2) == 1 && digitalRead(sensorlinha3) == 0 && digitalRead(sensorlinha4) == 0) {
    esquerda();
  } 
  // Ajuste para a direita (linha detectada nos sensores 3 e 4)
  else if (digitalRead(sensorlinha1) == 0 && digitalRead(sensorlinha2) == 0 && digitalRead(sensorlinha3) == 1 && digitalRead(sensorlinha4) == 1) {
    direita();
  }
  // Curva acentuada para a esquerda (apenas sensor 1 detecta a linha)
  else if (digitalRead(sensorlinha1) == 1 && digitalRead(sensorlinha2) == 0 && digitalRead(sensorlinha3) == 0 && digitalRead(sensorlinha4) == 0) {
    B_esquerda();
  }
  // Curva acentuada para a direita (apenas sensor 4 detecta a linha)
  else if (digitalRead(sensorlinha1) == 0 && digitalRead(sensorlinha2) == 0 && digitalRead(sensorlinha3) == 0 && digitalRead(sensorlinha4) == 1) {
    B_direita();
  }
  // Nenhum sensor detecta a linha, segue a vida do robô que pode ser gap 
  else (digitalRead(sensorlinha1) == 0 && digitalRead(sensorlinha2) == 0 && digitalRead(sensorlinha3) == 0 && digitalRead(sensorlinha4) == 0) {
    frente();
  } 
  delay(100); // Pequeno delay para evitar oscilações
}

void verificaVerde() {
  // Define o limite de detecção de verde
  const uint16_t LIMITE_VERDE = 200; // Ajuste conforme necessário
  
  // Verifica a presença de marcações verdes nos sensores
  bool verdeNoSensor1 = detectaVerde1();
  bool verdeNoSensor2 = detectaVerde2();

  // Condições para interseções com e sem marcação, ou beco sem saída
  if (verdeNoSensor1 || verdeNoSensor2) {
    // Realiza um movimento pequeno para frente para verificar a linha
    frente();
    delay(200); // Ajuste o tempo conforme necessário para o movimento pequeno
    // Agora verifica se a linha está sob os sensores
    bool linhaPresente = digitalRead(sensorlinha1) == 0 || 
                         digitalRead(sensorlinha2) == 0 || 
                         digitalRead(sensorlinha3) == 0 || 
                         digitalRead(sensorlinha4) == 0;

    // Se a linha estiver presente, segue conforme o verde detectado
    if (linhaPresente) {
      if (verdeNoSensor1 && verdeNoSensor2) {
        curva180(); // Beco sem saída
      }
      else if (verdeNoSensor1) {
        esquerda();  // Verde detectado apenas no sensor 1
      }
      else if (verdeNoSensor2) {
        direita();  // Verde detectado apenas no sensor 2
      }
    } else {
      // Se a linha não está presente, ignora o verde e continua em frente
      frente();
    }
  } else {
    // Se nenhum verde é detectado, segue em frente
    frente();
  }
}

long distancia() {
  digitalWrite(ultrassonicotrig, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrassonicotrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrassonicotrig, LOW);

  long duracao = pulseIn(ultrassonicoecho, HIGH);
  return duracao * 0.034 / 2; // Converte para cm
}

void verificaObstaculo() {
  long dist = distancia();
  
  if (dist < 20) { // Se um objeto estiver a menos de 20 cm
    desviaObstaculo(); // Chama a função de desvio
  }
}

void desviaObstaculo() {
  // Sequência de manobras de desvio
  frente();  // Avança para frente um pouco
  delay(300); // Ajuste o tempo conforme necessário
  stop(); // Para o robô

  Mec_direita(); // Faz uma curva para a direita
  delay(300); // Duração da curva
  stop(); // Para o robô
  frente();  // Avança para fora do obstáculo
  delay(300); // Continue por um tempo
  stop(); // Para o robô
  Mec_esquerda(); // Volta para a esquerda para retornar à linha
  delay(300); // Ajuste conforme necessário
  stop(); // Para o robô
}

void verificaEntradaResgate() {
  // Lógica para os sensores de linha (detecção de prata)
  bool linhaDetectada = false;
  
  // Verifica todos os quatro sensores de linha
  for (int i = 0; i < 4; i++) {
    int leituraSensor = analogRead(sensorlinhaanalogico1 + i);
    if (leituraSensor > LIMITE_REFLEXAO) { // Substitua LIMITE_REFLEXAO pelo seu valor de limite
      linhaDetectada = true;
      break; // Se qualquer sensor detectar a reflexão, sai do loop
    }
  }

  // Verifica os sensores ultrassônicos laterais
  long distanciaLateral1 = distanciaUltrassonicoLateral1(); // Função para medir distância do lado 1
  long distanciaLateral2 = distanciaUltrassonicoLateral2(); // Função para medir distância do lado 2
  
  // Condição para entrar na sala de resgate
  if (linhaDetectada && (distanciaLateral1 < LIMITE_DISTANCIA && distanciaLateral2 < LIMITE_DISTANCIA)) {
    // Ações para entrar na sala de resgate
    entrarNaSalaDeResgate();
  }
}

long distanciaUltrassonicoLateral1() {
  digitalWrite(ultrassonicotrig2, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrassonicotrig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrassonicotrig2, LOW);

  long duracao = pulseIn(ultrassonicoecho2, HIGH);
  return duracao * 0.034 / 2; // Converte para cm
}

long distanciaUltrassonicoLateral2() {
  digitalWrite(ultrassonicotrig3, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrassonicotrig3, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrassonicotrig3, LOW);

  long duracao = pulseIn(ultrassonicoecho3, HIGH);
  return duracao * 0.034 / 2; // Converte para cm
}

void verificaVermelho() {
  const uint16_t LIMITE_VERMELHO = 200; // Defina um limite adequado para a detecção de vermelho
  
  // Verifica a presença de vermelho nos sensores
  bool vermelhoNoSensor1 = corVermelho1() > LIMITE_VERMELHO;
  bool vermelhoNoSensor2 = corVermelho2() > LIMITE_VERMELHO;

  // Se a cor vermelha for detectada em qualquer sensor
  if (vermelhoNoSensor1 || vermelhoNoSensor2) {
    stop(); // Para todas as atividades do robô
  }
}
