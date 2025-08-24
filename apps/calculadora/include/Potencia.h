///<Summary>
/// Se declaran los métodos para poder hacer cálculos con potencias
///<Summary>

#ifndef PROYECTOMEMORIA_POTENCIA_H
#define PROYECTOMEMORIA_POTENCIA_H

typedef float* punteroPotencia;
class Potencia
{
public:
    Potencia();
    ~Potencia();
    void operadorPotencia(punteroPotencia a, punteroPotencia b, char Operando);
};
#endif //PROYECTOMEMORIA_POTENCIA_H