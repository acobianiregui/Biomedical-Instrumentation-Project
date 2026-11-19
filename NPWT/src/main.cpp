#include <Arduino.h>
#include <Wire.h>

//Pin configuration
#include "PinConfig.h"
//Include drivers made for the project
#include "BluetoothManager.h"
#include "PIDController.h"
#include "BuzzerDriver.h"
#include "MoistureSensorDriver.h"

//////////////////// DECLARE OBJECTS HERE ! //////////////////////////////////////////
//PIDController object with params
PIDController pid(1.0f,1.0f,1.0f); //change based on trials
//Bluetooth manager class
BluetoothManager bluetooth;
BuzzerDriver buzzer;
MoistureSensorDriver moistureSensor;

///////////Set global variables///////////////////////////////////////////////////
float target_pressure= -125.0f; //differential pressure desired
unsigned long last_update=0;  //to keep track of time
uint16_t ts=500; //sampling period, in milliseconds


void setup() {
  //Setup configurations (see PinConfig.h for clarification)
  Serial.begin(115200); //Set bit rate for transmission
  bluetooth.begin();
  //Set pin modes
  //Sensors
  pinMode(Pins::FLOW, INPUT);
  moistureSensor.init(Pins::MOISTURE, 0, 1023); // IMPORTANT TO CALIBRATE AND INTRODUCE DRY AND WET VALUES FOR MOISTURE SENSOR
  //Actuators
  pinMode(Pins::PUMP, OUTPUT); 
  buzzer.init(Pins::BUZZER);
  //I2C buses
  Wire.begin(Pins::I2C0_SDA, Pins::I2C0_SCL);
  Wire1.begin(Pins::I2C1_SDA, Pins::I2C1_SCL);
  

}

//Main code here
void loop() {
  
  if (millis()-last_update>=ts){ //Sampling 
      //Read sensors
      bluetooth.sendString("Cycle...");
      Serial.println("Reading sensors...");
      //PID calculation
      //Update actuators
      //Send info
      last_update=millis(); //Update time
  }
  

  
}

//Main functions below...
int myFunction(int x, int y) { 
  return x + y;
}