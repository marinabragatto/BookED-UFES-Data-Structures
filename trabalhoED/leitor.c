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
    // ListaLeitores * afinidades;
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
Leitor* criaLeitor(int idleitor, char * nome, Lista * Gostos){// PASSAR COMO PARAMETRO TAMBEM A LISTA CHAR DE AFINIDADES?

    Leitor * leitor = (Leitor*)malloc(sizeof(Leitor));
    leitor->id = idleitor;
    leitor->nome = strdup(nome);
    
    leitor->gostos = Gostos;

    leitor->recomendacoes = criaLista();
    leitor->desejados = criaLista();
    leitor->lidos = criaLista();
    
    
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
int comparaIdLeitor(void * leitor, int id){

   
    if( (((Leitor*)leitor)->id) == id ){
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
/*
Leitor: Bob
Lidos: O Nome da Rosa, Garota Exemplar
Desejados: Drácula
Recomendacoes: O Iluminado, A Culpa é das Estrelas
Afinidades: Alice, Clara
*/

    // VAI SER PARA PRINTAR EM UM ARQUIVO... a implementar
    Leitor * l = (Leitor*)leitor;

    fprintf(saida, "Leitor: %s\n", l->nome);
    fprintf(saida, "Lidos: ");
    imprimirLivrosLeitor(l->lidos, saida);
    // função Thais de imprimir os livros
    fprintf(saida, "\n");
    fprintf(saida, "Desejados: ");
    imprimirLivrosLeitor(l->desejados, saida);
    fprintf(saida, "\n");
    fprintf(saida, "Recomendacoes: ");
    imprimirLivrosLeitor(l->recomendacoes, saida);
    // função Thais de imprimir os livros
    fprintf(saida, "\n");
    fprintf(saida, "Afinidades: ");
    ImprimeGostos(l->gostos, saida);
    //  função Marina de imprimir pessoas
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
    retiraElemLista(leitor->recomendacoes, retornaIdLivro(livro), comparaIdLivro);
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
    switch (lista){
    case LIDOS:
        l = retornaElemComMesmoId(leitor->lidos, retornaIdLivro(livro), comparaIdLivro);
        break;
    
    case DESEJADOS:
        l = retornaElemComMesmoId(leitor->desejados, retornaIdLivro(livro), comparaIdLivro);
        break;

    case RECOMENDADOS:
        l = retornaElemComMesmoId(leitor->recomendacoes, retornaIdLivro(livro), comparaIdLivro);
        break;

    default:
        break;
    }

    return (l != NULL);
}

Lista* LivrosEmComumLeitores(Leitor * leitor1, Leitor * leitor2){

    Celula * lidosL1 = retornaPrimeiraCelulaLista(leitor1->lidos);
    Livro * livro = lidosL1->elemento;
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
    
    
   // verificaLivroEstaNaListaLeitor(leitor2, Livro* livro, LIDOS);
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
    printf("\n");
}