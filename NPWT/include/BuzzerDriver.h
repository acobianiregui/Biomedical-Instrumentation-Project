#pragma once
#include <Arduino.h>

class BuzzerDriver{
    public:
        void init(int pin);
        void playTone(int frequency, int duration);
        void stopTone();
        void update();
        void playAlarmTone();
        void activateAlarm(String alarmType);
        void stopAlarm();

    private:
        int buzzerPin;
        unsigned long toneStartTime=0;
        unsigned long toneDuration=0;
        bool isPlaying=false;

        //For repeating alarms
        String currentAlarm = "";
        bool alarmActive = false;
        unsigned long pauseDuration = 0;
        unsigned long pauseStartTime = 0;
};