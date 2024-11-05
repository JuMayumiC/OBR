#ifndef MOV
#define MOV

void initMotores_F(int DF_F, int DT_F, int EF_F, int ET_F);
void initMotores_T(int DF_T, int DT_T, int EF_T, int ET_T);

void frente();
void tras();
void direita();
void esquerda();

void B_direita();
void B_esquerda();

void Mec_direita();
void Mec_esquerda();

void curva180();
void stop();
#endif