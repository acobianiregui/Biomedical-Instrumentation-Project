#pragma once

class PumpDriver {
    public:
        void init(int pin);
        void setPumpSpeed(float speed); //in percentage (0.0 to 100.0)
        void stopPump();
        float getPumpSpeed() const;
    private:
        int pumpPin;
        float currentSpeed = 0.0f; //in percentage
};