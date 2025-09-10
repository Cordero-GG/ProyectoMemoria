#include <iostream>
#include <chrono>
#include "socket_client.h"
#include "config.h"

#pragma comment(lib, "ws2_32.lib")

SocketClient::SocketClient() : sock(INVALID_SOCKET), connected(false), running(true) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return;
    }
    connect();
    senderThread = std::thread(&SocketClient::sendThread, this);

    // Mensajes de depuración
    if (connected) {
        std::cout << "SocketClient: Conectado al servidor en "
                  << PROFILER_SERVER_IP << ":" << PROFILER_SERVER_PORT << std::endl;
    } else {
        std::cout << "SocketClient: No se pudo conectar al servidor. "
                  << "Los datos se enviarán cuando el servidor esté disponible." << std::endl;
    }
}

SocketClient::~SocketClient() {
    stop();
    if (senderThread.joinable()) {
        senderThread.join();
    }
    closesocket(sock);
    WSACleanup();
}

SocketClient& SocketClient::getInstance() {
    static SocketClient instance;
    return instance;
}

void SocketClient::connect() {
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
        return;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PROFILER_SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(PROFILER_SERVER_IP);

    if (::connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to server: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        sock = INVALID_SOCKET;
        return;
    }

    connected = true;
    std::cout << "Conexión exitosa al servidor." << std::endl;
}

void SocketClient::enqueueMessage(const std::string& message) {
    std::lock_guard<std::mutex> lock(queueMutex);
    messageQueue.push(message);
    std::cout << "Mensaje encolado: " << message.substr(0, 50) << "..." << std::endl;
}

void SocketClient::sendThread() {
    while (running) {
        std::string message;
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            if (!messageQueue.empty()) {
                message = messageQueue.front();
                messageQueue.pop();
            }
        }

        if (!message.empty()) {
            if (isConnected()) {
                int result = send(sock, message.c_str(), message.length(), 0);
                if (result == SOCKET_ERROR) {
                    std::cerr << "Error al enviar mensaje: " << WSAGetLastError() << std::endl;
                    connected = false;
                    // Intentar reconectar
                    connect();
                } else {
                    std::cout << "Mensaje enviado (" << result << " bytes)" << std::endl;
                }
            } else {
                // Intentar reconectar si no está conectado
                connect();
                // Re-encolar el mensaje si no se pudo enviar
                if (!isConnected()) {
                    std::lock_guard<std::mutex> lock(queueMutex);
                    messageQueue.push(message);
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

bool SocketClient::isConnected() const {
    return connected && sock != INVALID_SOCKET;
}

void SocketClient::stop() {
    running = false;
}