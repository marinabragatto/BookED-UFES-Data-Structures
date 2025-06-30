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

#define TAM_GOSTO 130

#ifndef leitor_h
#define leitor_h

#include "lista.h"
#include "livro.h"


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
Leitor* criaLeitor(int idleitor, char * nome, Lista * gostos);  // PASSAR COMO PARAMETRO TAMBEM A LISTA CHAR DE AFINIDADES?


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
int comparaIdLeitor(void * leitor, void * id);


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
void imprimeleitor(void * leitor, FILE* saida);


/**
 * @brief Imprime o nome do leitor no arquivo de saida.
 *
 * @param leitor Ponteiro para o leitor.
 * 
 * @pre leitor != NULL
 */
void imprimeNomeLeitor(Leitor* leitor, FILE* saida);


/**
 * @brief Libera a memória alocada para o leitor.
 *
 * @param leitor Ponteiro para o leitor.
 * 
 * @pre leitor != NULL
 * @post Memória liberada.
 */
void liberaleitor(void * leitor);


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


/**
 * @brief Retira um livro de uma lista de recomendacoes do leitor.
 *
 * @param leitor Ponteiro para o leitor.
 * @param livro Ponteiro para o livro.
 * 
 * @pre leitor != NULL, livro != NULL
 * @post Livro inserido na lista especificada.
 */
void retiraLivroDaListaLeitor(Leitor* leitor, Livro* livro);


/**
 * @brief Verifica se um livro ja se encontra em uma lista especifica do leitor.
 *
 * @param leitor Ponteiro para o leitor.
 * @param livro Ponteiro para o livro.
 * @param lista inteiro que identifica qual a lista.
 * 
 * @pre leitor != NULL, livro != NULL
 * @post inteiro indicando ou nao a existencia do livro na lista.
 */
int verificaLivroEstaNaListaLeitor(Leitor* leitor, Livro* livro, int lista);


/**
 * @brief Cria uma lista com os livros lidos em comum entre leitores.
 *
 * Percorre a lista de livros lidos de um dos leitores e confere se o outro tambem ja leu.
 * 
 * @param leitor1 Ponteiro para o leitor1.
 * @param leitor2 Ponteiro para o leitor2.
 * 
 * @return lista com livros em comum dos leitores.
 * 
 * @pre leitor1 != NULL, leitor2 != NULL
 * @post inteiro indicando ou nao a existencia do livro na lista.
 */
Lista * LivrosEmComumLeitores(Leitor * leitor1, Leitor * leitor2);


/**
 * @brief Imprime os nomes de uma sequencia de livros.
 * 
 * @param lista lista de livros a ser percorrida.
 * @param saida arquivo de saida.
 * 
 * @pre gostos != NULL
 */
void imprimirLivrosLeitor(Lista * lista, FILE * saida);


/**
 * @brief Imprime os gostos literarios dos leitores.
 * 
 * @param gostos lista de gostos a ser percorrida.
 * @param saida arquivo de saida.
 * 
 * @pre gostos != NULL
 */
void ImprimeGostos(Lista * gostos, FILE* saida);


/**
 * @brief Cria as listas de afinidades dos leitores.
 *
 * Percorre a lista de leitores e atualiza suas listas de afinidades com base nos gostos em comum.
 * 
 * @param leitores lista de leitores a ser percorrida.
 * 
 * @pre leitores != NULL
 * @post atualiza listas de afinidades dos leitores.
 */
void ConectaAfinidadesDireta(Lista * leitores);


/**
 * @brief Imprime o nome de cada leitor de uma lista, separado por vírgulas.
 *
 * @param leitores lista de leitores a ser percorrida.
 * @param saida arquivo de saida.
 * 
 * @pre lista leitores != NULL
 */
void imprimirLeitores(Lista * leitores, FILE * saida);


/**
 * @brief Compara dois leitores por meio da verificação de ponteiros iguais.
 *
 * @param leitor2 leitor a ser comparado.
 * @param leitor1 leitor a ser comparado.
 * @return Ao final a funcao retorna 1 caso sejam iguais, 0 caso contrario.
 * 
 * @pre leitor2 e leitor1 != NULL
 * @post retorna um inteiro.
 */
int comparaDoisLeitores(void * leitor2, void * leitor1);


/**
 * @brief Confere se o leitor2 esta na lista direta de afinidades do leitor1.
 *
 * @param leitor1 leitor cuja lista de afinidades sera percorrida.
 * @param leitor2 leitor a ser comparado.
 * @return Ao final a funcao retorna 1 caso leitor2 esteja na lista direta de afinidades do leitor1, 0 caso contrario.
 * 
 * @pre leitor2 e leitor1 != NULL
 * @post retorna um inteiro.
 */
int verificaAfinidadeJaExiste(Leitor * leitor1, Leitor * leitor2);


/**
 * @brief Verifica se dois leitores tem algum gosto (genero literario) em comum.
 *
 * Percorre a lista de gostos de ambos os leitores e retorna caso encontre algum gosto em comum.
 * 
 * @param leitor1 leitor a ser comparado.
 * @param leitor2 leitor a ser comparado.
 * @return Ao final a funcao retorna 1 caso os leitores tenham compatibilidade, 0 caso contrario.
 * 
 * @pre leitor2 e leitor1 != NULL
 * @post retorna um inteiro.
 */
int verificaCompatibilidade(Leitor * leitor2, Leitor * leitor1);


/**
 * @brief Procura afinidade entre dois leitores.
 *
 * Inicialmente verifica se existe uma afinidade direta entre dois leitores, ou seja, um esta na lista de afinidades do outro.
 * Caso nao haja, a funcao, a partir de chamadas recursivas a si mesma, percorre as listas de afinidades de todos os leitores
 * presentes na lista de afinidades do leitor de origem (marcando-as como ja visitadas, para evitar loops) e assim sucessivamente.
 *
 * @param origem leitor origem.
 * @param destino leitor origem.
 * @param visitados lista de leitores ja conferidos.
 * @return Ao final a funcao retorna 1 caso exista afinidade, 0 caso contrario.
 * 
 * @pre leitor origem e destino e lista visitados != NULL
 */
int ConectaAfinidadesIndireta(Leitor * origem, Leitor * destino, Lista * visitados);

#endif
