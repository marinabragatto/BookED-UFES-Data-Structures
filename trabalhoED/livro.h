//
// Autoria de Marina Bragatto e Thais Brandao
//
// Realizado dia 02/06/2025
//

#ifndef livro_h
#define livro_h

#define LIDOS 1
#define DESEJADOS 2
#define RECOMENDADOS 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct livro Livro;

/**Cria novo livro atribuindo os argumentos passados por parametro
 * inputs: idLivro, tituloLivro, autorLivro, generoLivro e anoLivro
 * output: tipo livro inicializado
 * pre-condicao: parametros devem ser passados
 * pos-condicao: tipo livro deve existir e estar inicializado
 */
Livro* criaLivro(int idLivro, char* tituloLivro, char* autorLivro, char* generoLivro, int anoLivro);

/**Compara se um id pertence a um livro
 * inputs: livro e id 
 * output: 1 se o id pertence ao livro, 0, caso contrario
 * pre-condicao: livro passado como parametro deve existir
 * pos-condicao: deve retornar um inteiro
 */
int comparaId(Livro* livro, int id);

/**Retorna o id do livro passado como parametro
 * inputs: livro
 * output: um inteiro representando o id do livro 
 * pre-condicao: livro passado como parametro deve existir
 * pos-condicao: deve retornar um inteiro
 */
int retornaIdLivro(Livro* livro);

//imprime todas as informacoes de um livro (nao sera utilizada)
void imprimeLivro(Livro* livro);

/**Imprime o nome do livro passado como parametro
 * inputs: livro
 * output: nenhum 
 * pre-condicao: livro passado como parametro deve existir
 * pos-condicao: titulo do livro deve ser impresso no arquivo de saida
 */
void imprimeNomeLivro(Livro* livro, FILE* saida);

/**Libera o livro passado como parametro
 * inputs: livro
 * output: nenhum 
 * pre-condicao: livro passado como parametro deve existir
 * pos-condicao: tipo livro deve ser liberado
 */
void liberaLivro(Livro* livro);

#endif