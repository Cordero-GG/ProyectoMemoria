#include "socket_client.h"
#include "config.h"
#include <iostream>
#include <chrono>

#pragma comment(lib, "ws2_32.lib")

SocketClient::SocketClient() : sock(INVALID_SOCKET), connected(false), running(true) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return;
    }
    connect();
    senderThread = std::thread(&SocketClient::sendThread, this);
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
        std::cerr << "Error creating socket." << std::endl;
        return;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PROFILER_SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(PROFILER_SERVER_IP);

    if (::connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to server." << std::endl;
        closesocket(sock);
        sock = INVALID_SOCKET;
        return;
    }

    connected = true;
}

void SocketClient::enqueueMessage(const std::string& message) {
    std::lock_guard<std::mutex> lock(queueMutex);
    messageQueue.push(message);
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

        if (!message.empty() && isConnected()) {
            send(sock, message.c_str(), message.length(), 0);
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