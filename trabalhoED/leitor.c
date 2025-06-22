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


/**
 * @brief Cria um novo leitor.
 *
 * Aloca e inicializa um novo leitor com o ID e nome fornecidos.
 *
 * @param idleitor ID numérico do leitor.
 * @param nome Nome do leitor.
 * @return Ponteiro para o leitor criado.
 * 
 * @pre idleitor >= 0, nome != NULL
 * @post Leitor criado e inicializado.
 */
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

/**
 * @brief Compara o ID fornecido com o ID de um leitor.
 *
 * Verifica se o ID passado corresponde ao ID do leitor fornecido.
 *
 * @param leitor Ponteiro para o leitor.
 * @param id ID a ser comparado.
 * @return 1 se o ID pertencer ao leitor, 0 caso contrário.
 * 
 * @pre leitor != NULL
 * @post Retorna 0 ou 1.
 */
int comparaIdLeitor(void * leitor, void * id){

    if( (((Leitor*)leitor)->id) == *((int*)id)){
        return 1;
    }
    return 0;
}

/**
 * @brief Retorna o ID de um leitor.
 *
 * @param leitor Ponteiro para o leitor.
 * @return ID do leitor.
 * 
 * @pre leitor != NULL
 * @post Retorna um número inteiro.
 */
int retornaIdleitor(Leitor * leitor){
    return leitor->id;
}

/**
 * @brief Imprime informações do leitor.
 *
 * @param leitor Ponteiro para o leitor.
 * 
 * @pre leitor != NULL
 */
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
    imprimirLivrosLeitor(l->recomendacoes, saida);
    fprintf(saida, "\n");

    fprintf(saida, "Afinidades: ");
    imprimirLeitores(l->afinidadesDiretas, saida);
    fprintf(saida, "\n");
//ImprimeGostos(l->gostos, saida);
    fprintf(saida, "\n");

}



/**
 * @brief Imprime o nome do leitor no arquivo de saida.
 *
 * @param leitor Ponteiro para o leitor.
 * 
 * @pre leitor != NULL
 */
void imprimeNomeLeitor(Leitor * leitor, FILE* saida){
    fprintf(saida, "%s", leitor->nome);
}



/**
 * @brief Libera a memória alocada para o leitor.
 *
 * @param leitor Ponteiro para o leitor.
 * 
 * @pre leitor != NULL
 * @post Memória liberada.
 */
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
            liberaListaParcialmente(l->recomendacoes);
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



/**
 * @brief Insere um livro em uma lista especifica do leitor.
 *
 * @param leitor Ponteiro para o leitor.
 * @param livro Ponteiro para o livro.
 * @param lista inteiro que identifica se eh lista de lidos ou de desejados.
 * 
 * @pre leitor != NULL, livro != NULL
 * @post Livro inserido na lista especificada.
 */
void insereLivroNaListaLeitor(Leitor* leitor, Livro* livro, int lista){
    switch (lista){
    case LIDOS:
        insereElemNoFimDaLista(leitor->lidos, livro);
        break;
    
    case DESEJADOS:
        insereElemNoFimDaLista(leitor->desejados, livro);
        break;

    case RECOMENDADOS:
        insereElemNoFimDaLista(leitor->recomendacoes, livro);
        break;

    default:
        break;
    }
}


/**
 * @brief Retira um livro de uma lista de recomendacoes do leitor.
 *
 * @param leitor Ponteiro para o leitor.
 * @param livro Ponteiro para o livro.
 * 
 * @pre leitor != NULL, livro != NULL
 * @post Livro inserido na lista especificada.
 */
void retiraLivroDaListaLeitor(Leitor* leitor, Livro* livro){
    int id = retornaIdLivro(livro);
    retiraElemLista(leitor->recomendacoes, &id , comparaIdLivro);
}



/**
 * @brief Verifica se um livro ja se encontra em uma lista especifica do leitor.
 *
 * @param leitor Ponteiro para o leitor.
 * @param livro Ponteiro para o livro.
 * @param lista inteiro que identifica qual a lista.
 * 
 * @pre leitor != NULL, livro != NULL
 * @post inteiro indicando ou nao a existencia do livro na lista.
 */
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

    case RECOMENDADOS:
        l = retornaElemComMesmoId(leitor->recomendacoes, &id, comparaIdLivro);
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

//Compara dois leitores por meio da verificação de ponteiros iguais
int comparaDoisLeitores(void * leitor2, void * leitor1){
    if(leitor1 == leitor2){
        return 1;
    }
    return 0;

}

//Imprime o nome de cada leitor separado por vírgulas
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