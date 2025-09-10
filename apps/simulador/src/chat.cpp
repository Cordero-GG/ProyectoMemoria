#ifndef PROYECTOMEMORIA_CHAT_H
#define PROYECTOMEMORIA_CHAT_H

#include <string>
#include <map>

// Declaración anticipada
class contactos;

class chat {
private:
    std::map<std::string, contactos*> contacts; // Fuente intencional de memory leaks
    contactos* currentChat;

public:
    chat();
    ~chat();

    void addContact(std::string name);
    void removeContact(const std::string& name);
    void selectChat(const std::string& name);
    void sendMessage(const std::string& message);
    void showContacts() const;
    void showCurrentChat() const;
    bool contactExists(const std::string& name) const;
};

#endif //PROYECTOMEMORIA_CHAT_H