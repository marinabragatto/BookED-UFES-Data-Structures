#include "booked.h"

#define ADICIONA_LIVRO_LIDO 1
#define ADICIONA_LIVRO_DESEJADO 2
#define ADICIONA_LIVRO_RECOMENDADO 3
#define ACEITAR_RECOMENDACAO 4
#define REJEITAR_RECOMENDACAO 5
#define IMPRIME_BOOKED 8


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
    FILE* saida;

    saida = fopen("saidas/saida.txt", "w");

    FILE* ComandosArq;
    char leComandos[1000];
    sprintf(leComandos, "testes/test1/test1/comandos.txt");

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

        ExecutaComando(booked, idComando, param1, param2, param3, saida);
    }

    fclose(ComandosArq);
    fclose(saida);
}



void LiberaBooked(Booked* booked){
    if(booked != NULL){
        liberaListaLeitores(booked->leitores);
        liberaListaLivros(booked->livros);
        free(booked);
    }
}



void ExecutaComando(Booked* booked, int idComando, int param1, int param2, int param3, FILE* saida){
    Leitor* leitor1 = retornaLeitorComMesmoId(booked->leitores, param1);
    Leitor* leitor2 = retornaLeitorComMesmoId(booked->leitores, param3);
    Livro* livro = retornaLivroComMesmoId(booked->livros, param2);

    switch (idComando){
        case ADICIONA_LIVRO_LIDO:
            if(!verificaLivroEstaNaListaLeitor(leitor1, livro, LIDOS)){
                insereLivroNaListaLeitor(leitor1, livro, LIDOS);
                ImprimeComandoRealizado(booked, idComando, param1, param2, param3, saida);
            }
            else ImprimeComandoNaoRealizado(booked, idComando, param1, param2, param3, saida);
        break;
        
        case ADICIONA_LIVRO_DESEJADO:
            if(!verificaLivroEstaNaListaLeitor(leitor1, livro, DESEJADOS)){
                insereLivroNaListaLeitor(leitor1, livro, DESEJADOS);
                ImprimeComandoRealizado(booked, idComando, param1, param2, param3, saida);
            }
            else ImprimeComandoNaoRealizado(booked, idComando, param1, param2, param3, saida);
        break;

        case ADICIONA_LIVRO_RECOMENDADO:
            if(param1 == param3) ImprimeComandoNaoRealizado(booked, idComando, param1, param2, param3, saida);
            else{
                if(!verificaLivroEstaNaListaLeitor(leitor2, livro, LIDOS)){
                    insereLivroNaListaLeitor(leitor2, livro, RECOMENDADOS);
                    ImprimeComandoRealizado(booked, idComando, param1, param2, param3, saida);
                }
                else ImprimeComandoNaoRealizado(booked, idComando, param1, param2, param3, saida);
            }
        break;

        case ACEITAR_RECOMENDACAO:
        insereLivroNaListaLeitor(leitor1, livro, DESEJADOS);
        retiraLivroDaListaLeitor(leitor1, livro);
        ImprimeComandoRealizado(booked, idComando, param1, param2, param3, saida);
        break;

        case REJEITAR_RECOMENDACAO:
        retiraLivroDaListaLeitor(leitor1, livro);
        ImprimeComandoRealizado(booked, idComando, param1, param2, param3, saida);
        break;

        case IMPRIME_BOOKED:
        ImprimeComandoRealizado(booked, idComando, param1, param2, param3, saida);
        break;

        default:
        break;
    }
}



