#include "lista.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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

void imprimeLista(Lista * lista, void (*imprime)(void*, FILE*), FILE* saida){
    // VAI SER EM ARQUIVO
    Celula * atual;
    atual = lista->prim;

    while(atual){
        imprime(atual->elemento, saida);
        atual = atual->prox;
    }
}

void * retornaElemComMesmoId(Lista* lista, void * chave, int (*compara)(void *, void *)){
    Celula* celula;

    for(celula = lista->prim; celula != NULL; celula = celula->prox){
        if(compara(celula->elemento, chave)){
            return celula->elemento;
        }
    }
  
    return NULL;
}

void retiraElemLista(Lista * lista, void * chave, int (*compara)(void *, void *)){
    Celula* aux;

    for(aux = lista->prim; aux != NULL; aux = aux->prox){
        if(compara(aux->elemento, chave)) break;
    }

    if(aux == lista->prim && aux == lista->ult){
        lista->prim = NULL;
        lista->ult = NULL;
        free(aux);
        return;
    }
    
    if(aux == lista->prim){
        lista->prim = aux->prox;
        lista->prim->ant = NULL;
        free(aux);
        return;
    }
    
    if(aux == lista->ult){
        lista->ult = aux->ant;
        lista->ult->prox = NULL;
        free(aux);
        return;
    }

    aux->prox->ant = aux->ant;
    aux->ant->prox = aux->prox;
    free(aux);
}

Celula * retornaPrimeiraCelulaLista(Lista * lista){
    return lista->prim;
}

