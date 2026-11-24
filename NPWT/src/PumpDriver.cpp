#include <Arduino.h>

#include "PumpDriver.h"

void PumpDriver:: init(int pin) {
    pumpPin = pin;
    
    ledcAttach(pumpPin,5000,8); //5kHz frequency, 8 bit resolution gives with resolution of 0.4% duty cycle
    ledcWrite(pumpPin, 0); //we start at 0% duty aka off
}

void PumpDriver::setPumpSpeed(float speed) {
    speed = constrain(speed, 0.0f, 100.0f); //doing speed in percentage
    currentSpeed = speed;
    int dutyCycle = round(speed * 255.0f / 100.0f);
    ledcWrite(pumpPin, dutyCycle); // Convert percentage to 8-bit value
}

void PumpDriver::stopPump() {
    currentSpeed = 0.0f;
    ledcWrite(pumpPin, 0); 
}

float PumpDriver::getPumpSpeed() const {
    return currentSpeed;
}

