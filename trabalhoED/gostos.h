#ifndef funcionalidades_h
#define funcionalidades_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_AFINIDADES 70

typedef struct VetorGostos VetorGostos;

VetorGostos *  CriaVetorGostos(int tamanho);
VetorGostos * AdicionaGostos(VetorGostos * afinidades, char * elemento);
VetorGostos * LiberaGostos(VetorGostos * afinidades);
void ImprimeGostos(VetorGostos * afinidades, FILE* saida);
#endif