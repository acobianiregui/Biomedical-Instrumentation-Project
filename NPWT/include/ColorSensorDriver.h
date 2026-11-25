#pragma once

#include <Arduino.h>
#include <Wire.h>

class ColorSensorDriver{
    public:
        ColorSensorDriver(TwoWire& bus, uint8_t address=0x29);
        bool begin();
        bool readRGB(uint8_t (&crgb)[3], uint16_t& c);
        String classifyColor(const uint8_t (&rgb)[3], uint16_t c);
        
    private:
        TwoWire& bus_;
        const uint8_t address_;

};