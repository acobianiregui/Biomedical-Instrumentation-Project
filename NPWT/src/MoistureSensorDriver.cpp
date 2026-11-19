#include "MoistureSensorDriver.h"
#include <Arduino.h>

void MoistureSensorDriver::init(int pin, int dry, int wet) {
    moisturePin = pin;
    dryValue = dry;
    wetValue = wet;

    pinMode(moisturePin, INPUT);
    analogReadResolution(10);//0-1023
}

void MoistureSensorDriver::setSaturationThreshold(int threshold) {
    saturationThreshold = constrain(threshold, 0, 100);
}

bool MoistureSensorDriver::isSaturated() {
    return currentMoisture >= saturationThreshold;
}

float MoistureSensorDriver::readMoisture(){
    int rawValue=analogRead(moisturePin); //This a value between 0 and 1023
    if (wetValue == dryValue) {
        Serial.println("wetValue and dryValue are the same ");
        currentMoisture = NAN;
        return currentMoisture;
    }
    currentMoisture=100*(float)(rawValue-dryValue)/(wetValue-dryValue); 
    currentMoisture=constrain(currentMoisture, 0.0f, 100.0f); //Make sure its capped
    return currentMoisture;
}

