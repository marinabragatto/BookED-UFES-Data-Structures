#ifndef booked_h
#define booked_h

#include "listaLivros.h"
#include "listaLeitores.h"

typedef struct booked Booked;

Booked* InicializaBooked();
void FuncionaBooked(Booked* booked);
void LiberaBooked(Booked* booked);
void ExecutaComando(Booked* booked, int idComando, int param1, int param2, int param3, FILE* saida);
void ImprimeBooked(Booked* booked, FILE* saida);

#endif