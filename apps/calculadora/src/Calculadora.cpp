///<Summary>
///Se define la clase de calculadora, y la lógica de los métodos
///<Summary>

#include "Calculadora.h"
#include <iostream>

Calculadora::Calculadora(){}
Calculadora::~Calculadora(){}

void Calculadora::operación(punteroBásico a, punteroBásico b, char símbolo)
{
    switch (símbolo)
    {
        case '+': *a += *b; break;
        case '-': *a -= *b; break;
        case '*': *a *= *b; break;
        case '/':
            if (*b !=0) *a /= *b;
            else std::cout<<"No se pueden hacer diviciones entre 0";
        break;
    default:
        std::cout<<"El símbolo ingresado no es válido";
    }
    std::cout<<"El resultado es: "<<*a;
}


