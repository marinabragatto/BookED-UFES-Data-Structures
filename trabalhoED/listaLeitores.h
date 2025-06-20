/**
 * @file listaLeitores.h
 * @brief Interface do módulo de lista de leitores.
 *
 * Define o tipo abstrato ListaLeitores e as funções para criação,
 * leitura, inserção e liberação de listas de leitores.
 *
 * @author Marina Bragatto
 * @author Thais Brandão
 * @date 08/06/2025
 */

#ifndef listaLeitores_h
#define listaLeitores_h

#include "leitor.h"
#include "livro.h"
#include "gostos.h"

// Tipo opaco ListaLeitores.
typedef struct listaLeitores ListaLeitores;


/**
 * @brief Cria uma nova lista de leitores.
 *
 * A lista é duplamente encadeada com nó sentinela.
 *
 * @return Ponteiro para a lista criada.
 *
 * @pre Nenhuma.
 * @post ListaLeitores inicializada e vazia.
 */
ListaLeitores * criaListaLeitores();


/**
 * @brief Lê os dados do arquivo "leitores.txt" e cria a lista de leitores.
 *
 * Cada linha do arquivo representa um leitor a ser inserido.
 *
 * @return Ponteiro para a lista preenchida.
 *
 * @pre O arquivo "leitores.txt" deve existir no diretório de execução.
 * @post ListaLeitores inicializada e preenchida com os leitores do arquivo.
 */
ListaLeitores * leArquivoLeitores();

/**
 * @brief Insere um leitor no final da lista.
 *
 * @param lista Ponteiro para a lista de leitores.
 * @param leitorNovo Ponteiro para o novo leitor a ser inserido.
 *
 * @pre lista != NULL, leitorNovo != NULL
 * @post leitorNovo inserido ao final da lista.
 */
void insereLeitorNoFimDaLista(ListaLeitores * lista, Leitor * leitorNovo);

/**
 * @brief Libera a memória de uma lista de leitores, incluindo seus elementos.
 *
 * @param lista Ponteiro para a lista a ser liberada.
 *
 * @pre lista != NULL
 * @post Toda a memória da lista e dos leitores é liberada.
 */
void liberaListaLeitores(ListaLeitores * lista);

/**
 * @brief Libera apenas a estrutura da lista, mantendo os leitores.
 *
 * Útil quando os leitores ainda são usados em outro lugar.
 *
 * @param lista Ponteiro para a lista a ser parcialmente liberada.
 *
 * @pre lista != NULL
 * @post A estrutura da lista é liberada, mas os leitores permanecem.
 */
void liberaListaLeitoresParcialmente(ListaLeitores * lista);


/**
 * @brief Imprime os leitores presentes na lista.
 *
 * @param lista Ponteiro para a lista de leitores.
 * @param saida Arquivo de saida onde serao impressas as saidas
 * 
 * @pre lista != NULL
 */
void imprimeLeitoresDaLista(ListaLeitores * lista, FILE* saida);

/**
 * @brief Funcao que navega pela lista de leitores ate encontrar o leitor ao qual o id passado como parametro pertence e retorna sua copia
 * @param leitores Ponteiro para lista de leitores.
 * @param idLeitor inteiro que identifica o id do leitor.
 * 
 * @pre lista de leitores deve existir
 * @post retorna um leitor
 */
Leitor* retornaLeitorComMesmoId(ListaLeitores* leitores, int idLeitor);


#endif