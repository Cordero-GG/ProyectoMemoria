///<Summary>
///En este archivo se hace el llamado a los métodos de cálculos y recibe los valores en consola
///<Summary>

#include "Calculadora.h"
#include "Potencia.h"
#include <iostream>

int main()
{
    float p1, p2, resultado;
    char op;
    Calculadora calc;
    Potencia pot;


    do {
        std::cout << "Elija la ecuación que se va a realizar: (+ - * / ^): ";
        std::cin >> op;
        std::cout << "Elija el primer número: ";
        std::cin >> p1;
        std::cout << "Elija el segundo número: ";
        std::cin >> p2;

        if (op == '^') {
            pot.operadorPotencia(&p1, &p2, op); // Asume que el resultado se guarda en p1 o p2
            std::cout << "Resultado: " << p1 << std::endl; // Imprime el resultado modificado
        } else {
            calc.operación(&p1, &p2, op); // Asume que el resultado se guarda en p1 o p2
            std::cout << "Resultado: " << p1 << std::endl; // Imprime el resultado modificado
        }
        std::cout << "¿Desea realizar otra operación? (s/n): ";
        std::cin >> op;
    } while (op == 's' || op == 'S');
}