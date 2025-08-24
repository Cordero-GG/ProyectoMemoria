///<Summary>
///Se agrega la lógica de la clase que se encarga de las ecuaciones con potencias
///<Summary>

#include "Potencia.h"
#include <cmath>
#include <iostream>
Potencia::Potencia(){}
Potencia::~Potencia(){}

void Potencia::operadorPotencia(punteroPotencia a, punteroPotencia b, char Operando)
{
    *a = pow(*a, *b);
}

