///<Summary>
///En este archivo se hace el llamado a los métodos de cálculos y recibe los valores en consola
///<Summary>

#include "Calculadora.h"
#include "Potencia.h"
#include <iostream>

int main()
{
    double p1, p2;
    char op;
    // Se crean los objetos de las clases
    Calculadora calc;
    Potencia pot;
    std::array<double , 1000000> memoriaArray; // Array para almacenar resultados
    std::size_t índice = 0; // Índice para el array de memoria

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
        //Aquí se agregan los elementos al array de memoria
        calc.agregarMemoriaArray(&memoriaArray, &p1, &índice);

        std::cout << "¿Desea realizar otra operación? (s/n): ";
        std::cin >> op;
    }while (op == 's' || op == 'S');
}