#ifndef listaLivro_h
#define listaLivro_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

typedef struct listaLivros ListaLivros;

ListaLivros* leArquivoLivro(){
    FILE* livrosArq;
    char lerlivro[1000];
    sprintf(lerlivro, "testes/test0-20250602T172934Z-1-001/test0/livros.txt");

    livrosArq = fopen(lerlivro, "r");
    if (livrosArq == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    int primeiraLinha = 0;
    while(1){
        if(primeiraLinha == 0){
            fscanf(livrosArq, "%*[^;];%*[^;];%*[^;];%*[^;];%*[^\n]\n");
            primeiraLinha++;
        }
        else{
            char titulo[100], autor[100], genero[100];
            int id, ano;
            
            int resultado = fscanf(livrosArq, "%d;%[^;];%[^;];%[^;];%d\n", &id, titulo, autor, genero, &ano);
            if (resultado != 5) break;

            Livro* l = criaLivro(id, titulo, autor, genero, ano);
            imprimeNomeLivro(l);
            printf("\n%d %s %s %s %d\n", id, titulo, autor, genero, ano);
            liberaLivro(l);
        }

    }

    fclose(livrosArq);
}

#endif