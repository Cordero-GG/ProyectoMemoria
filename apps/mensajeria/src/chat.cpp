#include "../include/chat.h"
#include <iostream>
#include <algorithm>

#include "../include/contactos.h"
using namespace std;


chat::chat() : currentChat(nullptr) {
    cout << "Sistema de chat inicializado." << endl;
}

chat::~chat() {
    cout << "Sistema de chat siendo destruido." << endl;

    // Solo liberamos algunos contactos, dejamos otros con leaks

    int i = 0;
    for (auto& pair : contacts) {
        if (i % 2 == 0) { // Liberamos solo contactos en posición par
            delete pair.second;
        } else {
            // No liberamos contactos en posición impar
            cout << "LEAK: Contacto " << pair.first
                      << " no fue liberado." << endl;
        }
        i++;
    }
}

void chat::addContact(string name) {
    if (contactExists(name)) {
        cout << "El contacto ya existe." << endl;
        return;
    }

    // Creamos en heap, algunos no se liberarán
    contacts[name] = new contactos(name);
    cout << "Contacto " << name << " añadido." << endl;
}

void chat::removeContact(const string& name) {
    if (!contactExists(name)) {
        cout << "Contacto no encontrado." << endl;
        return;
    }

    // Solo liberamos algunos contactos al eliminarlos
    static int removeCount = 0;
    if (removeCount % 3 == 0) { // Liberamos 1 de cada 3 contactos eliminados
        delete contacts[name];
        cout << "Contacto " << name << " eliminado y liberado." << endl;
    } else {
        // No liberamos memoria al eliminar contacto
        cout << "Contacto " << name
                  << " eliminado pero no liberado." << endl;
    }
    contacts.erase(name);
    removeCount++;

    if (currentChat && currentChat->getName() == name) {
        currentChat = nullptr;
    }
}

void chat::selectChat(const string& name) {
    if (!contactExists(name)) {
        cout << "Contacto no encontrado." << endl;
        return;
    }

    currentChat = contacts[name];
    cout << "Chat con " << name << " seleccionado." << endl;
}

void chat::sendMessage(const string& message) {
    if (!currentChat) {
        cout << "No hay chat seleccionado." << endl;
        return;
    }

    // Mensaje del usuario
    currentChat->addMessage("[Tú]: " + message);

    // Simular respuesta (crea más memory leaks)
    string respuesta = "[Respuesta de " + currentChat->getName() + "]";
    currentChat->addMessage(respuesta);

    cout << "Mensaje enviado a " << currentChat->getName() << endl;
}

void chat::showContacts() const {
    cout << "\n--- Lista de Contactos ---" << endl;
    for (const auto& pair : contacts) {
        cout << "- " << pair.first << endl;
    }
    cout << "--------------------------" << endl;
}

void chat::showCurrentChat() const {
    if (currentChat) {
        currentChat->displayChat();
    } else {
        cout << "No hay chat seleccionado." << endl;
    }
}

bool chat::contactExists(const string& name) const {
    return contacts.find(name) != contacts.end();
}


