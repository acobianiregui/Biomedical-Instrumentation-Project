#include <Arduino.h>
#include <Wire.h>

//Pin configuration
#include "PinConfig.h"
//Include drivers made for the project
#include "BluetoothManager.h"
#include "PIDController.h"
#include "BuzzerDriver.h"
#include "MoistureSensorDriver.h"
#include "PressureSensorDriver.h"
#include "PumpDriver.h"
#include "HX711Driver.h"

//////////////////// DECLARE OBJECTS HERE ! //////////////////////////////////////////
//PIDController object with params
PIDController pid(-0.4f,-0.05f,-0.01f); //change based on trials
//Bluetooth manager class
BluetoothManager bluetooth;
BuzzerDriver buzzer;
MoistureSensorDriver moistureSensor;
PressureSensorDriver pressure1(Wire, 0.0f, 1.0f, 0x28); PressureSensorDriver pressure2(Wire1, 0.0f, 1.0f, 0x28);
PumpDriver pump;
HX711Driver hx711(Pins::HX711_DOUT, Pins::HX711_SCK);



 
///////////Set global variables///////////////////////////////////////////////////
float target_pressure= -125.0f; //differential pressure desired
unsigned long last_update=0;  //to keep track of time
uint16_t ts=100; //sampling period, in milliseconds
float atmospheric_pressure;
float pump_speed=0.0f;

void setup() {
  //Setup configurations (see PinConfig.h for clarification)
  Serial.begin(115200); //Set bit rate for transmission
  bluetooth.begin();
  //Initialize I2C BEFORE probing sensors.
  Wire.begin(Pins::I2C0_SDA, Pins::I2C0_SCL);
  Wire1.begin(Pins::I2C1_SDA, Pins::I2C1_SCL);
  //sanity check for pressure sensors
  Serial.printf("P1 detected on Wire:  %s\n", pressure1.begin() ? "YES" : "NO");
  Serial.printf("P2 detected on Wire1: %s\n", pressure2.begin() ? "YES" : "NO");
  //Sensors
  hx711.begin();
  moistureSensor.init(Pins::MOISTURE, 620, 175); // IMPORTANT TO CALIBRATE AND INTRODUCE DRY AND WET VALUES FOR MOISTURE SENSOR
  moistureSensor.setSaturationThreshold(80); //Set saturation threshold for moisture sensor
  
  //Actuators
  pump.init(Pins::PUMP);
  buzzer.init(Pins::BUZZER);
  pump.setPumpSpeed(0.0f);
  //Set atmospheric pressure
  pressure1.readPressureMmHg(atmospheric_pressure);

  
}
bool pepe=false;
//Main code here
void loop() {
  float p1;
  bool ok=pressure1.readPressureMmHg(p1);
  Serial.println(ok);
   Serial.println(p1); 
  buzzer.update();
  if (millis()-last_update>=ts){ //Sampling 
      //Read sensors
      bluetooth.sendString("Cycle...");
      //Serial.println("Reading sensors...");
      //PID calculation
      pump_speed=pid.calculate_correction(620.0f, p1, ts/1000.0f);
      Serial.println("Current speed"); 
      Serial.println(pump_speed);
      pump.setPumpSpeed(pump_speed);
      //Update actuators
      //Send info
      //moistureSensor.readMoisture();
      last_update=millis(); //Update time
  }
  

  
}

//flow estimation function

float estimateFlow(float previousMass, float currentMass, float deltaTime, float density){
  if (deltaTime <=0 || density <=0){
    Serial.println("wrong deltaTime or density");
    return 0.0f; 
  }
  //Calculate flow rate based on mass change over time
  float massChange=currentMass-previousMass;
  float flowRate=massChange/(density * deltaTime); //in grams per second
  return flowRate;
}