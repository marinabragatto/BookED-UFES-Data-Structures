#include "lista.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct celula Celula;

struct celula {
    void * elemento;    ///< Ponteiro para o elemento armazenado
    Celula * ant;       ///< Ponteiro para a célula anterior
    Celula * prox;      ///< Ponteiro para a próxima célula
};

struct lista{
    Celula * prim;      ///< Ponteiro para a primeira célula
    Celula * ult;       ///< Ponteiro para a última célula
};


Lista * criaLista(){
    Lista * lista = (Lista*)malloc(sizeof(Lista));
    lista->ult = NULL;
    lista->prim = NULL;

    return lista;
}

void insereElemNoFimDaLista(Lista * lista, void * elemNovo){
    // CASOS
    //1 - Lista Vazia
    //2 - Lista NÃO Vazia
    Celula * nova;
    nova = (Celula*)malloc(sizeof(Celula));
    if(nova == NULL){
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    nova->elemento = elemNovo;
    nova->prox = NULL;
    
    if(lista->prim == NULL &&  lista->ult == NULL){ // 1 - Lista Vazia
        nova->ant  = NULL;
        lista->prim = nova;
        lista->ult = nova;
    }
    else { // 2 - Lista NÃO Vazia
        nova->ant  = lista->ult;
        lista->ult->prox = nova;
        lista->ult = nova;
    }


}

void liberaLista(Lista * lista, void (*libera)(void*)){

    if(lista){
        Celula * atual = lista->prim;
        Celula * seguinte;

        while(atual){
            seguinte = atual->prox;
            libera(atual->elemento);
            free(atual);
            atual = seguinte;
        }

        free(lista);
    }
}

void liberaListaParcialmente(Lista * lista){
    if(lista){
        Celula * atual;
        atual = lista->prim;
        while(atual){
            // NÃO LIBERA O ELEMENTO (leitor), só a célula
            free(atual);
            atual = atual->prox;
        }

        free(lista);
    }
}

void imprimeLista(Lista * lista, void (*imprime)(void*, FILE*), FILE* saida){
    // VAI SER EM ARQUIVO
    Celula * atual;
    atual = lista->prim;

    while(atual){
        imprime(atual->elemento, saida);
        atual = atual->prox;
    }
}

void * retornaElemComMesmoId(Lista* lista, int id, int (*compara)(void *, int)){
    Celula* celula;

    for(celula = lista->prim; celula != NULL; celula = celula->prox){
        if(compara(celula->elemento, id)){
            return celula->elemento;
        }
    }
  
    return NULL;
}