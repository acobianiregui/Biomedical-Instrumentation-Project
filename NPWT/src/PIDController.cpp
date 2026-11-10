#include "PIDController.h"

PIDController::PIDController(float kp, float ki, float kd):
    kp(kp), ki(ki), kd(kd) {} //Constructor

float PIDController:: calculate_correction(float goal, float measurement, float dt){
    if (dt<=0.0f) return 0.0f; //No negative time lapses

    float error= goal-measurement;

    integral+= error*dt; // Discrete integral is summation

    float derivative=0.0f; // Initizialize in case first run

    if (!beginnig){
        derivative= (error-previousError)/dt; //Discrete derivative
    }else{
        beginnig=false; 
    }
    previousError=error;
    float sol= kp*error+ ki*integral+ kd*derivative;
    return sol;
}

void PIDController:: reset(){
    integral=0.0f;
    previousError=0.0f;
    beginnig=true;
}