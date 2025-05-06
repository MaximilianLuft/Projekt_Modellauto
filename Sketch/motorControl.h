/////////////////////////////////////////////////////////
///// This file does not need any modification, /////////
///// if needed it can be extended //////////////////////
///////////////////////////////////////////////////////// 
#pragma once

#include "PID.h"

enum class MOTOR_STATES{STOP,RUN};

class MotorControl {
  
  public:
    
    MotorControl(unsigned int,unsigned int,pidParameterSet);
    void setSpeed(double);
    void updateMotor(void);
    void setState(MOTOR_STATES);
    void updateController(double);
    void setup();
    double getControllerP();
    double getControllerI();
    double getControllerD();
    void setControllerP(double parameterP);
    void setControllerI(double parameterI);
    void setControllerD(double parameterD);
    
  private:
    unsigned int motorPin;
    unsigned int deadManSwitchPin;
    int motorDuty;
    PID controller;
    MOTOR_STATES motorState=MOTOR_STATES::STOP;
};

