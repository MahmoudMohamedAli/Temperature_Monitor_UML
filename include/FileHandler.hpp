#pragma once
#include <string>

class FileHandler {
public:
    explicit FileHandler(std::string filepath);
    ~FileHandler();

    std::string read();
    bool isfileActive();

private:
    std::string m_filepath;
};
