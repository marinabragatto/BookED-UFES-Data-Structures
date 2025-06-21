#include "booked.h"

#define ADICIONA_LIVRO_LIDO 1
#define ADICIONA_LIVRO_DESEJADO 2
#define ADICIONA_LIVRO_RECOMENDADO 3
#define ACEITAR_RECOMENDACAO 4
#define REJEITAR_RECOMENDACAO 5
#define LIVROS_EM_COMUM 6
#define VERIFICAR_AFINIDADE 7
#define IMPRIME_BOOKED 8


struct booked{
    Lista * leitores; // Todos os leitores da plataforma
    Lista * livros; // Todos os livros da plataforma
};


static void AdicionaLivroLido(Booked * booked, int idLeitor, int idLivro, FILE* saida);
static void AdicionaLivroDesejado(Booked * booked, int idLeitor, int idLivro, FILE* saida);
static void RecomendarUmLivro(Booked * booked, int idRec, int idDes, int idLivro, FILE* saida);
static void  AceitarRecomendacao(Booked * booked, int idRec, int idDes, int idLivro, FILE* saida);
static void RejeitarRecomendacao(Booked * booked, int idRec, int idDes, int idLivro, FILE* saida);
static void DescobrirLivrosEmComum(Booked * booked, int idLeitor1, int idLeitor2, FILE * saida);
static void VerificaAfinidade(Booked * booked, int idLeitor1, int idLeitor2, FILE * saida);

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
        liberaLista(booked->leitores, liberaleitor);
        liberaLista(booked->livros, liberaLivro);
        free(booked);
    }
}

void ExecutaComando(Booked* booked, int idComando, int param1, int param2, int param3, FILE* saida){

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

        case LIVROS_EM_COMUM:
            DescobrirLivrosEmComum(booked, param1, param3, saida);
        break;

        case VERIFICAR_AFINIDADE:
            VerificaAfinidade(booked, param1, param3, saida);
        break;

        default:
            fprintf(saida,"Erro: Comando %d não reconhecido\n", idComando);
        break;

    }
}

void ImprimeBooked(Booked* booked, FILE* saida){
    fprintf(saida,"Imprime toda a BookED\n\n");
    imprimeLista(booked->leitores, imprimeleitor, saida); //colocar o arquivo de saida aqui tbm 
}

static void AdicionaLivroLido(Booked * booked, int idLeitor, int idLivro, FILE* saida){
    Leitor* leitor = retornaElemComMesmoId(booked->leitores, idLeitor, comparaIdLeitor);
    Livro* livro = retornaElemComMesmoId(booked->livros, idLivro, comparaIdLivro);

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
        fprintf(saida, " leu ");
        imprimeNomeLivro(livro, saida, COM_ASPAS);
        fprintf(saida, "\n");
    }
    else{
        //PARTE DE IMPRESSÃO
        imprimeNomeLeitor(leitor, saida);    
        fprintf(saida, " já leu ");
        imprimeNomeLivro(livro, saida, COM_ASPAS);
        fprintf(saida, "\n");
    }

}

static void AdicionaLivroDesejado(Booked * booked, int idLeitor, int idLivro,FILE* saida){
    Leitor* leitor = retornaElemComMesmoId(booked->leitores, idLeitor, comparaIdLeitor);
    Livro* livro = retornaElemComMesmoId(booked->livros, idLivro, comparaIdLivro);

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
        fprintf(saida, " deseja ler ");
        imprimeNomeLivro(livro, saida, COM_ASPAS);
        fprintf(saida, "\n");
        
    }
    else{
        //PARTE DE IMPRESSÃO
        imprimeNomeLeitor(leitor, saida);
        fprintf(saida, " já deseja ler ");
        imprimeNomeLivro(livro, saida, COM_ASPAS);
        fprintf(saida, "\n");
    }
}

static void RecomendarUmLivro(Booked * booked,  int idRec, int idDes, int idLivro, FILE* saida){
    Leitor* recomendador = retornaElemComMesmoId(booked->leitores, idRec, comparaIdLeitor);
    Leitor* destinatario = retornaElemComMesmoId(booked->leitores, idDes, comparaIdLeitor);
    Livro* livro = retornaElemComMesmoId(booked->livros, idLivro, comparaIdLivro);

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


    if(verificaLivroEstaNaListaLeitor(destinatario, livro, DESEJADOS)){
        imprimeNomeLeitor(destinatario, saida);
        fprintf(saida, " já deseja ler ");
        imprimeNomeLivro(livro, saida, COM_ASPAS);
        fprintf(saida,", recomendação desnecessária\n");
        //Bruno já deseja ler "Dom Casmurro", recomendação desnecessária
    }
    else if(!verificaLivroEstaNaListaLeitor(destinatario, livro, LIDOS)){
        insereLivroNaListaLeitor(destinatario, livro, RECOMENDADOS);    

        //PARTE DE IMPRESSÃO
        imprimeNomeLeitor(recomendador, saida);
        fprintf(saida, " recomenda ");
        imprimeNomeLivro(livro, saida, COM_ASPAS);
        fprintf(saida, " para ");
        imprimeNomeLeitor(destinatario, saida);  
        fprintf(saida, "\n");      
    }
    else{
        //PARTE DE IMPRESSÃO
        imprimeNomeLeitor(destinatario, saida);
        fprintf(saida, " não precisa da recomendação de ");
        imprimeNomeLivro(livro, saida, COM_ASPAS);
        fprintf(saida, " pois já leu este livro\n");
    }
    
}

