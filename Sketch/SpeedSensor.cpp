#include "SpeedSensor.h"
#include "Arduino.h"

SpeedSensor::SpeedSensor(int speedSendPinIn){
  SpeedSensor::speedSendPin=speedSendPinIn;
}

SpeedSensor::~SpeedSensor() {
}

void SpeedSensor::setup(){
  pinMode(SpeedSensor::speedSendPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(SpeedSensor::speedSendPin), speedInterrupt, CHANGE);  
}

//The following function needs modifications
void SpeedSensor::interrupt(unsigned long now) {

}

//The following function needs modifications
bool SpeedSensor::getState() {  

}

//The following function needs modifications
double SpeedSensor::getSpeed() {  
  
}

