#pragma once

template <typename T>
class ISensor {
public:
    ISensor() = default;
    virtual ~ISensor() = default;

    virtual bool enable() = 0;
    virtual bool disable() = 0;
    virtual bool isactive() = 0;
    virtual T readvalue() = 0;
};