static void  AceitarRecomendacao(Booked * booked, int idRec, int idDes, int idLivro,FILE* saida){
    Leitor* recomendador = retornaElemComMesmoId(booked->leitores, idRec, comparaIdLeitor);
    Leitor* destinatario = retornaElemComMesmoId(booked->leitores, idDes, comparaIdLeitor);
    Livro* livro = retornaElemComMesmoId(booked->livros, idLivro, comparaIdLivro);

    if(recomendador == NULL){
        fprintf(saida,"Erro: Leitor recomendador com ID %d não encontrado\n", idRec);
        return;
    }
    if(destinatario == NULL){
       fprintf(saida,"Erro: Leitor com ID %d não encontrado\n", idDes);
        return;
    }
    

    // FALTA Verificar se recomendação existe !!!!
    if(livro == NULL){
        imprimeNomeLeitor(destinatario, saida);
        fprintf(saida, " não possui recomendação do livro ID %d feita por ", idLivro);
        imprimeNomeLeitor(recomendador, saida);
        fprintf(saida, "\n");
    }
    else if(verificaLivroEstaNaListaLeitor(destinatario, livro, RECOMENDADOS)){
        insereLivroNaListaLeitor(destinatario, livro, DESEJADOS);
        retiraLivroDaListaLeitor(destinatario, livro);

        //PARTE DE IMPRESSÃO
        imprimeNomeLeitor(destinatario, saida);
        fprintf(saida, " aceita recomendação ");
        imprimeNomeLivro(livro, saida, COM_ASPAS);
        fprintf(saida, " de ");
        imprimeNomeLeitor(recomendador, saida);
        fprintf(saida, "\n"); 
    }
    else{
        imprimeNomeLeitor(destinatario, saida);
        fprintf(saida, " não possui recomendação do livro ID %d feita por ", idLivro);
        imprimeNomeLeitor(recomendador, saida);
        fprintf(saida, "\n");
         
    }





} 

static void RejeitarRecomendacao(Booked * booked, int idRec, int idDes, int idLivro,FILE* saida){
    Leitor* recomendador = retornaElemComMesmoId(booked->leitores, idRec, comparaIdLeitor);
    Leitor* destinatario = retornaElemComMesmoId(booked->leitores, idDes, comparaIdLeitor);
    Livro* livro = retornaElemComMesmoId(booked->livros, idLivro, comparaIdLivro);

    if(recomendador == NULL){
        fprintf(saida,"Erro: Leitor recomendador com ID %d não encontrado\n", idRec);
        return;
    }
    if(destinatario == NULL){
       fprintf(saida,"Erro: Leitor com ID %d não encontrado\n", idDes);
        return;
    }
    

    // FALTA Verificar se recomendação existe !!!!

    if(livro == NULL){
        imprimeNomeLeitor(destinatario, saida);
        fprintf(saida, " não possui recomendação do livro ID %d feita por ", idLivro);
        imprimeNomeLeitor(recomendador, saida);
        fprintf(saida, "\n");
    }
    else if(verificaLivroEstaNaListaLeitor(destinatario, livro, RECOMENDADOS)){
        retiraLivroDaListaLeitor(destinatario, livro);

        imprimeNomeLeitor(destinatario, saida);
        fprintf(saida, " rejeita recomendação ");
        imprimeNomeLivro(livro, saida, COM_ASPAS);
        fprintf(saida, " de ");
        imprimeNomeLeitor(recomendador, saida);
        fprintf(saida, "\n"); 
        
    }
    else{
        imprimeNomeLeitor(destinatario, saida);
        fprintf(saida, " não possui recomendação do livro ID %d feita por ", idLivro);
        imprimeNomeLeitor(recomendador, saida);
        fprintf(saida, "\n");
         
      //  Marcus não possui recomendação do livro ID 4 feita por Marcus

    }
    
}

