//
// Autoria de Marina Bragatto e Thais Brandao
//
// Realizado dia 08/06/2025
//

#ifndef listaLeitores_h
#define listaLeitores_h

#include "leitor.h"

typedef struct listaLeitores ListaLeitores;


/**Cria uma lista de leitores duplamente encadeada, com sentinela
 * inputs: nenhum
 * output: listaLeitores
 * pre-condicao: nenhuma
 * pos-condicao: retorna lista inicializada
 */
ListaLeitores * criaListaLeitores();

/**Le o arquivo leitores.txt e adiciona eles a lista de leitores
 * inputs: nenhum
 * output: listaLeitores inicializada e preenchida 
 * pre-condicao: arquivo deve existir
 * pos-condicao: listaLeitores deve estar inicializada e preenchida
 */
ListaLeitores * leArquivoLeitores();

/**Insere um novo livro no fim da listaLivros
 * inputs: listaLivros e livroNovo
 * output: nenhum 
 * pre-condicao: listaLivros e novoLivro passados como parametro devem existir
 * pos-condicao: livro eh adicionado ao fim da lista
 */
void insereLeitorNoFimDaLista(ListaLeitores * lista, Leitor * leitorNovo);

/**Libera a listaLeitores passada como parametro
 * inputs: listaLeitores
 * output: nenhum 
 * pre-condicao: listaLeitores passada como parametro deve existir
 * pos-condicao: tipo listaLeitores deve ser liberada
 */
void liberaListaLeitores(ListaLeitores * lista);




#endif