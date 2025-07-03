/**
 * @file leitor.c
 * @brief Implementação das funções relacionadas ao tipo Leitor.
 *
 * Este arquivo contém a implementação das funções para criação, manipulação
 * e liberação de leitores no sistema.
 *
 * @author Marina Bragatto
 * @author Thais Brandão
 * @date 09/06/2025
 */

#include "leitor.h"

struct leitor {
    int id;
    char * nome;
    Lista * lidos;
    Lista * desejados;
    Lista * recomendacoes;
    Lista * afinidadesDiretas;
    Lista * gostos;
};



Leitor* criaLeitor(int idleitor, char * nome, Lista * Gostos){

    Leitor * leitor = (Leitor*)malloc(sizeof(Leitor));
    leitor->id = idleitor;
    leitor->nome = strdup(nome);
    
    leitor->gostos = Gostos;

    leitor->recomendacoes = criaLista();
    leitor->desejados = criaLista();
    leitor->lidos = criaLista();
    leitor->afinidadesDiretas = criaLista();
    
    
    return leitor;
}



int comparaIdLeitor(void * leitor, void * id){

    if( (((Leitor*)leitor)->id) == *((int*)id)){
        return 1;
    }
    return 0;
}



int retornaIdleitor(Leitor * leitor){
    return leitor->id;
}



void imprimeleitor(void * leitor, FILE* saida){
    Leitor * l = (Leitor*)leitor;

    fprintf(saida, "Leitor: %s\n", l->nome);

    fprintf(saida, "Lidos: ");
    imprimirLivrosLeitor(l->lidos, saida);
    fprintf(saida, "\n");

    fprintf(saida, "Desejados: ");
    imprimirLivrosLeitor(l->desejados, saida);
    fprintf(saida, "\n");

    fprintf(saida, "Recomendacoes: ");
    imprimeRecomendacoes(l->recomendacoes, saida);
    fprintf(saida, "\n");

    fprintf(saida, "Afinidades: ");
    imprimirLeitores(l->afinidadesDiretas, saida);
    fprintf(saida, "\n");
//ImprimeGostos(l->gostos, saida);
    fprintf(saida, "\n");

}



void imprimeNomeLeitor(Leitor * leitor, FILE* saida){
    fprintf(saida, "%s", leitor->nome);
}



void liberaleitor(void * leitor){

    Leitor * l = (Leitor*)leitor;

    if(l){
        if(l->nome){
            free(l->nome);
        }
        if(l->desejados){
            // funçao thais de liberar parcialmente uma lista
            liberaListaParcialmente(l->desejados);
        }
        if(l->lidos){
            // funçao thais de liberar parcialmente uma lista
            liberaListaParcialmente(l->lidos);
        }
        if(l->recomendacoes){
            // funçao thais de liberar parcialmente uma lista
            liberaLista(l->recomendacoes, liberaRec);
        }
        if(l->gostos){
            liberaLista(l->gostos, free);
        }
        if(l->afinidadesDiretas){
            liberaListaParcialmente(l->afinidadesDiretas);
        }
        free(l);
    }
}



void insereLivroNaListaLeitor(Leitor* leitor, Livro* livro, int lista){
    switch (lista){
    case LIDOS:
        insereElemNoFimDaLista(leitor->lidos, livro);
        break;
    
    case DESEJADOS:
        insereElemNoFimDaLista(leitor->desejados, livro);
        break;

    default:
        break;
    }
}



void insereRecomendacaoNaListaLeitor(Leitor* leitor, Recomendacao* recomendacao){
    insereElemNoFimDaLista(leitor->recomendacoes, recomendacao);
}



int verfificaRecomendacaoExiste(Leitor* leitor, Livro* livro, int idRecomendador){
    Recomendacao* comparacao = criaRecomendacao(idRecomendador, livro);
    Celula* aux = retornaPrimeiraCelulaLista(leitor->recomendacoes);
    for(aux; aux != NULL; aux = aux->prox){
        if(comparaRecomendacao(aux->elemento, comparacao)){
            liberaRec(comparacao);
            return 1;
        }
    }
    liberaRec(comparacao);
    return 0;
}



void retiraLivroDaListaLeitor(Leitor* leitor, Livro* livro){
    int id = retornaIdLivro(livro);
    retiraElemLista(leitor->recomendacoes, &id , comparaIdLivro);
}



void retiraRecomendacaoLeitor(Leitor* leitor, Livro* livro, int idRecomendador){
    Recomendacao* comparacao = criaRecomendacao(idRecomendador, livro);
    Celula* aux = retornaPrimeiraCelulaLista(leitor->recomendacoes);
    
    Recomendacao* rec;
    for(aux; aux != NULL; aux = aux->prox){
        if(comparaRecomendacao(aux->elemento, comparacao))
        rec = retornaRecomendacao(aux->elemento);  
        break;
    }
    retiraElemLista(leitor->recomendacoes, rec, comparaRecomendacao);
    liberaRec(rec);
    liberaRec(comparacao);
}



int verificaLivroEstaNaListaLeitor(Leitor* leitor, Livro* livro, int lista){
    Livro* l;
    int id = retornaIdLivro(livro);
    switch (lista){
    case LIDOS:
        l = retornaElemComMesmoId(leitor->lidos, &id , comparaIdLivro);
        break;
    
    case DESEJADOS:
        l = retornaElemComMesmoId(leitor->desejados, &id, comparaIdLivro);
        break;

    default:
        break;
    }

    return (l != NULL);
}



