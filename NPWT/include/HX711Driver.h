#pragma once
#include <Arduino.h>

class HX711Driver {
public:
    HX711Driver(uint8_t douPin, uint8_t sckPin);
    void begin();
    bool isReady();

    int32_t readRaw();
    
    void tare();
    void setCalibrationFactor(float factor);
    float getWeight();

private:
    uint8_t douPin;
    uint8_t sckPin;
    float calibrationFactor;
    long offset;
};