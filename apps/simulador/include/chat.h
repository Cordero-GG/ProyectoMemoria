#ifndef PROYECTOMEMORIA_CHAT_H
#define PROYECTOMEMORIA_CHAT_H
#include <iostream>
#include <map>
using namespace std;
class contactos;

class chat {

private:
    map<string, contactos*> contacts; // Fuente intencional de memory leaks
    contactos* currentChat;

public:
    chat();
    ~chat();

    void addContact(string name);
    void removeContact(const string& name);
    void selectChat(const string& name);
    void sendMessage(const string& message);
    void showContacts() const;
    void showCurrentChat() const;
    bool contactExists(const string& name) const;

};


#endif //PROYECTOMEMORIA_CHAT_H