static void DescobrirLivrosEmComum(Booked * booked, int idLeitor1, int idLeitor2, FILE * saida){
    Leitor* Leitor1 = retornaElemComMesmoId(booked->leitores, idLeitor1, comparaIdLeitor);
    Leitor* Leitor2 = retornaElemComMesmoId(booked->leitores, idLeitor2, comparaIdLeitor);
    if(Leitor1 == NULL){
        fprintf(saida,"Erro: Leitor com ID %d não encontrado\n", idLeitor1);
        return;
    }
    if(Leitor2 == NULL){
       fprintf(saida,"Erro: Leitor com ID %d não encontrado\n", idLeitor2);
        return;
    }
    
    Lista * comum = LivrosEmComumLeitores(Leitor1, Leitor2);
        fprintf(saida, "Livros em comum entre ");
        imprimeNomeLeitor(Leitor1, saida);
        fprintf(saida, " e ");
        imprimeNomeLeitor(Leitor2, saida);
        fprintf(saida,": ");
    if(comum){
        imprimirLivrosLeitor(comum, saida);
        fprintf(saida,"\n");
        liberaListaParcialmente(comum);
    }
    else{
        fprintf(saida,"Nenhum livro em comum\n");
    }
   
    
}

static void VerificaAfinidade(Booked * booked, int idLeitor1, int idLeitor2, FILE * saida){
    Leitor* Leitor1 = retornaElemComMesmoId(booked->leitores, idLeitor1, comparaIdLeitor);
    Leitor* Leitor2 = retornaElemComMesmoId(booked->leitores, idLeitor2,comparaIdLeitor);
    if(Leitor1 == NULL){
        fprintf(saida,"Erro: Leitor com ID %d não encontrado\n", idLeitor1);
        return;
    }
    if(Leitor2 == NULL){
       fprintf(saida,"Erro: Leitor com ID %d não encontrado\n", idLeitor2);
        return;
    }
}

Lista * leArquivoLeitores(){
    /*
    Id;nome;n_afinidades; afinidades
    1;Alice;2;Romance; Terror
    2;Bob;2;Terror;Mistério
    3;Clara;1;Mistério
    */
    Lista  * lista = criaLista();
    if(lista == NULL){
        printf("Erro ao Alocar Memória");
        exit(1);
    }

    // Abre efetivamente o arquivo
    FILE * arquivoLeitores;
    char nomeArquivo[200] = "testes/test1/test1/leitores.txt";
    arquivoLeitores = fopen(nomeArquivo, "r");
    if(arquivoLeitores == NULL){
        printf("Erro ao Abrir arquivo Leitores");
        exit(1);
    }

    // Le efetivamente o arquivo
    fscanf(arquivoLeitores,"%*[^\n]\n"); // Descarta o cabeçalho

    // Coisas a serem lidas:
    int id, qtdAfin;
    Lista * Gostos;
    char afinididade[TAM_GOSTO];
    char nome[TAM_MAX_NOME_LEITOR];
    Leitor * novo;

    while(1){
        if(fscanf(arquivoLeitores, "%d;", &id) == 1){
            fscanf(arquivoLeitores, "%[^;];", nome);

            fscanf(arquivoLeitores,"%d;",&qtdAfin);
            Gostos = criaLista();

            for(int i = 0; i < qtdAfin; i++){
                if(i != qtdAfin-1){
                    fscanf(arquivoLeitores,"%[^;];", afinididade);
                }
                else{
                    fscanf(arquivoLeitores,"%[^\n]\n", afinididade);
                }
                //printf("(%s)", afinididade);
                char * pontAfinidade = strdup(afinididade);
                insereElemNoFimDaLista(Gostos, pontAfinidade);
            }
            
             // Descarta TEMPORARIAMENTE as afinidades
            novo = criaLeitor(id, nome, Gostos);
            //imprimeleitor(novo);
            insereElemNoFimDaLista(lista, novo);
        }
        else{ 
            break;
        }
    }
    fclose(arquivoLeitores);

    return lista;

}

Lista * leArquivoLivros(){
    Lista * lista = criaLista(); //cria a lista de livros

    //abrindo o arquivo pra leitura
    FILE* livrosArq;
    char lerlivro[1000];
    sprintf(lerlivro, "testes/test1/test1/livros.txt"); //aqui eh preciso pensar como nos vamos chegar ate o livros.txt de cada caso de teste

    livrosArq = fopen(lerlivro, "r");
    if (livrosArq == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    fscanf(livrosArq,"%*[^\n]\n"); // Descarta o cabeçalho

    while(1){
        char titulo[100], autor[100], genero[100];
        int id, ano;
        
        int resultado = fscanf(livrosArq, "%d;%[^;];%[^;];%[^;];%d\n", &id, titulo, autor, genero, &ano); //da pra ler isso de forma mais eficiente tbm
        if (resultado != 5) break;

        Livro* novoLivro = criaLivro(id, titulo, autor, genero, ano);
        insereElemNoFimDaLista(lista, novoLivro);
    }

    fclose(livrosArq);

    return lista;
}
