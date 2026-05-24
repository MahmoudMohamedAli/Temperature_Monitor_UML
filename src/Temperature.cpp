#include "Temperature.hpp"
#include <stdexcept>
#include <string>

// RPi thermal sensor path
static const std::string SENSOR_PATH = "/sys/class/thermal/thermal_zone0/temp";

Temperature::Temperature()
    : m_activation(false)
    , m_filehandler(std::make_unique<FileHandler>(SENSOR_PATH))
    , m_lastValue(0.0) {}

Temperature::~Temperature() {}

bool Temperature::enable() {
    if (!m_filehandler->isfileActive()) {
        return false;
    }
    m_activation = true;
    return true;
}

bool Temperature::disable() {
    m_activation = false;
    return true;
}

bool Temperature::isactive() {
    return m_activation;
}

double Temperature::readvalue() {
    if (!m_activation) {
        return m_lastValue;
    }
    try {
        std::string raw = m_filehandler->read();
        // RPi reports temp in millidegrees Celsius e.g. 45000 = 45.0°C
        m_lastValue = std::stod(raw) / 1000.0;
    } catch (const std::exception& e) {
        m_activation = false;
    }
    return m_lastValue;
}
