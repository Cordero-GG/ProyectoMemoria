#include "../include/contactos.h"
#include <iostream>
using namespace std;

contactos::contactos(const string& contactName) : name(contactName) {
    cout << "Contacto " << name << " creado." << endl;
}

contactos::~contactos() {
    cout << "Contacto " << name << " siendo destruido." << endl;

    // No liberamos los mensajes para generar memory leaks
}

string contactos::getName() const {
    return name;
}

void contactos::addMessage(const string& message) {
    // Creamos string en heap que no se liberará
    string* newMessage = new string(message);
    messages.push_back(newMessage);
}

void contactos::displayChat() const {
    cout << "\n--- Chat con " << name << " ---" << endl;
    for (const auto& msg : messages) {
        cout << *msg << endl;
    }
    cout << "----------------------------" << endl;
}








