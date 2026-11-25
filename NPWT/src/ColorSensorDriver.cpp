#include "ColorSensorDriver.h"

#include <Arduino.h>
#include <Wire.h>

namespace {
    constexpr uint32_t OUTPUT_MIN_COUNTS = 1677722UL;
    constexpr uint32_t OUTPUT_MAX_COUNTS = 15099494UL;
    constexpr uint8_t COMMAND[] = {0xAA, 0x00, 0x00};
    constexpr uint8_t STATUS_BUSY = 0x20;
    constexpr uint8_t STATUS_MEMORY_ERROR = 0x04;
    constexpr uint8_t STATUS_MATH_SATURATION = 0x01;
}

ColorSensorDriver::ColorSensorDriver(TwoWire& bus, uint8_t address)
    : bus_(bus), address_(address) {
}

bool ColorSensorDriver::begin(){
    bus_.beginTransmission(address_);
    return bus_.endTransmission() == 0;
}

bool ColorSensorDriver :: readRGB(uint8_t (&rgb)[3],uint16_t& c){
    //The color sensor uses 16 bit for each color, but we'll store it with 8 bit (0-255) range
    uint16_t reading[4]={0,0,0,0};
    uint8_t buf[8]={0};
    bus_.beginTransmission(address_);
    if (bus_.write(COMMAND, sizeof(COMMAND)) != sizeof(COMMAND)) {
        Serial.println("ERROR: Could not write command");
        bus_.endTransmission();
        return false;
    }
    if (bus_.endTransmission() != 0) {

        return false;
    }
    if (bus_.requestFrom(address_, (uint8_t)8) != 8) {
        Serial.println("ERROR: Incomplete sensor reading");
        return false;
    }
    //At least 5ms delay
    delay(10);

    for (uint8_t i = 0; i < 8; i++) {
        buf[i] = bus_.read();
    }

    // Reconstruct 16-bit values
    for (uint8_t i = 0; i < 4; i++) {
        reading[i] = (uint16_t)buf[2*i] |
                    ((uint16_t)buf[2*i+1] << 8);
    }
    if (reading[0]>0){ //This is c
        c=reading[0];
        rgb[0]=(uint8_t)min(255.0f, ((float) reading[1]/ (float) c) * 255.0f); //This is red
        rgb[1]=(uint8_t)min(255.0f, ((float) reading[2]/ (float) c) * 255.0f); //This is green
        rgb[2]=(uint8_t)min(255.0f, ((float) reading[3]/ (float) c) * 255.0f); //This is blue
    }else{
        return false;
    }

    return true;
}

String ColorSensorDriver:: classifyColor(const uint8_t (&rgb)[3], uint16_t c){
    float r = rgb[0];
    float g = rgb[1];
    float b = rgb[2];

    // Example thresholds: must be calibrated
    if (c < 100) {
        return "UNKNOWN";
    }

    if (c < 1000 && r > g && g > b) {
        return "OPAQUE_BROWN";
    }

    if (r > 1.4f * g && r > 1.4f * b) {
        return "CLEAR_RED";
    }

    if (g > 1.3f * r && g > 1.3f * b) {
        return "CLEAR_GREEN";
    }

    if (r > 1.5f * b && g > 1.5f * b) {
        return "CLEAR_YELLOW";
    }

    return "UNKNOWN";
}

