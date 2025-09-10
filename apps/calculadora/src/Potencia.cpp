#define USER_SOURCE
#include "../../profiler_lib/profiler.h"
#include "Potencia.h"
#include <iostream>
#include <cmath>

Potencia::Potencia() {
    std::cout << "Calculadora de potencias inicializada." << std::endl;
}

Potencia::~Potencia() {
    std::cout << "Calculadora de potencias finalizada." << std::endl;
}

void Potencia::operadorPotencia(punteroPotencia a, punteroPotencia b, char Operando) {
    if (Operando == '^') {
        *a = std::pow(*a, *b);
        std::cout << "Resultado de la potencia: " << *a << std::endl;
    } else {
        std::cout << "Operador no válido para potencia." << std::endl;
    }
}