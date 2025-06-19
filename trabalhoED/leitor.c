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
    ListaLivros * lidos;
    ListaLivros * desejados;
    ListaLivros * recomendacoes;
    // ListaLeitores * afinidades;
    VetorAfinidades * afinidades;
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
Leitor* criaLeitor(int idleitor, char * nome, VetorAfinidades * VetorAfinidades){// PASSAR COMO PARAMETRO TAMBEM A LISTA CHAR DE AFINIDADES?

    Leitor * leitor = (Leitor*)malloc(sizeof(Leitor));
    leitor->id = idleitor;
    leitor->nome = strdup(nome);
    
    leitor->afinidades = VetorAfinidades;

    leitor->recomendacoes = criaListaLivros();
    leitor->desejados = criaListaLivros();
    leitor->lidos = criaListaLivros();
    
    
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
int comparaIdLeitor(Leitor * leitor, int id){
    if(leitor->id== id){
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
void imprimeleitor(Leitor * leitor){
/*
Leitor: Bob
Lidos: O Nome da Rosa, Garota Exemplar
Desejados: Drácula
Recomendacoes: O Iluminado, A Culpa é das Estrelas
Afinidades: Alice, Clara
*/

    // VAI SER PARA PRINTAR EM UM ARQUIVO... a implementar
    
    printf("Leitor: %s\n", leitor->nome);
    printf("Lidos: ");
    imprimeLivrosDaLista(leitor->lidos);
    // função Thais de imprimir os livros
    printf("\n");
    printf("Desejados:");
    imprimeLivrosDaLista(leitor->desejados);
    printf("\n");
    printf("Recomendacoes: ");
    imprimeLivrosDaLista(leitor->recomendacoes);
    // função Thais de imprimir os livros
    printf("\n");
    printf("Afinidades: ");
    ImprimeAfinidades(leitor->afinidades);
    //  função Marina de imprimir pessoas
    printf("\n\n");

}

/**
 * @brief Libera a memória alocada para o leitor.
 *
 * @param leitor Ponteiro para o leitor.
 * 
 * @pre leitor != NULL
 * @post Memória liberada.
 */
void liberaleitor(Leitor* leitor){
    if(leitor){
        if(leitor->nome){
            free(leitor->nome);
        }
        if(leitor->desejados){
            // funçao thais de liberar parcialmente uma lista
            liberaListaLivrosParcialmente(leitor->desejados);
        }
        if(leitor->lidos){
            // funçao thais de liberar parcialmente uma lista
            liberaListaLivrosParcialmente(leitor->lidos);
        }
        if(leitor->recomendacoes){
            // funçao thais de liberar parcialmente uma lista
            liberaListaLivrosParcialmente(leitor->recomendacoes);
        }
        if(leitor->afinidades){
            LiberaAfinidades(leitor->afinidades);
        }
        free(leitor);
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
        insereLivroNoFimDaLista(leitor->lidos, livro);
        break;
    
    case DESEJADOS:
        insereLivroNoFimDaLista(leitor->desejados, livro);
        break;

    case RECOMENDADOS:
        insereLivroNoFimDaLista(leitor->recomendacoes, livro);
        break;

    default:
        break;
    }
}
