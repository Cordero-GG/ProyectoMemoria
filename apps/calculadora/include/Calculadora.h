
///<Summary>
///Se declaran los métodos que va a tener la clase Calculadora
///<Summary>

#ifndef PROYECTOMEMORIA_CALCULADORA_H
#define PROYECTOMEMORIA_CALCULADORA_H

typedef float* punteroBásico; //Es un "sinónimo" de puntero, lo uso para hacerlo más legible
class Calculadora
{
public:
    Calculadora();
    ~Calculadora(); //Este es el destructor, libera recursos cuando se destruye el objeto
    void operación(punteroBásico a, punteroBásico b, char símbolo);
};
#endif //PROYECTOMEMORIA_CALCULADORA_H