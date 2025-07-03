/**
 * @file recomendacao.h
 * @brief Interface do módulo de recomendacao.
 *
 * Define o tipo abstrato Recomendacao e funções relacionadas à criação,
 * manipulação e liberação de recomendacoes.
 * 
 * @author Marina Bragatto
 * @author Thais Brandão
 * @date 09/06/2025
 */

#ifndef RECOMENDACAO_H
#define RECOMENDACAO_H

#include "lista.h"
#include "livro.h"

typedef struct recomendacao Recomendacao;



/**
 * @brief Cria uma recomendacao.
 *
 * @param livro livro recomendado.
 * @param recomendador id do recomendador. 
 *
 * @return recomendacao inicializada e preenchida. 
 */
Recomendacao * criaRecomendacao(int recomendador, Livro* livro);


/**
 * @brief Compara duas recomendacoes.
 *
 * @param rec recomendacao.
 * @param comp recomendacao a ser comparada. 
 * 
 * @return 1 caso sejam iguais, 0 caso contrario.
 * 
 * @pre leitor != NULL, rec != NULL
 */
int comparaRecomendacao(void* rec, void* comp);



/**
 * @brief Libera uma recomendacao.
 *
 * @param recomendacao recomendacao a ser liberada.
 * 
 * @pre recomendacao != NULL
 * @post recomendacao liberada.
 */
void liberaRec(void* recomendacao);



/**
 * @brief Imprime uma recomendacao.
 *
 * @param recomendacao recomendacao a ser impressa.
 * 
 * @pre recomendacao != NULL
 * @post recomendacao impressa.
 */
void imprimeRecomendacao(Recomendacao* rec, FILE* saida);



/**
 * @brief Faz o casting em uma recomendacao e a retorna.
 *
 * @param rec recomendacao a ser retornada.
 * 
 * @return uma recomendacao.
 * 
 * @pre rec != NULL
 * @post recomendacao retornada.
 */
Recomendacao* retornaRecomendacao(void* rec);

#endif