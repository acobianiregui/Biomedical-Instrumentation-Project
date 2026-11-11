#pragma once

#include <Arduino.h>

//This file includes all pin configurations/selectiosn for the project
//The assigment of pins is based on the ESP32 board
//Review ESP32 datasheet for pin disribution.

//IMPORTANT TO UPDATE IN CASE OF PIN CHANGES !!!!!!!!!!!!!!!!!

namespace Pins {
    //I2C pins for pressure sensor and color
    constexpr uint8_t I2C_SDA = A4;
    constexpr uint8_t I2C_SCL = A5;
    //Flow sensor
    constexpr uint8_t FLOW=A0; //Flow sensor pin
    //Moisture sensor
    constexpr uint8_t MOISTURE=A1; //Moisture sensor pin
    //Pump control
    constexpr uint8_t PUMP=D5; //Pump control pin
    //Buzzer
    constexpr uint8_t BUZZER=D6; //Buzzer pin

}
