#pragma once
#include "Server.hpp"
#include "Temperature.hpp"

class Manager {
public:
    Manager(std::string ip, uint16_t port);
    ~Manager() = default;

    void mainloop();

private:
    Server server;
    Temperature temp;
};
