/**
 * @file livro.h
 * @brief Interface do módulo de livro.
 *
 * Define o tipo abstrato Livro e funções relacionadas à criação,
 * manipulação e liberação de livros.
 * 
 * @author Marina Bragatto
 * @author Thais Brandão
 * @date 09/06/2025
 */

#ifndef livro_h
#define livro_h

#define LIDOS 1
#define DESEJADOS 2
#define RECOMENDADOS 3

#define SEM_ASPAS 0
#define COM_ASPAS 1


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct livro Livro;



/**
 * @brief Cria novo livro atribuindo os argumentos passados por parametro.
 * 
 * @param idLivro id do livro.
 * @param tituloLivro string contendo o nome do livro.
 * @param autorLivro string contendo o nome do autor do livro.
 * @param generoLivro string contendo o genero do livro.
 * @param anoLivro ano do livro.
 *
 * @return tipo livro inicializado.
 * 
 * @pre parametros devem ser passados.
 * @post tipo livro deve existir e estar inicializado.
 */
Livro* criaLivro(int idLivro, char* tituloLivro, char* autorLivro, char* generoLivro, int anoLivro);



/**
 * @brief Compara se um id pertence a um livro.
 * 
 * @param livro livro a ser comparado.
 * @param id id a ser comparado.
 *
 * @return 1 caso sejam iguais, zero caso contrario.
 * 
 * @pre livro != NULL
 */
int comparaIdLivro(void * livro, void * id);



/**
 * @brief Retorna o id do livro passado como parametro.
 * 
 * @param livro livro a ter o id retornado.
 *
 * @return um inteiro representando o id do livro.
 * 
 * @pre livro != NULL
 */
int retornaIdLivro(Livro* livro);



/**
 * @brief Imprime um livro, decide a forma de impressao, com ou sem aspas.
 * 
 * @param livro livro a ser impresso.
 * @param saida arquivo de saida.
 * 
 * @pre livro != NULL
 */
void imprimeLivro(void * livro, FILE * saida);



/**
 * @brief Imprime o nome de um livro.
 * 
 * @param livro livro a ser impresso.
 * @param saida arquivo de saida.
 * @param aspas com ou sem aspas.
 * 
 * @pre livro != NULL
 */
void imprimeNomeLivro(Livro* livro, FILE* saida, int aspas);



/**
 * @brief Libera um livro, caso esse nao seja NULL.
 * 
 * @param livro livro a ser liberado.
 * 
 * @post livro liberado.
 */
void liberaLivro(void * livro);

#endif