#include "movimento.h"
#include "cor.h"
//Sensores de linha
#define S1 1
#define S2 2
#define S3 3
#define S4 4

// Motores
//Rotores pra frente
#define DF_F 5
#define DT_F 6
#define EF_F 7
#define ET_F 8

//Rotores para tras
#define DF_T 9
#define DT_T 10
#define EF_T 11
#define ET_T 12

//Variaveis
int leituraS1;
int leituraS2;
int leituraS3;
int leituraS4;


void setup() {
  //Serial
  Serial.beguin(115200);

  //sensores
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);

  initMotores_F(DF_F, DT_F, EF_F, ET_F);
  initMotores_T(DF_T, DT_T, EF_T, ET_T);

  if(confere_cor1() == 1){
    Serial.println("Sensor 1 OK")
  }
  else{
    Serial.println("Sensor 1 com osmar")
  }
  
  
  if(confere_cor2() == 1){
    Serial.println("Sensor 2 OK")
  }
  else{
    Serial.println("Sensor 2 com osmar")
  }
}

void loop() {
  leituraS1 = digitalRead(S1);
  leituraS2 = digitalRead(S2);
  leituraS3 = digitalRead(S3);
  leituraS4 = digitalRead(S4);

  if(leituraS1 == 0 || leituraS2 == 0 || leituraS3 == 0 || leituraS4 == 0){ 
    seguelinha();
  }
  corVerde1();
  corVerde2();
}

void seguelinha(){
  frente();
}

