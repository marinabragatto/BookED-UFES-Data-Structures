#ifndef booked_h
#define booked_h

#include "lista.h"
#include "leitor.h"
#include "livro.h"
#include "recomendacao.h"

typedef struct booked Booked;

Booked* InicializaBooked();
void FuncionaBooked(Booked* booked);
void LiberaBooked(Booked* booked);
void ExecutaComando(Booked* booked, int idComando, int param1, int param2, int param3, FILE* saida);
void ImprimeBooked(Booked* booked, FILE* saida);
Lista * leArquivoLeitores();
Lista * leArquivoLivros();

#endif