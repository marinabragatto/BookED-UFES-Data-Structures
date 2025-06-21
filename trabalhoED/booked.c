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


static void AdicionaLivroLido(Booked * booked, int idLeitor, int idLivro, FILE* saida);
static void AdicionaLivroDesejado(Booked * booked, int idLeitor, int idLivro, FILE* saida);
static void RecomendarUmLivro(Booked * booked, int idRec, int idDes, int idLivro, FILE* saida);
static void  AceitarRecomendacao(Booked * booked, int idRec, int idDes, int idLivro, FILE* saida);
static void RejeitarRecomendacao(Booked * booked, int idRec, int idDes, int idLivro, FILE* saida);

Booked* InicializaBooked(){
    Booked* booked = malloc(sizeof(struct booked));
    if(booked == NULL){
       // fprintf(saida,"Erro ao alocar memoria!");
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
    sprintf(leComandos, "testes/test2/test2/comandos.txt");

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
            AdicionaLivroLido(booked, param1, param2, saida);
        break;
        
        case ADICIONA_LIVRO_DESEJADO:
            AdicionaLivroDesejado(booked, param1, param2 ,saida);
        break;

        case ADICIONA_LIVRO_RECOMENDADO:
            RecomendarUmLivro(booked, param1, param3, param2, saida);
        break;

        case ACEITAR_RECOMENDACAO:
            AceitarRecomendacao(booked, param3, param1, param2, saida);
        break;

        case REJEITAR_RECOMENDACAO:
            RejeitarRecomendacao(booked, param3, param1, param2,saida);
        break;

        case IMPRIME_BOOKED:
            ImprimeBooked(booked, saida);
        break;

        default:
        break;
    }
}

void ImprimeBooked(Booked* booked, FILE* saida){
    imprimeLeitoresDaLista(booked->leitores, saida); //colocar o arquivo de saida aqui tbm 
}

static void AdicionaLivroLido(Booked * booked, int idLeitor, int idLivro, FILE* saida){
    Leitor* leitor = retornaLeitorComMesmoId(booked->leitores, idLeitor);
    Livro* livro = retornaLivroComMesmoId(booked->livros, idLivro);

    if(leitor == NULL){
        fprintf(saida,"Erro: Leitor com ID %d não encontrado\n", idLeitor);
        return;
    }
    if(livro == NULL){
        fprintf(saida,"Erro: Livro com ID %d não encontrado\n", idLivro);
        return;
    }


    if(!verificaLivroEstaNaListaLeitor(leitor, livro, LIDOS)){
        insereLivroNaListaLeitor(leitor, livro, LIDOS);

        //PARTE DE IMPRESSÃO
        imprimeNomeLeitor(leitor, saida);
        fprintf(saida, " leu");
        imprimeNomeLivro(livro, saida, COM_ASPAS);
        fprintf(saida, "\n");
    }
    else{
        //PARTE DE IMPRESSÃO
        imprimeNomeLeitor(leitor, saida);    
        fprintf(saida, " já leu");
        imprimeNomeLivro(livro, saida, COM_ASPAS);
        fprintf(saida, "\n");
    }

}

static void AdicionaLivroDesejado(Booked * booked, int idLeitor, int idLivro,FILE* saida){
    Leitor* leitor = retornaLeitorComMesmoId(booked->leitores, idLeitor);
    Livro* livro = retornaLivroComMesmoId(booked->livros, idLivro);

    if(leitor == NULL){
        fprintf(saida,"Erro: Leitor com ID %d não encontrado\n", idLeitor);
        return;
    }
    if(livro == NULL){
        fprintf(saida,"Erro: Livro com ID %d não encontrado\n", idLivro);
        return;
    }

    if(!verificaLivroEstaNaListaLeitor(leitor, livro, DESEJADOS)){
        insereLivroNaListaLeitor(leitor, livro, DESEJADOS);

        //PARTE DE IMPRESSÃO
        imprimeNomeLeitor(leitor, saida);
        fprintf(saida, " deseja ler");
        imprimeNomeLivro(livro, saida, COM_ASPAS);
        fprintf(saida, "\n");
        
    }
    else{
        //PARTE DE IMPRESSÃO
        imprimeNomeLeitor(leitor, saida);
        fprintf(saida, " já deseja ler");
        imprimeNomeLivro(livro, saida, COM_ASPAS);
        fprintf(saida, "\n");
    }
}

