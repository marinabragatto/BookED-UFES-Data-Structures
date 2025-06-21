#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>

typedef struct celula Celula;

struct celula {
    void * elemento;    ///< Ponteiro para o elemento armazenado
    Celula * ant;       ///< Ponteiro para a célula anterior
    Celula * prox;      ///< Ponteiro para a próxima célula
};

typedef struct lista Lista;

Lista * criaLista();

void insereElemNoFimDaLista(Lista * lista, void * elemNovo);

void liberaLista(Lista * lista, void (*libera)(void*));

void liberaListaParcialmente(Lista * lista);

void imprimeLista(Lista * lista, void (*imprime)(void*, FILE*), FILE* saida);

void * retornaElemComMesmoId(Lista* lista, void * chave, int (*compara)(void *, void *));

void retiraElemLista(Lista * lista, void * chave, int (*compara)(void *, void *));

Celula * retornaPrimeiraCelulaLista(Lista * lista);

#endif