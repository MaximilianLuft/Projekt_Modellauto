#include "motorControl.h"
#include "Arduino.h"

MotorControl::MotorControl(unsigned int deadManSwitchPinIn,unsigned int motorPinIn, pidParameterSet pidParameters) : controller(pidParameters) {
  MotorControl::motorDuty = 0; 
  MotorControl::motorPin = motorPinIn;
  MotorControl::deadManSwitchPin = deadManSwitchPinIn;
}

void MotorControl::setup(){
  pinMode(MotorControl::motorPin, OUTPUT);
  MotorControl::setState(MOTOR_STATES::STOP);
}

//The following function needs modifications
void MotorControl::setSpeed(double speedSetpoint){
  
}

//The following function needs modifications
void MotorControl::updateController(double currentSpeed){
  
}


void MotorControl::updateMotor(void){
  if(MotorControl::motorState==MOTOR_STATES::RUN && !digitalRead(MotorControl::deadManSwitchPin)){
    analogWrite(MotorControl::motorPin, MotorControl::motorDuty);
  }else{
    analogWrite(MotorControl::motorPin, 0);//Stop motor
  }
}

void MotorControl::setState(MOTOR_STATES stateIn){
  if(MotorControl::motorState != stateIn){
    MotorControl::motorState = stateIn;
    if(MotorControl::motorState==MOTOR_STATES::RUN){
      MotorControl::controller.resetIntegrator();
    }
    MotorControl::updateMotor();//update Motor in case of a state change
  }
}

double MotorControl::getControllerP(){
  return controller.getP();
}

double MotorControl::getControllerI(){
  return controller.getI();
}

double MotorControl::getControllerD(){
  return controller.getD();
}

void MotorControl::setControllerP(double parameterP){
  controller.setP(parameterP);
}

void MotorControl::setControllerI(double parameterI){
  controller.setI(parameterI);
}

void MotorControl::setControllerD(double parameterD){
  controller.setD(parameterD);
}

