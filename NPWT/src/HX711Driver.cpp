#include <Arduino.h>
#include "HX711Driver.h"

HX711Driver::HX711Driver(uint8_t douPin, uint8_t sckPin){
    this->douPin=douPin;
    this->sckPin=sckPin;
}

void HX711Driver::begin(){
    digitalWrite(sckPin, LOW);
    pinMode(douPin, INPUT);
    pinMode(sckPin, OUTPUT);
    calibrationFactor=1.0f;
    offset=0;
}

bool HX711Driver::isReady(){
    return digitalRead(douPin)==LOW;
}

int32_t HX711Driver::readRaw(){ //If dout is high, DO NOT READ
    while(!isReady()){
        //wait for conversion
    }
    //now data should be ready
    //nuance, the HX711 returns data in 24 bits (c2)
    uint32_t data=0;
    for(int i=0;i<24;i++){
        digitalWrite(sckPin, HIGH);
        data=(data<<1)|digitalRead(douPin);
        digitalWrite(sckPin, LOW);
    }
    //choose channel for next reading´
    //if we add one more pulse we select channel A with gain 128
    digitalWrite(sckPin, HIGH);
    digitalWrite(sckPin, LOW);

    //Convert the 24 bit two complement to 32 bit int
    if(data & 0x800000){
        data |= 0xFF000000;
    }
    return (int32_t)data;

}

void HX711Driver::tare(){
    offset=readRaw();
}

void HX711Driver::setCalibrationFactor(float factor){
    calibrationFactor=factor;
}

float HX711Driver::getWeight(){
    int32_t raw=readRaw();
    return (raw-offset)/calibrationFactor;
}

