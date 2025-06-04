//
// Autoria de Marina Bragatto e Thais Brandao
//
// Realizado dia 02/06/2025
//

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
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    livro->id = idLivro;
    livro->titulo = strdup(tituloLivro);
    livro->autor = strdup(autorLivro);
    livro->genero = strdup(generoLivro);
    livro->ano = anoLivro;

    return livro;
}

int comparaId(Livro* livro, int id){
    return (retornaIdLivro(livro) == id);
}

int retornaIdLivro(Livro* livro){
    return livro->id;
}

void imprimeLivro(Livro* livro){
    printf("\nId: %d\n", livro->id);
    printf("Titulo:");
    imprimeNomeLivro(livro);
    printf("\nAutor: %s\n", livro->autor);
    printf("Genero: %s\n", livro->genero);
    printf("Ano: %d", livro->ano);
}

void imprimeNomeLivro(Livro* livro){
    printf(" \"%s\" ", livro->titulo);
    // tenho que imprimir no arquivo
}

void liberaLivro(Livro* livro){
    if(livro != NULL){
        if(livro->titulo != NULL) free(livro->titulo);
        if(livro->autor != NULL) free(livro->autor);
        if(livro->genero != NULL) free(livro->genero);
        free(livro);
    }
}
