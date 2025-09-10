#define USER_SOURCE
#include <profiler.h>
#include <iostream>
#include <string>
#include "../include/chat.h"

void showMenu() {
    std::cout << "\n=== SISTEMA DE CHAT ===" << std::endl;
    std::cout << "1. Mostrar contactos" << std::endl;
    std::cout << "2. Añadir contacto" << std::endl;
    std::cout << "3. Eliminar contacto" << std::endl;
    std::cout << "4. Seleccionar chat" << std::endl;
    std::cout << "5. Enviar mensaje" << std::endl;
    std::cout << "6. Mostrar chat actual" << std::endl;
    std::cout << "7. Salir" << std::endl;
    std::cout << "Selecciona una opción: ";
}

int main() {
    chat chatSystem;
    int choice;
    std::string input;

    do {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(); // Limpiar buffer

        switch (choice) {
            case 1:
                chatSystem.showContacts();
                break;

            case 2:
                std::cout << "Nombre del nuevo contacto: ";
                std::getline(std::cin, input);
                chatSystem.addContact(input);
                break;

            case 3:
                std::cout << "Nombre del contacto a eliminar: ";
                std::getline(std::cin, input);
                chatSystem.removeContact(input);
                break;

            case 4:
                std::cout << "Seleccionar chat con: ";
                std::getline(std::cin, input);
                chatSystem.selectChat(input);
                break;

            case 5:
                std::cout << "Mensaje: ";
                std::getline(std::cin, input);
                chatSystem.sendMessage(input);
                break;

            case 6:
                chatSystem.showCurrentChat();
                break;

            case 7:
                std::cout << "Saliendo del sistema de chat" << std::endl;
                break;

            default:
                std::cout << "Opción inválida." << std::endl;
        }
    } while (choice != 7);

    // Reportar memory leaks al finalizar
    Profiler::ReportarMemoryLeaks();

    return 0;
}