#pragma once
#include "ISensor.hpp"
#include "FileHandler.hpp"
#include <memory>

class Temperature : public ISensor<double> {
public:
    Temperature();
    ~Temperature();

    bool enable() override;
    bool disable() override;
    bool isactive() override;
    double readvalue() override;

private:
    bool m_activation;
    std::unique_ptr<FileHandler> m_filehandler;
    double m_lastValue;
};
