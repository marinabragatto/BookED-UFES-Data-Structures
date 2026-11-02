/**
 * @file booked.h
 * @brief Interface do módulo Booked.
 *
 * Define o tipo abstrato Booked e funções relacionadas à criação,
 * manipulação e liberação da booked.
 *
 * @author Marina Bragatto
 * @author Thais Brandão
 * @date 09/06/2025
 */

#ifndef booked_h
#define booked_h

#include "lista.h"
#include "leitor.h"
#include "livro.h"
#include "recomendacao.h"

typedef struct booked Booked;


/**
 * @brief Inicializa a booked e le os arquivos de entrada, criando as listas de livros e leitores.
 * 
 * @return struct booked inicializada.
 */
Booked* InicializaBooked();


/**
 * @brief Funcao que le e executa os comandos e abre o arquivo de saida para a impressao.
 *
 * @param booked struct booked inicializada.
 * 
 * @pre booked != NULL
 * @post comandos lidos e executados.
 */
void FuncionaBooked(Booked* booked);


/**
 * @brief Libera a booked e suas listas de livros e leitores.
 *
 * @param booked struct booked a ser liberada.
 * 
 * @post booked liberada.
 */
void LiberaBooked(Booked* booked);


/**
 * @brief Funcao que chama as funcoes de execucao dos comandos de acordo com seus ids.
 *
 * @param booked struct booked inicializada.
 * @param idComando id do comando a ser realizado.
 * @param param1 id leitor.
 * @param param2 id livro.
 * @param param3 id leitor.
 * @param saida arquivo de saida.
 * 
 * @pre booked != NULL
 * @post comando executado.
 */
void ExecutaComando(Booked* booked, int idComando, int param1, int param2, int param3, FILE* saida);


/**
 * @brief Imprime a lista de leitores e todas as suas informacoes (sublistas).
 *
 * @param booked struct booked inicializada.
 * @param saida arquivo de saida.
 * 
 * @pre booked != NULL
 * @post leitores e suas informacoes impressos no arquivo de saida.
 */
void ImprimeBooked(Booked* booked, FILE* saida);


/**
 * @brief Le o arquivo que contem as informacoes sobre cada leitor.
 * 
 * @return lista de leitores inicializada e com as afinidades diretas ja conectadas a partir dos gostos de cada leitor.
 * 
 */
Lista * leArquivoLeitores();


/**
 * @brief Le o arquivo que contem as informacoes sobre cada livro.
 * 
 * @return lista de livros inicializada.
 * 
 */
Lista * leArquivoLivros();

#endif