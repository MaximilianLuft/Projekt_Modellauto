/////////////////////////////////////////////////////////
///// This file does not need any modification, /////////
///// if needed it can be extended //////////////////////
///////////////////////////////////////////////////////// 
#pragma once

#include "PID.h"
#include <Servo.h>

struct directionParameterSet{
  int maxPos, minPos, centerPos;
};

class DirectionControl{
  public:
    DirectionControl(int,directionParameterSet,pidParameterSet);
    ~DirectionControl();

    int getDirection();
    
    void updateDirection();
    void updateController(double);
    double getControllerP();
    double getControllerI();
    double getControllerD();
    void setControllerP(double parameterP);
    void setControllerI(double parameterI);
    void setControllerD(double parameterD);
    
    void testServo();
    void setup();
    Servo directionServo;
  private:
    PID controller;
    
    int servoPin;
    int centerPos;
    int maxPos;
    int minPos;

    unsigned int currentDirection;
};

