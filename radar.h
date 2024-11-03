#ifndef RADAR
#define RADAR

void inicializarRadar(int sensorT, int sensorE, int motor);
void paraZero();

int analizaDireita(int dist);
int analizaEsquerda(int dist);

int getDistancia();

#endif