#include "FileHandler.hpp"
#include <fstream>
#include <stdexcept>
#include <sys/stat.h>

FileHandler::FileHandler(std::string filepath)
    : m_filepath(std::move(filepath)) {}

FileHandler::~FileHandler() {}

std::string FileHandler::read() {
    std::ifstream file(m_filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + m_filepath);
    }
    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
    return content;
}

bool FileHandler::isfileActive() {
    struct stat buffer;
    return (stat(m_filepath.c_str(), &buffer) == 0);
}
