#include "funcionalidades.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct VetorAfinidades {
    char ** vetor;
    int tamanho; // Esse tamanho é fixo
};

VetorAfinidades *  CriaVetorAfinidades(int tamanho){
    VetorAfinidades * afinidades;
    afinidades = (VetorAfinidades*)malloc(sizeof(VetorAfinidades));
    if(afinidades == NULL){
        printf("Erro ao alocar memória\n");
        exit(1);
    }

    afinidades->vetor  = (char**)malloc(sizeof(char*)*tamanho);
    if(afinidades->vetor == NULL){
        printf("Erro ao alocar memória\n");
        exit(1);
    }
    for(int i = 0; i < tamanho; i++){
        afinidades->vetor[i] = NULL;
    }

    return afinidades;

}

VetorAfinidades * AdicionaElemento(VetorAfinidades * afinidades, char * elemento){

    for(int i  = 0; i < afinidades->tamanho; i++){
        if(afinidades->vetor[i] == NULL){
            afinidades->vetor[i] = elemento;
        }
    }

}