Lista* LivrosEmComumLeitores(Leitor * leitor1, Leitor * leitor2){

    Celula * lidosL1 = retornaPrimeiraCelulaLista(leitor1->lidos);
    Livro * livro;
    int qtd = 0;

    // Criação de uma lista (apenas para fim de printar ela) que contém os livros lidos em comum
    Lista * comum = criaLista();

    while(lidosL1){
        livro = lidosL1->elemento;
        if(verificaLivroEstaNaListaLeitor(leitor2, livro, LIDOS)){
            insereElemNoFimDaLista(comum, livro);
            qtd++;
        }
        lidosL1 = lidosL1->prox;  
    }


    if(qtd > 0){
        return comum;
    }
    liberaListaParcialmente(comum);
    return NULL;
    
}



void imprimirLivrosLeitor(Lista * lista, FILE * saida){

    Celula* aux = retornaPrimeiraCelulaLista(lista);

    for(; aux != NULL; aux = aux->prox){
        imprimeNomeLivro(aux->elemento, saida, SEM_ASPAS);
        if(aux->prox != NULL){
            fprintf(saida, ", ");
        }
    }
}



void imprimeRecomendacoes(Lista* recomendacoes, FILE* saida){
    Celula* aux = retornaPrimeiraCelulaLista(recomendacoes);

    for(; aux != NULL; aux = aux->prox){
        imprimeRecomendacao(aux->elemento, saida);
        if(aux->prox != NULL){
            fprintf(saida, ", ");
        }
    }
}




void ImprimeGostos(Lista * gostos, FILE* saida){ 
    Celula* aux = retornaPrimeiraCelulaLista(gostos);

    for(; aux != NULL; aux = aux->prox){
        fprintf(saida,"%s", (char*)aux->elemento);
        //(aux->elemento, saida, SEM_ASPAS);
        if(aux->prox != NULL){
            fprintf(saida, ", ");
        }
    }
    fprintf(saida,"\n");
}



void ConectaAfinidadesDireta(Lista * leitores){
    Celula * leitorCel1 = retornaPrimeiraCelulaLista(leitores); // Recebe célula do primeiro leitor da lista 
    Leitor * leitor1; // Recebe o primeiro leitor

    
    Celula * leitorCel2 = retornaPrimeiraCelulaLista(leitores); // Recebe célula do primeiro leitor da lista 
    Leitor * leitor2; // Recebe o primeiro leitor

    while(leitorCel1){
        leitor1 = leitorCel1->elemento;

        while(leitorCel2){
            leitor2 = leitorCel2->elemento;
            if(leitor2 != leitor1 && !verificaAfinidadeJaExiste(leitor2, leitor1)){
                if(verificaCompatibilidade(leitor2, leitor1)){
                    insereElemNoFimDaLista(leitor1->afinidadesDiretas, leitor2);
                    insereElemNoFimDaLista(leitor2->afinidadesDiretas, leitor1);
                }
            }
            leitorCel2 = leitorCel2->prox;
        }
        
        leitorCel2 = retornaPrimeiraCelulaLista(leitores);
        leitorCel1 = leitorCel1->prox;
        
    }
}



int verificaCompatibilidade(Leitor * leitor2, Leitor * leitor1){
    Celula * gostoCel1 = retornaPrimeiraCelulaLista(leitor1->gostos); // Recebe a célula da lista de gostos, do primeiro leitor
    char * gosto1; // Recebe primeiro gosto

    Celula * gostoCel2 = retornaPrimeiraCelulaLista(leitor2->gostos); // Recebe a célula da lista de gostos, do primeiro leitor
    char * gosto2; // Recebe primeiro gosto
    
    while(gostoCel1){
        gosto1 = gostoCel1->elemento;
        
        while(gostoCel2){
            gosto2 = gostoCel2->elemento;
            if(!strcmp(gosto1, gosto2)){
                return 1;
            }
            gostoCel2 = gostoCel2->prox;
        }
        gostoCel2 = retornaPrimeiraCelulaLista(leitor2->gostos);
        gostoCel1 = gostoCel1->prox;
    }

    return 0;

}



int verificaAfinidadeJaExiste(Leitor * leitor1, Leitor * leitor2){
    Leitor * leitor = retornaElemComMesmoId(leitor1->afinidadesDiretas, leitor2, comparaDoisLeitores);
    return (leitor != NULL);
}



int comparaDoisLeitores(void * leitor2, void * leitor1){
    if(leitor1 == leitor2){
        return 1;
    }
    return 0;

}



void imprimirLeitores(Lista * leitores, FILE * saida){
    Celula* aux = retornaPrimeiraCelulaLista(leitores);
    Leitor * leitor;

    for(; aux != NULL; aux = aux->prox){
        leitor = aux->elemento;
        imprimeNomeLeitor(leitor, saida);
        if(aux->prox != NULL){
            fprintf(saida, ", ");
        }
    }
}



int ConectaAfinidadesIndireta(Leitor * origem, Leitor * destino, Lista * visitados){
    insereElemNoFimDaLista(visitados, origem);

    if(verificaAfinidadeJaExiste(origem, destino)){
        return 1;
    }
    else{
        Celula * celulaAfinidade = retornaPrimeiraCelulaLista(origem->afinidadesDiretas);
        Leitor * leitor;
        
        while(celulaAfinidade){
            leitor = celulaAfinidade->elemento;

            if(!retornaElemComMesmoId(visitados,leitor, comparaDoisLeitores)){
                if(ConectaAfinidadesIndireta(leitor,destino,visitados)){
                    return 1;
                }
            }

            celulaAfinidade = celulaAfinidade->prox;
        }
    }

    return 0;
}