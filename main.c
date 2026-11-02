#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"
#include "booked.h"


int main(int argc, char *argv[]){
    Booked* booked = InicializaBooked();

    FuncionaBooked(booked);
    LiberaBooked(booked);

    return 0; 
}
