#ifndef funcionalidades_h
#define funcionalidades_h

#define TAM_AFINIDADES 70

typedef struct VetorAfinidades VetorAfinidades;

VetorAfinidades *  CriaVetorAfinidades(int tamanho);
VetorAfinidades * AdicionaElemento(VetorAfinidades * afinidades, char * elemento);
#endif