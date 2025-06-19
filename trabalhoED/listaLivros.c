//
// Autoria de Marina Bragatto e Thais Brandao
//
// Realizado dia 03/06/2025
//

#include "listaLivros.h"

typedef struct celula Celula;

struct celula{
    Livro* livro;
    Celula* ant;
    Celula* prox;
};

struct listaLivros{
    Celula* prim;
    Celula* ult;
};



//So um teste de como eu leria cada um dos livros e colocaria eles na lista de livros
ListaLivros* leArquivoLivros(){
    ListaLivros* lista = criaListaLivros(); //cria a lista de livros

    //abrindo o arquivo pra leitura
    FILE* livrosArq;
    char lerlivro[1000];
    sprintf(lerlivro, "testes/test0/test0/livros.txt"); //aqui eh preciso pensar como nos vamos chegar ate o livros.txt de cada caso de teste

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
        insereLivroNoFimDaLista(lista, novoLivro);
    }

    fclose(livrosArq);

    return lista;
}



ListaLivros* criaListaLivros(){
    ListaLivros* lista = malloc(sizeof(struct listaLivros));
    if(lista == NULL){
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    lista->prim = NULL;
    lista->ult = NULL;

    return lista;
}



void insereLivroNoFimDaLista(ListaLivros* lista, Livro* livroNovo){
    Celula* nova = malloc(sizeof(struct celula));
    if(nova == NULL){
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    nova->livro = livroNovo;
    nova->ant = NULL;
    nova->prox = NULL;

    if(lista->prim == NULL && lista->ult == NULL){ //caso seja a primeira celula contendo um livro
        lista->prim = nova;
        lista->ult = nova;
    }
    else{
        nova->ant = lista->ult; //aponta o elemento anterior da nova celula pra ultima celula da lista
        lista->ult->prox = nova; //aponta o proximo elemento da ultima celula da lista pra nova
        lista->ult = nova; //aponta a celula ult da sentinela pra nova celula
    }
}



Livro* retornaLivroComMesmoId(ListaLivros* lista, int id){
    Celula* aux;
    for(aux = lista->prim; aux != NULL; aux = aux->prox){
        if(comparaId(aux->livro, id)) return aux->livro;
    }

    return NULL; //caso o id nao pertenca a nenhum livro
}



// void imprimeLivrosDaLista(ListaLivros* lista){
//     Celula* aux;
//     for(aux = lista->prim; aux != NULL; aux = aux->prox){
//         //imprimeLivro(aux->livro);
//         imprimeNomeLivro(aux->livro);
//     }
// }



void liberaListaLivros(ListaLivros* lista){
    Celula* atual = lista->prim;
    Celula* seguinte;

    while (atual != NULL) {
        seguinte = atual->prox;
        liberaLivro(atual->livro);
        free(atual);
        atual = seguinte;
    }

    free(lista);
}



void liberaListaLivrosParcialmente(ListaLivros* lista){
    Celula* atual = lista->prim;
    Celula* seguinte;

    while (atual != NULL) {
        seguinte = atual->prox;
        //liberaLivro(atual->livro); //Não Libera o Livro em si
        free(atual);
        atual = seguinte;
    }

    free(lista);
}


