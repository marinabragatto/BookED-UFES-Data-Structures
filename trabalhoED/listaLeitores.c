#include "listaLeitores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct celula Celula;

struct celula {
    Leitor * leitor;
    Celula * ant;
    Celula * prox;
};


struct listaLeitores{
    Celula * prim;
    Celula * ult;
};




/**Cria uma lista de leitores duplamente encadeada, com sentinela
 * inputs: nenhum
 * output: listaLeitores
 * pre-condicao: nenhuma
 * pos-condicao: retorna lista inicializada
 */
ListaLeitores * criaListaLeitores(){
    ListaLeitores * lista = (ListaLeitores*)malloc(sizeof(ListaLeitores));
    lista->ult = NULL;
    lista->prim = NULL;

    return lista;
}

/**Le o arquivo leitores.txt e adiciona eles a lista de leitores
 * inputs: nenhum
 * output: listaLeitores inicializada e preenchida 
 * pre-condicao: arquivo deve existir
 * pos-condicao: listaLeitores deve estar inicializada e preenchida
 */
ListaLeitores * leArquivoLeitores(){
    /*
    Id;nome;n_afinidades; afinidades
    1;Alice;2;Romance; Terror
    2;Bob;2;Terror;Mistério
    3;Clara;1;Mistério
    */
    ListaLeitores  * lista = criaListaLeitores();

    // Abre efetivamente o arquivo
    FILE * arquivoLeitores;
    char nomeArquivo[200] = "testes/test1-20250602T172935Z-1-001/test1/livros.txt";
    arquivoLeitores = fopen(nomeArquivo, "r");

    // Le efetivamente o arquivo
    fscanf(arquivoLeitores,"%*[^\n]"); // Descarta o cabeçalho


    fclose(arquivoLeitores);

   // while(){

    //}

    return lista;

}

/**Insere um novo livro no fim da listaLivros
 * inputs: listaLivros e livroNovo
 * output: nenhum 
 * pre-condicao: listaLivros e novoLivro passados como parametro devem existir
 * pos-condicao: livro eh adicionado ao fim da lista
 */
void insereLeitorNoFimDaLista(ListaLeitores * lista, Leitor * leitorNovo){

}

/**Libera a listaLeitores passada como parametro
 * inputs: listaLeitores
 * output: nenhum 
 * pre-condicao: listaLeitores passada como parametro deve existir
 * pos-condicao: tipo listaLeitores deve ser liberada
 */
void liberaListaLeitores(ListaLeitores * lista){

}