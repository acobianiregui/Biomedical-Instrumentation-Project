#pragma once
#include <Arduino.h>

class MoistureSensorDriver{
    public:
        void init(int pin, int dry, int wet); 
        float readMoisture(); //in percentage
        bool isSaturated(); 
        void setSaturationThreshold(int threshold);


    private:
        int moisturePin;
        int dryValue=620; 
        int wetValue=175;
        int saturationThreshold=80;
        float currentMoisture=NAN; 
};