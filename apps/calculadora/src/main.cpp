///<Summary>
///En este archivo se hace el llamado a los métodos de cálculos y recibe los valores en consola
///<Summary>

#include "../include/Calculadora.h"
#include "../include/Potencia.h"
#include <iostream>

int main()
{
    double p1, p2;
    char op;
    // Se crean los objetos de las clases
    Calculadora calc;
    Potencia pot;
    double memoriaArray[100000]; // Arreglo estático para almacenar resultados
    double* memoriaFuga[1000] = {nullptr}; // Arreglo de punteros para simular fugas y picos de memoria
    int operaciones = 0;
    std::size_t índice = 0; // Índice para el array de memoria

    do {
        std::cout << "Elija la ecuacion que se va a realizar: (+ - * / ^): ";
        std::cin >> op;
        std::cout << "Elija el primer numero: ";
        std::cin >> p1;
        std::cout << "Elija el segundo numero: ";
        std::cin >> p2;

        if (op == '^') {
            pot.operadorPotencia(&p1, &p2, op); // Asume que el resultado se guarda en p1 o p2
            std::cout << "Resultado: " << p1 << std::endl; // Imprime el resultado modificado
        } else {
            calc.operación(&p1, &p2, op); // Asume que el resultado se guarda en p1 o p2
            std::cout << "Resultado: " << p1 << std::endl; // Imprime el resultado modificado
        }
        //Aquí se agregan los elementos al array de memoria
        calc.agregarMemoriaArray(memoriaArray, &p1, &índice);

        // Simular asignación de memoria en cada operación
        for (int i = 0; i < 1000; ++i) {
            if (memoriaFuga[i] == nullptr) {
                memoriaFuga[i] = new double[1000];
                break;
            }
        }

        // Simular picos de memoria cada 10 operaciones
        if (operaciones % 10 == 0) {
            for (int i = 0; i < 1000; ++i) {
                if (memoriaFuga[i] == nullptr) {
                    memoriaFuga[i] = new double[100000];
                    break;
                }
            }
        }

        // Simular liberación parcial (fuga) cada 5 operaciones
        if (operaciones % 5 == 0) {
            for (int i = 0; i < 1000; ++i) {
                if (memoriaFuga[i] != nullptr) {
                    delete[] memoriaFuga[i];
                    memoriaFuga[i] = nullptr;
                    break; // Solo liberar uno para simular fuga
                }
            }
        }

        operaciones++;

        std::cout << "Desea realizar otra operacion? (s/n): ";
        std::cin >> op;
    }while (op == 's' || op == 'S');

    // Al final, liberar la memoria restante (opcional, para evitar fugas reales)
    for (int i = 0; i < 1000; ++i) {
        if (memoriaFuga[i] != nullptr) {
            delete[] memoriaFuga[i];
            memoriaFuga[i] = nullptr;
        }
    }
}