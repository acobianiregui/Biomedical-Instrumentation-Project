#include <Arduino.h>
//Pin configuration
#include "PinConfig.h"
//Include drivers made for the project
#include "BluetoothManager.h"
#include "PIDController.h"

//////////////////// DECLARE OBJECTS HERE ! //////////////////////////////////////////
//PIDController object with params
PIDController pid(1.0f,1.0f,1.0f); //change based on trials
//Bluetooth manager class
BluetoothManager bluetooth;


///////////Set global variables///////////////////////////////////////////////////
float target_pressure= -125.0f; //differential pressure desired
unsigned long last_update=0;  //to keep track of time
uint16_t ts=500; //sampling period, in milliseconds


void setup() {
  //Setup configurations
  Serial.begin(115200); //Set bit rate for transmission
  bluetooth.begin();
  //Set pin modes
  //Sensors
  pinMode(Pins::FLOW, INPUT);
  pinMode(Pins::MOISTURE, INPUT);
  //I2C includes pressure sensors and color sensor
  pinMode(Pins::I2C_SDA, INPUT); 
  pinMode(Pins::I2C_SCL, INPUT);
  //Actuators
  pinMode(Pins::PUMP, OUTPUT); 
  pinMode(Pins::BUZZER, OUTPUT); 

}

//Main code here
void loop() {
  
  if (millis()-last_update>=ts){ //Sampling 
      //Read sensors

      //PID calculation
      //Update actuators
      //Send info
  }

  last_update=millis(); //Update time
}

//Main functions below...
int myFunction(int x, int y) { 
  return x + y;
}