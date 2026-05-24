cmake_minimum_required(VERSION 3.16)
project(temperature-monitor VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    src/main.cpp
    src/FileHandler.cpp
    src/Temperature.cpp
    src/Server.cpp
    src/Manager.cpp
)

# Create executable
add_executable(temperature-monitor ${SOURCES})

# Include headers
target_include_directories(temperature-monitor PRIVATE include)

# Link pthread for std::thread
target_link_libraries(temperature-monitor PRIVATE pthread)

# Install binary to /usr/bin
install(TARGETS temperature-monitor
    RUNTIME DESTINATION bin
)
