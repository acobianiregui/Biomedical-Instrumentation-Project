#include "BuzzerDriver.h"
#include <Arduino.h>

void BuzzerDriver::init(int pin) {
    buzzerPin = pin;

    ledcAttach(buzzerPin, 2000, 8); //2kHz frequency, 8 bit resolution gives with resolution of 0.4% duty cycle
    ledcWrite(buzzerPin, 0); //we start at 0% duty cycle to start off
}

void BuzzerDriver::playTone(int frequency, int duration) {
    ledcWriteTone(buzzerPin, frequency); //Different frequency for different alarms

    toneStartTime = millis();
    toneDuration = duration;
    isPlaying = true;
}

void BuzzerDriver::stopTone() {
    ledcWriteTone(buzzerPin, 0); // Stop the tone
    isPlaying = false;
}



void BuzzerDriver::playAlarmTone() {
    if (currentAlarm == "high_pressure") {
        playTone(1000, 500); // 1kHz for 500ms
    } else if (currentAlarm == "low_pressure") {
        playTone(500, 500); // 500Hz for 500ms
    } else if (currentAlarm == "SATURATION") {
        playTone(2000, 300); // 2kHz for 300ms
    }
}

void BuzzerDriver::activateAlarm(String alarmType) {

    //Ignore if alarm already active
    if (alarmActive && currentAlarm == alarmType) {
        return;
    }

    int frequency;
    int duration;

    if (alarmType == "high_pressure") {
        frequency = 1000;
        duration = 500;
        pauseDuration = 500;

    } else if (alarmType == "low_pressure") {
        frequency = 500;
        duration = 500;
        pauseDuration = 1000;

    } else if (alarmType == "SATURATION") {
        frequency = 2000;
        duration = 300;
        pauseDuration = 2000;

    } else {
        Serial.println("Unknown alarm type: " + alarmType);
        return; 
    }

    currentAlarm = alarmType;
    alarmActive = true;

    playTone(frequency, duration);
}

void BuzzerDriver::stopAlarm() {
    alarmActive = false;
    currentAlarm = "";
    stopTone();
}

void BuzzerDriver::update() {

    unsigned long now = millis();

    //check if tone has finished
    if (isPlaying && now - toneStartTime >= toneDuration) {
        stopTone();
        pauseStartTime = now;
    }

    //check if pause has finished
    if (alarmActive && !isPlaying &&
        now - pauseStartTime >= pauseDuration) {

        playAlarmTone();
    }
}