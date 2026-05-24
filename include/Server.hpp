#pragma once
#include <string>
#include <thread>
#include <functional>
#include <vector>
#include <cstdint>

class Server {
public:
    Server(std::string ip, uint16_t port);
    ~Server();

    bool start();
    bool stop();
    bool reload();
    void add_endpoint(std::function<std::string()> callback);

private:
    void run();

    std::string ip;
    uint16_t port;
    std::thread t;
    bool start_thread = false;
    int serverSocket = 0;
    std::vector<std::function<std::string()>> m_callbacks;
};
