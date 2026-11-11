#pragma once

#include <NimBLEDevice.h>

//ESP32 uses LBE bluetooth instead of traditional bluetooth
//in the BLE architechture, the esp32 acts like a server and advertises itself by broadcasting
//the computer in this case is the central and is constantly scanning for communication
//the server manages its data in services (folder), each with its own characteristics (files)
//refer to https://docs.arduino.cc/libraries/arduinoble/ for more info

class BluetoothManager{
    public:
        void begin(); //Device must be included in the BluetoohManager.cpp file
        void sendData(float p1, float p2, float flow, float moisture, float r, float g, float b); 
        //r,g,b refers to rgb from color sensor
        bool isConnected(); //Check status of connection
        void sendString(const std::string& message); //mainly for debugging
    private:
        NimBLEServer* server= nullptr;
        NimBLECharacteristic* dataCharacteristic= nullptr;

};