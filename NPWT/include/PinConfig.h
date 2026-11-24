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
    constexpr uint8_t I2C0_SDA = A4;//21;
    constexpr uint8_t I2C0_SCL = A5;//22;
    //I2C Bus 1 (for p2)
    constexpr uint8_t I2C1_SDA = D2;//18;
    constexpr uint8_t I2C1_SCL = D3;//19;
    //Moisture sensor
    constexpr uint8_t MOISTURE=A1;//4; //Moisture sensor pin
    //Pump control
    constexpr uint8_t PUMP=D5;//D5; //Pump control pin
    //Buzzer
    constexpr uint8_t BUZZER=D6;//D6; //Buzzer pin
    //HX711 pins
    constexpr uint8_t HX711_DOUT=D7;//D7; //HX711 data
    constexpr uint8_t HX711_SCK=D8;//D8; //HX711 clock

}
