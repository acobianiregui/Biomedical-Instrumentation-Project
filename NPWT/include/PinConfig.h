#pragma once

#include <Arduino.h>

//This file includes all pin configurations/selectiosn for the project
//The assigment of pins is based on the ESP32 board
//Review ESP32 datasheet for pin disribution.

//IMPORTANT TO UPDATE IN CASE OF PIN CHANGES !!!!!!!!!!!!!!!!!

/* Important considerations:
        - Pressure sensors 1 and 2 have the same I2C address so unless we use multiplexer they have to be on different busses.

*/
namespace Pins {
    //I2C Bus 0 (for p1 and color sensor)
    constexpr uint8_t I2C0_SDA = A4;
    constexpr uint8_t I2C0_SCL = A5;
    //I2C Bus 1 (for p2)
    constexpr uint8_t I2C1_SDA = D2;
    constexpr uint8_t I2C1_SCL = D3;
    //Flow sensor
    constexpr uint8_t FLOW=A0; //Flow sensor pin
    //Moisture sensor
    constexpr uint8_t MOISTURE=A1; //Moisture sensor pin
    //Pump control
    constexpr uint8_t PUMP=D5; //Pump control pin
    //Buzzer
    constexpr uint8_t BUZZER=D6; //Buzzer pin

}
