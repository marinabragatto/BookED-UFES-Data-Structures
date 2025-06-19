#include "gostos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct VetorGostos {
    char ** vetor;
    int tamanho; // Esse tamanho é fixo
};

VetorGostos *  CriaVetorGostos(int tamanho){
    VetorGostos * afinidades;
    afinidades = (VetorGostos*)malloc(sizeof(VetorGostos));
    if(afinidades == NULL){
        printf("Erro ao alocar memória\n");
        exit(1);
    }

    afinidades->vetor = (char**)malloc(sizeof(char*)*tamanho);
    
    afinidades->tamanho = tamanho;

    if(afinidades->vetor == NULL){
        printf("Erro ao alocar memória\n");
        exit(1);
    }
    for(int i = 0; i < tamanho; i++){
        afinidades->vetor[i] = NULL;
    }

    return afinidades;

}

VetorGostos * AdicionaGostos(VetorGostos * afinidades, char * elemento){

    for(int i  = 0; i < afinidades->tamanho; i++){
        if(afinidades->vetor[i] == NULL){
            
            afinidades->vetor[i] = elemento;
            break;
        }
    }
    return afinidades;
}

VetorGostos * LiberaGostos(VetorGostos * afinidades){
    if(afinidades){
        if(afinidades->vetor){
            for(int i = 0; i < afinidades->tamanho; i++){
                if(afinidades->vetor[i]){
                    free(afinidades->vetor[i]);
                }
            }
            free(afinidades->vetor);
        }
        free(afinidades);
    }
}

void ImprimeGostos(VetorGostos * afinidades){
    for(int i = 0; i < afinidades->tamanho; i++){
        printf("%s", afinidades->vetor[i]);
        if(i != afinidades->tamanho -1){
            printf(", ");
        }
        else{
            printf("\n");
        }
       
    }
}