void ImprimeComandoRealizado(Booked* booked, int idComando, int param1, int param2, int param3, FILE* saida){
    Leitor* leitor1 = retornaLeitorComMesmoId(booked->leitores, param1);
    Leitor* leitor2 = retornaLeitorComMesmoId(booked->leitores, param3);
    Livro* livro = retornaLivroComMesmoId(booked->livros, param2);

    switch (idComando){
        case ADICIONA_LIVRO_LIDO:
            imprimeNomeLeitor(leitor1, saida);
            fprintf(saida, " leu");
            imprimeNomeLivro(livro, saida, COM_ASPAS);
        break;
    
        case ADICIONA_LIVRO_DESEJADO:
            imprimeNomeLeitor(leitor1, saida);
            fprintf(saida, " deseja ler");
            imprimeNomeLivro(livro, saida, COM_ASPAS);
        break;

        case ADICIONA_LIVRO_RECOMENDADO:
            imprimeNomeLeitor(leitor1, saida);
            fprintf(saida, " recomenda");
            imprimeNomeLivro(livro, saida, COM_ASPAS);
            fprintf(saida, "para ");
            imprimeNomeLeitor(leitor2, saida);
        break;

        case ACEITAR_RECOMENDACAO:
            imprimeNomeLeitor(leitor1, saida);
            fprintf(saida, " aceita recomendação");
            imprimeNomeLivro(livro, saida, COM_ASPAS);
            fprintf(saida, "de ");
            imprimeNomeLeitor(leitor2, saida);
        break; 

        case REJEITAR_RECOMENDACAO:
            imprimeNomeLeitor(leitor1, saida);
            fprintf(saida, " rejeita recomendação");
            imprimeNomeLivro(livro, saida, COM_ASPAS);
            fprintf(saida, "de ");
            imprimeNomeLeitor(leitor2, saida);
        break;

        case IMPRIME_BOOKED:
            fprintf(saida, "\n");
            ImprimeBooked(booked, saida);
        break;

        default:
        break;
    }

    fprintf(saida, "\n");

}


void ImprimeComandoNaoRealizado(Booked* booked, int idComando, int param1, int param2, int param3, FILE* saida){
    Leitor* leitor1 = retornaLeitorComMesmoId(booked->leitores, param1);
    Leitor* leitor2 = retornaLeitorComMesmoId(booked->leitores, param3);
    Livro* livro = retornaLivroComMesmoId(booked->livros, param2);

    switch (idComando){
        case ADICIONA_LIVRO_LIDO: 
            imprimeNomeLeitor(leitor1, saida);
            fprintf(saida, " já leu");
            imprimeNomeLivro(livro, saida, COM_ASPAS);
        break;
    
        case ADICIONA_LIVRO_DESEJADO:
            imprimeNomeLeitor(leitor1, saida);
            fprintf(saida, " já deseja ler");
            imprimeNomeLivro(livro, saida, COM_ASPAS);
        break;

        case ADICIONA_LIVRO_RECOMENDADO: 
            if(param1 == param3){
                imprimeNomeLeitor(leitor2, saida);
                fprintf(saida, " não pode recomendar livros para si mesmo");
            }
            else{
                imprimeNomeLeitor(leitor2, saida);
                fprintf(saida, " não precisa da recomendação de");
                imprimeNomeLivro(livro, saida, COM_ASPAS);
                fprintf(saida, "pois já leu este livro ");
            }
        break;

        case ACEITAR_RECOMENDACAO:
            imprimeNomeLeitor(leitor1, saida);
            fprintf(saida, " aceita recomendação");
            imprimeNomeLivro(livro, saida, COM_ASPAS);
            fprintf(saida, "de ");
            imprimeNomeLeitor(leitor2, saida);
        break; 

        case REJEITAR_RECOMENDACAO:
            imprimeNomeLeitor(leitor1, saida);
            fprintf(saida, " rejeita recomendação");
            imprimeNomeLivro(livro, saida, COM_ASPAS);
            fprintf(saida, "de ");
            imprimeNomeLeitor(leitor2, saida);
        break;

        case IMPRIME_BOOKED:
            ImprimeBooked(booked, saida);
        break;

        default:
        break;
    }

    fprintf(saida, "\n");

}



void ImprimeBooked(Booked* booked, FILE* saida){
    imprimeLeitoresDaLista(booked->leitores, saida); //colocar o arquivo de saida aqui tbm 
}
