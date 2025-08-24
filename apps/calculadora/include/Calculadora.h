
///<Summary>
///Se declaran los métodos que va a tener la clase Calculadora
///<Summary>

#ifndef PROYECTOMEMORIA_CALCULADORA_H
#define PROYECTOMEMORIA_CALCULADORA_H
#include <array>

typedef std::array<double, 1000000>* punteroArray; // Puntero a un array de 100mil doubles
typedef double* punteroBásico; //Es un "sinónimo" de puntero, lo uso para hacerlo más legible
class Calculadora
{
public:
    Calculadora();
    ~Calculadora(); //Este es el destructor, libera recursos cuando se destruye el objeto
    void operación(punteroBásico a, punteroBásico b, char símbolo);
    void agregarMemoriaArray(punteroArray arreglo, punteroBásico elemento,std::size_t* índice);
};

#endif //PROYECTOMEMORIA_CALCULADORA_H