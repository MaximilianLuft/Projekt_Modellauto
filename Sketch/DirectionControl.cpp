#include "DirectionControl.h"
#include "Arduino.h"


//The following function needs modifications
DirectionControl::DirectionControl(int servoPinIn, directionParameterSet directionParameters, pidParameterSet pidParameters) : controller(pidParameters){

}

DirectionControl::~DirectionControl(){}

void DirectionControl::setup(){
  DirectionControl::directionServo.attach(DirectionControl::servoPin); // initialize servodirectionServo.attach(pin_servo); // initialize
}

//The following function needs modifications
void DirectionControl::updateController(double is) {

}

double DirectionControl::getControllerP(){
  return controller.getP();
}

double DirectionControl::getControllerI(){
  return controller.getI();
}

double DirectionControl::getControllerD(){
  return controller.getD();
}

void DirectionControl::setControllerP(double parameterP){
  controller.setP(parameterP);
}

void DirectionControl::setControllerI(double parameterI){
  controller.setI(parameterI);
}

void DirectionControl::setControllerD(double parameterD){
  controller.setD(parameterD);
}

//The following function needs modifications
int DirectionControl::getDirection() {

}

//The following function needs modifications
void DirectionControl::updateDirection(){

}

//The following function needs modifications
void DirectionControl::testServo() {

}

