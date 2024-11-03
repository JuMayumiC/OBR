#include <Arduino.h>
#include "radar.h"
#include <ESP32Servo.h>

int ST;
int SE;
int M;

Servo servo; 

void inicializarRadar(int sensorT, int sensorE, int motor){
  
  pinMode(sensorT, OUTPUT); 
  pinMode(sensorE, INPUT);
  servo.attach(motor);

  ST = sensorT;
  SE = sensorE;
  M = motor;
}
void paraZero(){
  servo.write(90);
}

int analizaDireita(int dist){
  paraZero();
  int distancia;
  int valor = 0;
  for(int i=90;i<=165;i++){
    distancia = getDistancia();
    if(distancia < dist){
      valor = i;
      paraZero();
      break;
    }
  } 
  return valor;
}
int analizaEsquerda(int dist){
  paraZero();
  int distancia;
  int valor = 0;
  for(int i=90;i<=15;i--){
    distancia = getDistancia();
    if(distancia < dist){
      valor = i;
      paraZero();
      break;
    }
  }
  return valor;
}

int getDistancia(){
  int tempo;
  int distancia;

  digitalWrite(ST, LOW); 
  delayMicroseconds(2);
  digitalWrite(ST, HIGH); 
  delayMicroseconds(10);
  digitalWrite(ST, LOW);
  tempo = pulseIn(SE, HIGH); 
  distancia= tempo*0.034/2;
  return distancia;
}