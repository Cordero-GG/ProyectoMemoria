///<Summary>
///Se declaran los métodos que va a tener la clase Calculadora
///<Summary>

#ifndef PROYECTOMEMORIA_CALCULADORA_H
#define PROYECTOMEMORIA_CALCULADORA_H

#include <cstddef>

typedef double* punteroArray; // Puntero a un arreglo de doubles
typedef double* punteroBasico; //Es un "sinónimo" de puntero, lo uso para hacerlo más legible
class Calculadora
{
public:
    Calculadora();
    ~Calculadora(); //Este es el destructor, libera recursos cuando se destruye el objeto
    void operación(punteroBasico a, punteroBasico b, char símbolo);
    void agregarMemoriaArray(punteroArray arreglo, punteroBasico elemento, std::size_t* indice);
};

#endif //PROYECTOMEMORIA_CALCULADORA_H