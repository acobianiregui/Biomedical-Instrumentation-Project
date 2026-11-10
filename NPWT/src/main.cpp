#include <Arduino.h>
//Include drivers made for the project
#include "BluetoothManager.h"
#include "PIDController.h"

//////////////////// DECLARE OBJECTS HERE ! //////////////////////////////////////////
//PIDController object with params
PIDController pid(1.0f,1.0f,1.0f); //change based on trials
//Bluetooth manager class
BluetoohManager bluetooth;


///////////Set global variables///////////////////////////////////////////////////
float target_pressure= -125.0f; //differential pressure desired
unsigned long last_update=0;  //to keep track of time
uint16_t ts=500; //sampling period


void setup() {
  //Setup configurations
  Serial.begin(115200); //Set bit rate for transmission
  bluetooth.begin();
}

//Main code here
void loop() {
  
  if (millis()-last_update>=ts){ //Sampling 

  }
}

//Main functions below...
int myFunction(int x, int y) {
  return x + y;
}