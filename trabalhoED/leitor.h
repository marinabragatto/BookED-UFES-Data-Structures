/**
 * @file leitor.h
 * @brief Interface do módulo de leitores.
 *
 * Define o tipo abstrato Leitor e funções relacionadas à criação,
 * manipulação e liberação de leitores.
 *
 * @author Marina Bragatto
 * @author Thais Brandão
 * @date 09/06/2025
 */


#ifndef leitor_h
#define leitor_h

#include "listaLivros.h"
#include "livro.h"
#include "gostos.h"

/// Tipo opaco Leitor.
typedef struct leitor Leitor;

#define TAM_MAX_NOME_LEITOR 200

/**
 * @brief Cria um novo leitor.
 *
 * Aloca e inicializa um novo leitor com o ID e nome fornecidos.
 *
 * @param idleitor ID numérico do leitor.
 * @param nome Nome do leitor.
 * @return Ponteiro para o leitor criado.
 * 
 * @pre idleitor >= 0, nome != NULL
 * @post Leitor criado e inicializado.
 */
Leitor* criaLeitor(int idleitor, char * nome, VetorGostos * VetorAfinidades);  // PASSAR COMO PARAMETRO TAMBEM A LISTA CHAR DE AFINIDADES?

/**
 * @brief Compara o ID fornecido com o ID de um leitor.
 *
 * Verifica se o ID passado corresponde ao ID do leitor fornecido.
 *
 * @param leitor Ponteiro para o leitor.
 * @param id ID a ser comparado.
 * @return 1 se o ID pertencer ao leitor, 0 caso contrário.
 * 
 * @pre leitor != NULL
 * @post Retorna 0 ou 1.
 */
int comparaIdLeitor(Leitor * leitor, int id);

/**
 * @brief Retorna o ID de um leitor.
 *
 * @param leitor Ponteiro para o leitor.
 * @return ID do leitor.
 * 
 * @pre leitor != NULL
 * @post Retorna um número inteiro.
 */
int retornaIdleitor(Leitor * leitor);

/**
 * @brief Imprime informações do leitor.
 *
 * @param leitor Ponteiro para o leitor.
 * 
 * @pre leitor != NULL
 */
void imprimeleitor(Leitor * leitor);


/**
 * @brief Libera a memória alocada para o leitor.
 *
 * @param leitor Ponteiro para o leitor.
 * 
 * @pre leitor != NULL
 * @post Memória liberada.
 */
void liberaleitor(Leitor* leitor);


/**
 * @brief Insere um livro em uma lista especifica do leitor.
 *
 * @param leitor Ponteiro para o leitor.
 * @param livro Ponteiro para o livro.
 * @param lista inteiro que identifica se eh lista de lidos ou de desejados.
 * 
 * @pre leitor != NULL, livro != NULL
 * @post Livro inserido na lista especificada.
 */
void insereLivroNaListaLeitor(Leitor* leitor, Livro* livro, int lista);

#endif
