/**
 * @file listaLeitores.c
 * @brief Implementação do módulo de lista de leitores.
 *
 * Este módulo implementa uma lista duplamente encadeada de leitores com célula sentinela,
 * permitindo inserção, leitura de arquivo, liberação e impressão dos leitores.
 *
 * @author Marina Bragatto
 * @author Thais Brandão
 * @date 08/06/2025
 */

#include "listaLeitores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tipo auxiliar para representar as células da lista
typedef struct celula Celula;

struct celula {
    Leitor * leitor;    ///< Ponteiro para o leitor armazenado
    Celula * ant;       ///< Ponteiro para a célula anterior
    Celula * prox;      ///< Ponteiro para a próxima célula
};


/// Estrutura da lista de leitores (lista duplamente encadeada)
struct listaLeitores{
    Celula * prim;      ///< Ponteiro para a primeira célula
    Celula * ult;        ///< Ponteiro para a última célula
};




/**
 * @brief Cria uma nova lista de leitores.
 *
 * A lista é duplamente encadeada com nó sentinela.
 *
 * @return Ponteiro para a lista criada.
 *
 * @pre Nenhuma.
 * @post ListaLeitores inicializada e vazia.
 */
ListaLeitores * criaListaLeitores(){
    ListaLeitores * lista = (ListaLeitores*)malloc(sizeof(ListaLeitores));
    lista->ult = NULL;
    lista->prim = NULL;

    return lista;
}

/**
 * @brief Lê os dados do arquivo "leitores.txt" e cria a lista de leitores.
 *
 * Cada linha do arquivo representa um leitor a ser inserido.
 *
 * @return Ponteiro para a lista preenchida.
 *
 * @pre O arquivo "leitores.txt" deve existir no diretório de execução.
 * @post ListaLeitores inicializada e preenchida com os leitores do arquivo.
 */
ListaLeitores * leArquivoLeitores(){
    /*
    Id;nome;n_afinidades; afinidades
    1;Alice;2;Romance; Terror
    2;Bob;2;Terror;Mistério
    3;Clara;1;Mistério
    */
    ListaLeitores  * lista = criaListaLeitores();
    if(lista == NULL){
        printf("Erro ao Alocar Memória");
        exit(1);
    }

    // Abre efetivamente o arquivo
    FILE * arquivoLeitores;
    char nomeArquivo[200] = "testes/test2/test2/leitores.txt";
    arquivoLeitores = fopen(nomeArquivo, "r");
    if(arquivoLeitores == NULL){
        printf("Erro ao Abrir arquivo Leitores");
        exit(1);
    }

    // Le efetivamente o arquivo
    fscanf(arquivoLeitores,"%*[^\n]\n"); // Descarta o cabeçalho

    // Coisas a serem lidas:
    int id, qtdAfin;
    VetorGostos * VetorGostos;
    char afinididade[TAM_AFINIDADES];
    char nome[TAM_MAX_NOME_LEITOR];
    Leitor * novo;

    while(1){
        if(fscanf(arquivoLeitores, "%d;", &id) == 1){
            fscanf(arquivoLeitores, "%[^;];", nome);

            fscanf(arquivoLeitores,"%d;",&qtdAfin);
            VetorGostos = CriaVetorGostos(qtdAfin);

            for(int i = 0; i < qtdAfin; i++){
                if(i != qtdAfin-1){
                    fscanf(arquivoLeitores,"%[^;];", afinididade);
                }
                else{
                    fscanf(arquivoLeitores,"%[^\n]\n", afinididade);
                }
                //printf("(%s)", afinididade);
                char * pontAfinidade = strdup(afinididade);
                VetorGostos = AdicionaGostos(VetorGostos, pontAfinidade);
            }
            
             // Descarta TEMPORARIAMENTE as afinidades
            novo = criaLeitor(id, nome, VetorGostos);
            //imprimeleitor(novo);
            insereLeitorNoFimDaLista(lista, novo);
        }
        else{ 
            break;
        }
    }
    fclose(arquivoLeitores);

    return lista;

}

/**
 * @brief Insere um leitor no final da lista.
 *
 * @param lista Ponteiro para a lista de leitores.
 * @param leitorNovo Ponteiro para o novo leitor a ser inserido.
 *
 * @pre lista != NULL, leitorNovo != NULL
 * @post leitorNovo inserido ao final da lista.
 */
void insereLeitorNoFimDaLista(ListaLeitores * lista, Leitor * leitorNovo){
    // CASOS
    //1 - Lista Vazia
    //2 - Lista NÃO Vazia
    Celula * nova;
    nova = (Celula*)malloc(sizeof(Celula));
    if(nova == NULL){
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    nova->leitor = leitorNovo;
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


/**
 * @brief Libera a memória de uma lista de leitores, incluindo seus elementos.
 *
 * @param lista Ponteiro para a lista a ser liberada.
 *
 * @pre lista != NULL
 * @post Toda a memória da lista e dos leitores é liberada.
 */
void liberaListaLeitores(ListaLeitores * lista){

    if(lista){
        Celula * atual = lista->prim;
        Celula * seguinte;

        while(atual){
            seguinte = atual->prox;
            liberaleitor(atual->leitor);
            free(atual);
            atual = seguinte;
        }

        free(lista);
    }
}


/**
 * @brief Libera apenas a estrutura da lista, mantendo os leitores.
 *
 * Útil quando os leitores ainda são usados em outro lugar.
 *
 * @param lista Ponteiro para a lista a ser parcialmente liberada.
 *
 * @pre lista != NULL
 * @post A estrutura da lista é liberada, mas os leitores permanecem.
 */
void liberaListaLeitoresParcialmente(ListaLeitores * lista){
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

/**
 * @brief Imprime os leitores presentes na lista.
 *
 * @param lista Ponteiro para a lista de leitores.
 *
 * @pre lista != NULL
 */
void imprimeLeitoresDaLista(ListaLeitores * lista, FILE* saida){
    // VAI SER EM ARQUIVO
    Celula * atual;
    atual = lista->prim;

    while(atual){
        imprimeleitor(atual->leitor, saida);
        atual = atual->prox;
    }
}



Leitor* retornaLeitorComMesmoId(ListaLeitores* leitores, int idLeitor){
    Celula* leitor;

    for(leitor = leitores->prim; leitor != NULL; leitor = leitor->prox){
        if(comparaIdLeitor(leitor->leitor, idLeitor)){
            return leitor->leitor;
        }
    }
    return NULL;
}