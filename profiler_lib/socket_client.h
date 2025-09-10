#ifndef PROYECTOMEMORIA_SOCKET_CLIENT_H
#define PROYECTOMEMORIA_SOCKET_CLIENT_H


#pragma once
#include <string>
#include <queue>
#include <mutex>
#include <thread>
#include <winsock2.h>

class SocketClient {
public:
    static SocketClient& getInstance();
    void enqueueMessage(const std::string& message);
    bool isConnected() const;
    void stop();

private:
    SocketClient();
    ~SocketClient();
    void connect();
    void sendThread();

    SOCKET sock;
    std::queue<std::string> messageQueue;
    std::mutex queueMutex;
    std::thread senderThread;
    bool connected;
    bool running;
};

#endif //PROYECTOMEMORIA_SOCKET_CLIENT_H