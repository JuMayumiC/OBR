#include <Arduino.h>
#include "cor.h"
#include <Wire.h>
#include <Adafruit_TCS34725.h>

#define multiplex 0x70 

Adafruit_TCS34725 tcs1;
Adafruit_TCS34725 tcs2;

void chenel(uint8_t canal){

  Wire.beginTransmission(multiplex);
  Wire.write(1 << canal); 
  Wire.endTransmission();

}


int confere_cor1(){
  chenel(0);
  if(!tcs1.begin()){
    return 0;
  }
  else{
    return 1;
  }
}


int confere_cor2(){
  chenel(1);
  if(!tcs2.begin()){
    return 0;
  }
  else{
    return 1;
  }
}


uint16_t corVerde1(){
  chenel(0);
  uint16_t r1, g1, b1, c1;
  tcs1.getRawData(&r1, &g1, &b1, &c1);
  return g1;
}

uint16_t corVerde2(){
  chenel(1);
  uint16_t r2, g2, b2, c2;
  tcs1.getRawData(&r2, &g2, &b2, &c2);
  return g2;
}

uint16_t corVermelho1(){
  chenel(0);
  uint16_t r1, g1, b1, c1;
  tcs1.getRawData(&r1, &g1, &b1, &c1);
  return r1;
}

uint16_t corVermelho2(){
  chenel(1);
  uint16_t r2, g2, b2, c2;
  tcs1.getRawData(&r2, &g2, &b2, &c2);
  return r2;
}




