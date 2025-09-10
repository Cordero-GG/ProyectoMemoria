#ifndef PROYECTOMEMORIA_CONTACTOS_H
#define PROYECTOMEMORIA_CONTACTOS_H

#include <string>
#include <vector>

class contactos {
private:
    std::string name;
    std::vector<std::string*> messages; // Fuente intencional de memory leaks

public:
    contactos(const std::string& name);
    ~contactos();

    std::string getName() const;
    void addMessage(const std::string& message);
    void displayChat() const;
};

#endif //PROYECTOMEMORIA_CONTACTOS_H