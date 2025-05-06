#include "PID.h"

PID::PID(pidParameterSet parameterIn) {
  PID::p = parameterIn.p;
  PID::i = parameterIn.i;
  PID::d = parameterIn.d;
  PID::soll = parameterIn.soll;
  PID::base = parameterIn.base;
  PID::antiWindup = parameterIn.antiWindup;
  PID::outMin = parameterIn.outMin;
  PID::outMax = parameterIn.outMax;
}

PID::~PID() {}

//The following function needs modifications
double PID::calcOutput(double input) {

  return out;
}

double PID::getBase() {
  return base;
}

double PID::getP(){
  return p;  
}

double PID::getI(){
  return i;
}

double PID::getD(){
  return d;
}

void PID::setP(double parameterP){
  p = parameterP;
  return;
}

void PID::setI(double parameterI){
  i = parameterI;
  resetIntegrator();
  return;
}

void PID::setD(double parameterD){
  d = parameterD;
  return;
}


void PID::resetIntegrator() {
  integral = 0;
}


void PID::setSoll(double soll) {
  PID::soll = soll;
}

