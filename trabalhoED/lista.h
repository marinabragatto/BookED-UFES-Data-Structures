#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>

typedef struct lista Lista;

Lista * criaLista();

void insereElemNoFimDaLista(Lista * lista, void * elemNovo);

void liberaLista(Lista * lista, void (*libera)(void*));

void liberaListaParcialmente(Lista * lista);

void imprimeLista(Lista * lista, void (*imprime)(void*, FILE*), FILE* saida);

void * retornaElemComMesmoId(Lista* lista, int id, int (*compara)(void *, int));

#endif