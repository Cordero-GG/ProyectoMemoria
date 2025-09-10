#include <iostream>
#include <string>
#include "chat.h"

void showMenu() {
    cout << "\n=== SISTEMA DE CHAT ===" << endl;
    cout << "1. Mostrar contactos" << endl;
    cout << "2. Añadir contacto" << endl;
    cout << "3. Eliminar contacto" << endl;
    cout << "4. Seleccionar chat" << endl;
    cout << "5. Enviar mensaje" << endl;
    cout << "6. Mostrar chat actual" << endl;
    cout << "7. Salir" << endl;
    cout << "Selecciona una opción: ";
}

int main() {
    chat chatSystem;
    int choice;
    string input;


    do {
        showMenu();
        cin >> choice;
        cin.ignore(); // Limpiar buffer

        switch (choice) {
            case 1:
                chatSystem.showContacts();
                break;

            case 2:
                cout << "Nombre del nuevo contacto: ";
                getline(cin, input);
                chatSystem.addContact(input);
                break;

            case 3:
                cout << "Nombre del contacto a eliminar: ";
                getline(cin, input);
                chatSystem.removeContact(input);
                break;

            case 4:
                cout << "Seleccionar chat con: ";
                getline(cin, input);
                chatSystem.selectChat(input);
                break;

            case 5:
                cout << "Mensaje: ";
                getline(cin, input);
                chatSystem.sendMessage(input);
                break;

            case 6:
                chatSystem.showCurrentChat();
                break;

            case 7:
                cout << "Saliendo del sistema de chat" << endl;
                break;

            default:
                cout << "Opción inválida." << endl;
        }
    } while (choice != 7);


    return 0;
}


