#pragma once

class MoistureSensorDriver{
    public:
        float readMoisture();
        

    private:
        int dryValue=0; 
        int wetValue=0;

};