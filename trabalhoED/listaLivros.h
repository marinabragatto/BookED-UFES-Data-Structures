//
// Autoria de Marina Bragatto e Thais Brandao
//
// Realizado dia 03/06/2025
//

#ifndef listaLivros_h
#define listaLivros_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

typedef struct listaLivros ListaLivros;

/**Cria uma lista de livros duplamente encadeada, com sentinela
 * inputs: nenhum
 * output: listaLivros 
 * pre-condicao: nenhuma
 * pos-condicao: retorna lista inicializada
 */
ListaLivros* criaListaLivros();

/**Le o arquivo livros.txt, cria os livros e adiciona eles a lista de livros
 * inputs: nenhum
 * output: listaLivros inicializada e preenchida 
 * pre-condicao: arquivo deve existir
 * pos-condicao: listaLivros deve estar inicializada e preenchida
 */
ListaLivros* leArquivoLivros();

/**Insere um novo livro no fim da listaLivros
 * inputs: listaLivros e livroNovo
 * output: nenhum 
 * pre-condicao: listaLivros e novoLivro passados como parametro devem existir
 * pos-condicao: livro eh adicionado ao fim da lista
 */
void insereLivroNoFimDaLista(ListaLivros* lista, Livro* livroNovo);

/**Retorna o livro cujo id passado pertence
 * inputs: listaLivros e id
 * output: livro 
 * pre-condicao: listaLivros passada como parametro deve existir
 * pos-condicao: retorna o livro caso o id pertenca e ele e NULL caso contrario
 */
Livro* retornaLivroComMesmoId(ListaLivros* lista, int id);

/**Imprime todos os livros da listaLivros passada como parametro
 * inputs: listaLivros
 * output: nenhum 
 * pre-condicao: listaLivros passada como parametro deve existir
 * pos-condicao: livros apontados pelo tipo listaLivros devem ser impressos
 */
void imprimeLivrosDaLista(ListaLivros* lista);

/**Libera a listaLivros passada como parametro
 * inputs: listaLivros
 * output: nenhum 
 * pre-condicao: listaLivros passada como parametro deve existir
 * pos-condicao: tipo listaLivros deve ser liberada
 */
void liberaListaLivros(ListaLivros* lista);


/**Libera a listaLivros passada como parametro, mas não libera o Livro em si
 * inputs: listaLivros
 * output: nenhum 
 * pre-condicao: listaLivros passada como parametro deve existir
 * pos-condicao: tipo listaLivros deve ser liberada
 */
void liberaListaLivrosParcialmente(ListaLivros* lista);

#endif
