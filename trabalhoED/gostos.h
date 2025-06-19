#ifndef funcionalidades_h
#define funcionalidades_h

#define TAM_AFINIDADES 70

typedef struct VetorGosto VetorGostos;

VetorGostos *  CriaVetorGostos(int tamanho);
VetorGostos * AdicionaGostos(VetorGostos * afinidades, char * elemento);
VetorGostos * LiberaGostos(VetorGostos * afinidades);
void ImprimeGostos(VetorGostos * afinidades);
#endif