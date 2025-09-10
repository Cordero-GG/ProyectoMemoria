#ifndef PROYECTOMEMORIA_CONTACTOS_H
#define PROYECTOMEMORIA_CONTACTOS_H
#include <iostream>
#include <vector>
using namespace std;

class contactos
{
private:
    string name;
    vector<string*> messages; // Fuente intencional de memory leaks

public:
    contactos(const string& name);
    ~contactos();

    string getName() const;
    void addMessage(const string& message);
    void displayChat() const;
};


#endif //PROYECTOMEMORIA_CONTACTOS_H
