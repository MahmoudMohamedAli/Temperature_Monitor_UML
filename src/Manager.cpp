#include "Manager.hpp"
#include <iostream>
#include <chrono>
#include <thread>

Manager::Manager(std::string ip, uint16_t port)
    : server(std::move(ip), port) {}

void Manager::mainloop() {
    // Enable temperature sensor
    if (!temp.enable()) {
        std::cerr << "Failed to enable temperature sensor\n";
        return;
    }

    // Register temperature endpoint with server
    server.add_endpoint([this]() {
        double val = temp.readvalue();
        return "temperature=" + std::to_string(val) + "C";
    });

    // Start server
    if (!server.start()) {
        std::cerr << "Failed to start server\n";
        return;
    }

    std::cout << "Manager running. Reading temperature...\n";

    // Main loop - read and print temperature every 2 seconds
    while (true) {
        if (temp.isactive()) {
            double val = temp.readvalue();
            std::cout << "Temperature: " << val << " C\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}
