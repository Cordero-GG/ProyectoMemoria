#define USER_SOURCE
#include <profiler.h>
#include <iostream>
#include "Calculadora.h"
#include "Potencia.h"

int main() {
    std::cout << "=== CALCULADORA CON PROFILER ===" << std::endl;

    // Crear algunos números en el heap (algunos con leaks)
    double* num1 = new double(10.5);
    double* num2 = new double(5.2);
    double* num3 = new double(7.8); // Este tendrá leak

    Calculadora calc;

    // Realizar algunas operaciones
    calc.operación(num1, num2, '+');

    // Liberar algunos recursos
    delete num1;
    delete num2;
    // num3 no se libera -> LEAK

    // Crear un arreglo grande (con leak parcial)
    double* arreglo = new double[1000];
    std::size_t indice = 0;

    for (int i = 0; i < 500; i++) {
        double* temp = new double(i * 1.1);
        calc.agregarMemoriaArray(arreglo, temp, &indice);
        if (i % 2 == 0) {
            delete temp; // Liberar algunos
        }
        // Los impares tendrán leak
    }

    // Liberar el arreglo pero no todos sus elementos
    delete[] arreglo;

    std::cout << "Finalizando calculadora..." << std::endl;

    // Reportar memory leaks al finalizar
    Profiler::ReportarMemoryLeaks();

    return 0;
}