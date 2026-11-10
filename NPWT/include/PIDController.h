#pragma once

class PIDController{
    public:
        PIDController(float kp, float ki, float kd);
     
        float calculate_correction(float goal, float measurement, float dt);
        //Goal is our desired differential pressure
        //Measurement is the difference picked up by 
        //Dt is time lapse between measurements (this PID is discrete not continous)

        void reset(); //Just in case we need to reset configuration!

     private: 
        float kp, ki, kd;
        float integral=0.0f;
        float previousError= 0.0f;
        bool beginnig=true; //First time has no previous error
};