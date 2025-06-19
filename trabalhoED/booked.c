#include "booked.h"

#define ADICIONA_LIVRO_LIDO 1
#define ADICIONA_LIVRO_DESEJADO 2
#define ADICIONA_LIVRO_RECOMENDADO 3

struct booked{
    ListaLeitores * leitores; // Todos os leitores da plataforma
    ListaLivros * livros; // Todos os livros da plataforma
};


Booked* InicializaBooked(){
    Booked* booked = malloc(sizeof(struct booked));
    if(booked == NULL){
        printf("Erro ao alocar memoria!");
        exit(1);
    }
    
    booked->livros = leArquivoLivros();
    booked->leitores = leArquivoLeitores();   

    return booked;
}



void FuncionaBooked(Booked* booked){
    FILE* ComandosArq;
    char leComandos[1000];
    sprintf(leComandos, "testes/test0/test0/comandos.txt");

    ComandosArq = fopen(leComandos, "r");
    if (ComandosArq == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    fscanf(ComandosArq,"%*[^\n]\n"); // Descarta o cabeçalho

    while(1){
        int idComando, param1, param2, param3;
        
        int resultado = fscanf(ComandosArq, "%d;%d;%d;%d\n", &idComando, &param1, &param2, &param3); 
        if (resultado != 4) break;

        ExecutaComando(booked, idComando, param1, param2, param3);
    }

    fclose(ComandosArq);
}



void LiberaBooked(Booked* booked){
    if(booked != NULL){
        liberaListaLeitores(booked->leitores);
        liberaListaLivros(booked->livros);
        free(booked);
    }
}



void ExecutaComando(Booked* booked, int idComando, int param1, int param2, int param3){
    switch (idComando){
        case ADICIONA_LIVRO_LIDO:
        case ADICIONA_LIVRO_DESEJADO:
        Livro* livro = retornaLivroComMesmoId(booked->livros, param2);
        booked->leitores = AdicionaLivroListaLeitor(booked->leitores, livro, param1, param2, idComando);
        break;
        
        case ADICIONA_LIVRO_RECOMENDADO:

        default:
            break;
    }
}




void ImprimeBooked(Booked* booked){
    //teste pra ver se o livro foi adicionado a lista de lidos dos leitores
    imprimeLeitoresDaLista(booked->leitores);
}
