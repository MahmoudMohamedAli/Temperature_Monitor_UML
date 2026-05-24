#include "Server.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

Server::Server(std::string ip, uint16_t port)
    : ip(std::move(ip)), port(port) {}

Server::~Server() {
    stop();
}

bool Server::start() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket\n";
        return false;
    }

    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

    // bind
    if (bind(serverSocket, (sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "Bind failed\n";
        return false;
    }

    // listen
    if (listen(serverSocket, 5) < 0) {
        std::cerr << "Listen failed\n";
        return false;
    }

    start_thread = true;
    t = std::thread(&Server::run, this);
    std::cout << "Server started on " << ip << ":" << port << "\n";
    return true;
}

bool Server::stop() {
    start_thread = false;
    if (serverSocket > 0) {
        close(serverSocket);
        serverSocket = 0;
    }
    if (t.joinable()) {
        t.join();
    }
    return true;
}

bool Server::reload() {
    stop();
    return start();
}

void Server::add_endpoint(std::function<std::string()> callback) {
    m_callbacks.push_back(callback);
}

void Server::run() {
    while (start_thread) {
        sockaddr_in clientAddr{};
        socklen_t clientLen = sizeof(clientAddr);

        // accept
        int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientLen);
        if (clientSocket < 0) {
            if (start_thread) std::cerr << "Accept failed\n";
            break;
        }

        // Build response from all callbacks
        std::string response;
        for (auto& cb : m_callbacks) {
            response += cb() + "\n";
        }

        // Send HTTP response
        std::string httpResponse =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Connection: close\r\n\r\n" + response;

        send(clientSocket, httpResponse.c_str(), httpResponse.size(), 0);
        close(clientSocket);
    }
}
