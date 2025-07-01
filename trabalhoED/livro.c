/**
 * @file livro.c
 * @brief Implementação das funções relacionadas ao tipo Livro.
 *
 * Este arquivo contém a implementação das funções para criação, manipulação
 * e liberação de livros no sistema.
 *
 * @author Marina Bragatto
 * @author Thais Brandão
 * @date 09/06/2025
 */

#include "livro.h"

typedef struct livro Livro;

struct livro{
    int id;
    char* titulo;
    char* autor;
    char* genero;
    int ano;
};

Livro* criaLivro(int idLivro, char* tituloLivro, char* autorLivro, char* generoLivro, int anoLivro){
    Livro* livro = malloc(sizeof(struct livro));
    if(livro == NULL){
        exit(1);
    }

    livro->id = idLivro;
    livro->titulo = strdup(tituloLivro);
    livro->autor = strdup(autorLivro);
    livro->genero = strdup(generoLivro);
    livro->ano = anoLivro;

    return livro;
}

int comparaIdLivro(void * livro, void * id){
    Livro * l = (Livro*)livro;

    return (retornaIdLivro(l) == *((int*)id));
}

int retornaIdLivro(Livro* livro){
    return livro->id;
}

void imprimeLivro(void * livro, FILE * saida){
    Livro * l = (Livro *)livro;
    imprimeNomeLivro(l, saida, SEM_ASPAS);
}

void imprimeNomeLivro(Livro* livro, FILE* saida, int aspas){
    switch (aspas){
    case COM_ASPAS:
        fprintf(saida, "\"%s\"", livro->titulo);
    break;
    
    case SEM_ASPAS:
        fprintf(saida, "%s" , livro->titulo);
        break;
    default:
        break;
    }
}

void liberaLivro(void * livro){
    Livro * l = (Livro *)livro;
    if(l != NULL){
        if(l->titulo != NULL) free(l->titulo);
        if(l->autor != NULL) free(l->autor);
        if(l->genero != NULL) free(l->genero);
        free(livro);
    }
}
