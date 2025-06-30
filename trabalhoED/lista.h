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


/**
 * @brief Cria uma lista e aponta prim e ult para NULL.
 *
 * @return lista vazia.
 * 
 * @post lista deve existir.
 */
Lista * criaLista();


/**
 * @brief Insere um novo elemneto no fim da lista.
 *
 * Cria uma nova celula e a insere na posicao adequada da lista.
 * 
 * @param lista lista que tera o elemento inserido.
 * @param elemNovo elemento a ser inserido.
 * 
 * @pre lista e elemNovo != NULL
 * @post lista deve ser atualizada.
 */
void insereElemNoFimDaLista(Lista * lista, void * elemNovo);


/**
 * @brief Libera toda uma lista.
 * 
 * @param lista lista a ser liberada.
 * @param libera funcao de liberar os elementos da lista void.
 * 
 * @pre funcao de liberar elementos deve ser passada como parametro.
 * @post lista liberada.
 */
void liberaLista(Lista * lista, void (*libera)(void*));


/**
 * @brief Libera lista sem liberar os elemnetos.
 * 
 * @param lista lista a ser liberada.
 * 
 * @pre lista deve existir.
 * @post lista liberada.
 */
void liberaListaParcialmente(Lista * lista);


/**
 * @brief Imprime os elementos de uma lista no arquivo de saida.
 * 
 * @param lista lista a ser impressa.
 * @param imprime funcao de imprimir de cada elemento da lista void.
 * @param saida arquivo de saida.
 * 
 * @pre funcao de imprimir deve ser passada como parametro.
 * @post lista impressa.
 */
void imprimeLista(Lista * lista, void (*imprime)(void*, FILE*), FILE* saida);


/**
 * @brief Percorre uma lista e retorna o elemento com mesmo id que a chave passada por parametro.
 * 
 * @param lista lista a ser percorrida.
 * @param chave elemento a ser comparado.
 * @param compara funcao de comparar de cada elemento da lista void.
 * 
 * @return o elemento de mesmo id, caso seja encontrado, 0 caso contrario.
 * 
 * @pre funcao de comparacao deve ser passada como parametro.
 */
void * retornaElemComMesmoId(Lista* lista, void * chave, int (*compara)(void *, void *));


/**
 * @brief Retira um elemento da lista.
 * 
 * @param lista lista a ser percorrida.
 * @param chave elemento a ser comparado.
 * @param compara funcao de comparar de cada elemento da lista void.
 * 
 * @pre funcao de comparacao deve ser passada como parametro.
 * @post lista atualizada.
 */
void retiraElemLista(Lista * lista, void * chave, int (*compara)(void *, void *));


/**
 * @brief Retorna a primeira celula de uma lista (lista->prim).
 * 
 * @param lista lista que retornara a celula.
 * 
 * @return a primeira celula da lista.
 * 
 * @pre lista != NULL
 * @post celula inicializada ou NULL.
 */
Celula * retornaPrimeiraCelulaLista(Lista * lista);

#endif