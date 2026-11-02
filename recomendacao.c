/**
 * @file recomendacao.c
 * @brief Implementação das funções relacionadas ao tipo Recomendacao.
 *
 * Este arquivo contém a implementação das funções para criação, manipulação
 * e liberação de recomendacoes no sistema.
 *
 * @author Marina Bragatto
 * @author Thais Brandão
 * @date 09/06/2025
 */

#include "recomendacao.h"
#include "livro.h"

struct recomendacao{
    int recomendador;
    Livro* livro;
};



Recomendacao * criaRecomendacao(int recomendador, Livro* livro){
    Recomendacao* rec = malloc(sizeof(struct recomendacao));
    rec->recomendador = recomendador;
    rec->livro = livro;
    return rec;
}



int comparaRecomendacao(void* rec, void* comp){
    Recomendacao * recomendacao = retornaRecomendacao(rec);
    Recomendacao * comparacao = retornaRecomendacao(comp);

    if ((retornaIdLivro(recomendacao->livro) == retornaIdLivro(comparacao->livro))){
        if(recomendacao->recomendador == comparacao->recomendador) return 1;
    }
    return 0;
}



void liberaRec(void* recomendacao){
    Recomendacao* rec = (Recomendacao*)recomendacao;
    if(rec != NULL) free(rec);
}



void imprimeRecomendacao(Recomendacao* rec, FILE* saida){
    imprimeLivro(rec->livro, saida);
}



Recomendacao* retornaRecomendacao(void* rec){
    Recomendacao* recomendacao = (Recomendacao*)rec;
    return recomendacao;
}
