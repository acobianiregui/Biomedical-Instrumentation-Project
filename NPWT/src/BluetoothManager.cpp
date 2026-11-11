#include "BluetoothManager.h"
#include <string>

//ESP32 uses LBE bluetooth instead of traditional bluetooth
//in the BLE architechture, the esp32 acts like a server and advertises itself by broadcasting
//the computer in this case is the central and is constantly scanning for communication
//the server manages its data in services (folder), each with its own characteristics (files)
//refer to https://docs.arduino.cc/libraries/arduinoble/ for more info


#define SERVICE_UUID "12345678-1234-1234-1234-123456789abc"
#define DATA_UUID    "87654321-4321-4321-4321-cba987654321"

void BluetoothManager:: begin(){
    //Initialize 
    NimBLEDevice :: init("NPWT_device"); //Public name in bluetooth
    //Create Server
    server = NimBLEDevice::createServer();
    server->advertiseOnDisconnect(true); //To be available again after user disconnects
    //Create service
    NimBLEService* service = server->createService(SERVICE_UUID);
    //Create characteristic
    dataCharacteristic = service->createCharacteristic(
        DATA_UUID,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::NOTIFY
    );
    //Start service
    service->start();
    // Advertise device name
    NimBLEAdvertising* advertising = NimBLEDevice::getAdvertising();

    advertising->setName("NPWT_ESP32");
    advertising->start();
}

bool BluetoothManager::isConnected(){
    return server != nullptr && server->getConnectedCount() > 0;
}

void BluetoothManager :: sendData(
    float p1, float p2, float flow, float moisture, float r, float g, float b){
        
    if (!isConnected() || dataCharacteristic == nullptr) {
        return; 
    }
    //Store in array of 32 floats
    float data[7]= {p1, p2, flow, moisture, r, g, b};
    //Send data to characteristic
    dataCharacteristic->setValue(
        reinterpret_cast<const uint8_t*>(data),
        sizeof(data)
    );

    //Notify clients of new data
    dataCharacteristic->notify();
}
//For debugging
void BluetoothManager :: sendString(const std::string& message) {
    if (!isConnected() || dataCharacteristic == nullptr) {
        return; 
    }
    // Send string data to characteristic
    dataCharacteristic->setValue(message);
    // Notify clients of new data
    dataCharacteristic->notify();
}