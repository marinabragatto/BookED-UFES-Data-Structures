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



int comparaLivrosRecomendados(void* rec, void* livro){
    Recomendacao * recomendacao = (Recomendacao*)rec;
    Livro * l = (Livro*)livro;

    return ((retornaIdLivro(recomendacao->livro) == retornaIdLivro(l)));
}



int comparaRecomendacao(Recomendacao* rec, Livro* livro, int idRecomendador){
    if(comparaLivrosRecomendados(rec, livro)){
        if(rec->recomendador == idRecomendador) return 1;
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
