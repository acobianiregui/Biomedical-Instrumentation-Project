#pragma once

#include <Arduino.h>
#include <Wire.h>

class PressureSensorDriver {
public:
    PressureSensorDriver(TwoWire& bus, float minimumPressureBar = 0.0f, float maximumPressureBar = 1.0f,
                         uint8_t address = 0x28);

    bool begin();

    bool readPressureMmHg(float& pressureMmHg);

private:
    TwoWire& bus_;
    const uint8_t address_;
    const float pMinBar_;
    const float pMaxBar_;
};
