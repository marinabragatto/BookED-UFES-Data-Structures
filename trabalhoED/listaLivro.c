#include "listaLivro.h"

typedef struct listaLivros ListaLivros;

//So um teste de como eu leria cada um dos livros e colocaria eles na lista de livros
ListaLivros* leArquivoLivros(){
    FILE* livrosArq;
    char lerlivro[1000];
    sprintf(lerlivro, "testes/test0-20250602T172934Z-1-001/test0/livros.txt"); //aqui eh preciso pensar como nos vamos chegar ate o livros.txt de cada caso de teste

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
            
            int resultado = fscanf(livrosArq, "%d;%[^;];%[^;];%[^;];%d\n", &id, titulo, autor, genero, &ano); //da pra ler isso de forma mais eficiente tbm
            if (resultado != 5) break;

            Livro* l = criaLivro(id, titulo, autor, genero, ano);
            // imprimeNomeLivro(l);
            // printf("\n%d %s %s %s %d\n", id, titulo, autor, genero, ano);
            // liberaLivro(l);
            // AQUI SERIA A INSERCAO DE CADA LIVRO NA LISTA
        }

    }

    fclose(livrosArq);
}
