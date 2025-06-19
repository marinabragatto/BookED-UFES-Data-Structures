#include "gostos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct VetorGostos {
    char ** vetor;
    int tamanho; // Esse tamanho é fixo
};

VetorAfinidades *  CriaVetorGostos(int tamanho){
    VetorAfinidades * afinidades;
    afinidades = (VetorAfinidades*)malloc(sizeof(VetorAfinidades));
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

VetorAfinidades * AdicionaGostos(VetorAfinidades * afinidades, char * elemento){

    for(int i  = 0; i < afinidades->tamanho; i++){
        if(afinidades->vetor[i] == NULL){
            
            afinidades->vetor[i] = elemento;
            break;
        }
    }
    return afinidades;
}

VetorAfinidades * LiberaGostos(VetorAfinidades * afinidades){
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

void ImprimeGostos(VetorAfinidades * afinidades){
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