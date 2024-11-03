#include "esp32-hal-gpio.h"
#include "movimento.h"
#include <Arduino.h>

static int DF_F_C;
static int DT_F_C;
static int EF_F_C;
static int ET_F_C;

static int DF_T_C;
static int DT_T_C;
static int EF_T_C;
static int ET_T_C;

void initMotores_F(int DF_F, int DT_F, int EF_F, int ET_F){
  pinMode(DF_F, OUTPUT);
  pinMode(DT_F, OUTPUT);
  pinMode(EF_F, OUTPUT);
  pinMode(ET_F, OUTPUT);

  DF_F_C = DF_F;
  DT_F_C = DT_F;
  EF_F_C = EF_F;
  ET_F_C = ET_F;
}

void initMotores_T(int DF_T, int DT_T, int EF_T, int ET_T){
  pinMode(DF_T, OUTPUT);
  pinMode(DT_T, OUTPUT);
  pinMode(EF_T, OUTPUT);
  pinMode(ET_T, OUTPUT);

  DF_T_C = DF_T;
  DT_T_C = DT_T;
  EF_T_C = EF_T;
  ET_T_C = ET_T;
}

void frente(){
  digitalWrite(DF_F_C, HIGH);
  digitalWrite(DT_F_C, HIGH);
  digitalWrite(EF_F_C, HIGH);
  digitalWrite(ET_F_C, HIGH);

  digitalWrite(DF_T_C, LOW);
  digitalWrite(DT_T_C, LOW);
  digitalWrite(EF_T_C, LOW);
  digitalWrite(ET_T_C, LOW);
}
void tras(){
  digitalWrite(DF_F_C, LOW);
  digitalWrite(DT_F_C, LOW);
  digitalWrite(EF_F_C, LOW);
  digitalWrite(ET_F_C, LOW);

  digitalWrite(DF_T_C, HIGH);
  digitalWrite(DT_T_C, HIGH);
  digitalWrite(EF_T_C, HIGH);
  digitalWrite(ET_T_C, HIGH);

}
void direita(){
  digitalWrite(DF_F_C, LOW);
  digitalWrite(DT_F_C, LOW);
  digitalWrite(EF_F_C, HIGH);
  digitalWrite(ET_F_C, HIGH);

  digitalWrite(DF_T_C, LOW);
  digitalWrite(DT_T_C, LOW);
  digitalWrite(EF_T_C, LOW);
  digitalWrite(ET_T_C, LOW);
}
void esquerda(){
  digitalWrite(DF_F_C, HIGH);
  digitalWrite(DT_F_C, HIGH);
  digitalWrite(EF_F_C, LOW);
  digitalWrite(ET_F_C, LOW);

  digitalWrite(DF_T_C, LOW);
  digitalWrite(DT_T_C, LOW);
  digitalWrite(EF_T_C, LOW);
  digitalWrite(ET_T_C, LOW);

}

void B_direita(){
  digitalWrite(DF_F_C, LOW);
  digitalWrite(DT_F_C, LOW);
  digitalWrite(EF_F_C, HIGH);
  digitalWrite(ET_F_C, HIGH);

  digitalWrite(DF_T_C, HIGH);
  digitalWrite(DT_T_C, HIGH);
  digitalWrite(EF_T_C, LOW);
  digitalWrite(ET_T_C, LOW);

}
void B_esquerda(){
  digitalWrite(DF_F_C, HIGH);
  digitalWrite(DT_F_C, HIGH);
  digitalWrite(EF_F_C, LOW);
  digitalWrite(ET_F_C, LOW);

  digitalWrite(DF_T_C, LOW);
  digitalWrite(DT_T_C, LOW);
  digitalWrite(EF_T_C, HIGH);
  digitalWrite(ET_T_C, HIGH);

}

void Mec_direita(){
  digitalWrite(DF_F_C, LOW);
  digitalWrite(DT_F_C, HIGH);
  digitalWrite(EF_F_C, HIGH);
  digitalWrite(ET_F_C, LOW);

  digitalWrite(DF_T_C, HIGH);
  digitalWrite(DT_T_C, LOW);
  digitalWrite(EF_T_C, LOW);
  digitalWrite(ET_T_C, HIGH);

}

void Mec_esquerda(){
  digitalWrite(DF_F_C, HIGH);
  digitalWrite(DT_F_C, LOW);
  digitalWrite(EF_F_C, LOW);
  digitalWrite(ET_F_C, HIGH);

  digitalWrite(DF_T_C, LOW);
  digitalWrite(DT_T_C, HIGH);
  digitalWrite(EF_T_C, HIGH);
  digitalWrite(ET_T_C, LOW);
}

void stop(){
  digitalWrite(DF_F_C, LOW);
  digitalWrite(DT_F_C, LOW);
  digitalWrite(EF_F_C, LOW);
  digitalWrite(ET_F_C, LOW);

  digitalWrite(DF_T_C, LOW);
  digitalWrite(DT_T_C, LOW);
  digitalWrite(EF_T_C, LOW);
  digitalWrite(ET_T_C, LOW);
}

void curva180() {
  // Um motor para frente e o outro para trás para girar 180 graus
  digitalWrite(DF_F_C, HIGH);  // Motor da frente (direita) gira para frente
  digitalWrite(DT_F_C, LOW);    // Motor da frente (esquerda) para
  digitalWrite(EF_T_C, LOW);    // Motor de trás (direita) para
  digitalWrite(ET_T_C, HIGH);    // Motor de trás (esquerda) gira para trás

  delay(1000); // Tempo para completar a curva (ajuste conforme necessário)

  // Parar todos os motores após a curva
  digitalWrite(DF_F_C, LOW);
  digitalWrite(DT_F_C, LOW);
  digitalWrite(EF_T_C, LOW);
  digitalWrite(ET_T_C, LOW);
}