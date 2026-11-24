#pragma once

#include <Arduino.h>
#include <Wire.h>

class ColorSensorDriver{
    public:
        ColorSensorDriver(TwoWire& bus, uint8_t address);
    private:
        TwoWire& bus;

};