static void RecomendarUmLivro(Booked * booked,  int idRec, int idDes, int idLivro, FILE* saida){
    Leitor* recomendador = retornaLeitorComMesmoId(booked->leitores, idRec);
    Leitor* destinatario = retornaLeitorComMesmoId(booked->leitores, idDes);
    Livro* livro = retornaLivroComMesmoId(booked->livros, idLivro);

    if(recomendador == NULL){
        fprintf(saida,"Erro: Leitor recomendador com ID %d não encontrado\n", idRec);
        return;
    }
    if(destinatario == NULL){
       fprintf(saida,"Erro: Leitor destinatário com ID %d não encontrado\n", idDes);
        return;
    }
    if(recomendador == destinatario){
        imprimeNomeLeitor(recomendador, saida);
        fprintf(saida, " não pode recomendar livros para si mesmo\n");
        return;
    }
    if(livro == NULL){
        fprintf(saida,"Erro: Livro com ID %d não encontrado\n", idLivro);
        return;
    }

    if(!verificaLivroEstaNaListaLeitor(destinatario, livro, LIDOS)){
        insereLivroNaListaLeitor(destinatario, livro, RECOMENDADOS);    

        //PARTE DE IMPRESSÃO
        imprimeNomeLeitor(recomendador, saida);
        fprintf(saida, " recomenda");
        imprimeNomeLivro(livro, saida, COM_ASPAS);
        fprintf(saida, "para ");
        imprimeNomeLeitor(destinatario, saida);  
        fprintf(saida, "\n");      
    }
    else{
        //PARTE DE IMPRESSÃO
        imprimeNomeLeitor(destinatario, saida);
        fprintf(saida, " não precisa da recomendação de");
        imprimeNomeLivro(livro, saida, COM_ASPAS);
        fprintf(saida, "pois já leu este livro ");
        fprintf(saida, "\n");
    }
    
}

static void  AceitarRecomendacao(Booked * booked, int idRec, int idDes, int idLivro,FILE* saida){
    Leitor* recomendador = retornaLeitorComMesmoId(booked->leitores, idRec);
    Leitor* destinatario = retornaLeitorComMesmoId(booked->leitores, idDes);
    Livro* livro = retornaLivroComMesmoId(booked->livros, idLivro);

    if(recomendador == NULL){
        fprintf(saida,"Erro: Leitor recomendador com ID %d não encontrado\n", idRec);
        return;
    }
    if(destinatario == NULL){
       fprintf(saida,"Erro: Leitor destinatário com ID %d não encontrado\n", idRec);
        return;
    }
    if(livro == NULL){
        fprintf(saida,"Erro: Livro com ID %d não encontrado\n", idLivro);
        return;
    }

    // FALTA Verificar se recomendação existe !!!!

    if(1){
        insereLivroNaListaLeitor(destinatario, livro, DESEJADOS);
        retiraLivroDaListaLeitor(destinatario, livro);

        //PARTE DE IMPRESSÃO
        imprimeNomeLeitor(destinatario, saida);
        fprintf(saida, " aceita recomendação");
        imprimeNomeLivro(livro, saida, COM_ASPAS);
        fprintf(saida, "de ");
        imprimeNomeLeitor(recomendador, saida);
        fprintf(saida, "\n"); 
    }
    else{

    }





} 

static void RejeitarRecomendacao(Booked * booked, int idRec, int idDes, int idLivro,FILE* saida){
    Leitor* recomendador = retornaLeitorComMesmoId(booked->leitores, idRec);
    Leitor* destinatario = retornaLeitorComMesmoId(booked->leitores, idDes);
    Livro* livro = retornaLivroComMesmoId(booked->livros, idLivro);

    if(recomendador == NULL){
        fprintf(saida,"Erro: Leitor recomendador com ID %d não encontrado\n", idRec);
        return;
    }
    if(destinatario == NULL){
       fprintf(saida,"Erro: Leitor destinatário com ID %d não encontrado\n", idDes);
        return;
    }
    if(livro == NULL){
        fprintf(saida,"Erro: Livro com ID %d não encontrado\n", idLivro);
        return;
    }

    // FALTA Verificar se recomendação existe !!!!
    if(1){
        retiraLivroDaListaLeitor(destinatario, livro);

        imprimeNomeLeitor(destinatario, saida);
        fprintf(saida, " rejeita recomendação");
        imprimeNomeLivro(livro, saida, COM_ASPAS);
        fprintf(saida, "de ");
        imprimeNomeLeitor(recomendador, saida);
        fprintf(saida, "\n"); 
        
    }
    else{

    }
    
}
