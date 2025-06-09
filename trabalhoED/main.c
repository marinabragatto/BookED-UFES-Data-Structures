#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaLivros.h"
#include "listaLeitores.h"
#include "livro.h"

//testando se a lista de livros foi alocada e removida corretamente (sucesso (0-0) valgrind deu certo tbm)

void testaFuncionalidadesListaLeitores();
void testaFuncionalidadesListaLivros();


int main(int argc, char *argv[]){
    //testaFuncionalidadesListaLivros(); //vai ficar no booked.c
    testaFuncionalidadesListaLeitores();
    return 0;
}


void testaFuncionalidadesListaLivros(){
    ListaLivros* listaLivros = leArquivoLivros();
    Livro* livro = retornaLivroComMesmoId(listaLivros, 16);

    if(livro != NULL) imprimeLivro(livro);
    else printf("Id solicitado nao corresponde a um livro\n");

    imprimeLivrosDaLista(listaLivros);
    liberaListaLivros(listaLivros);
}

void testaFuncionalidadesListaLeitores(){
    ListaLeitores * lista = leArquivoLeitores();
    imprimeLeitoresDaLista(lista);
    liberaListaLeitores(lista);
}