#include "pid.hpp"


float pid(pid_settings_t &s, float soll, float in) {
  //code needs to be added here
  float pid;

  float  error = soll-in;
  float T = 1.1;
  int clamp = 1;

  s.integral += error;


  pid = s.p * error + s.i * T * s.integral + s.d * (error - s.last_error)/T;
  
  float pidin = pid;

  if(pid > s.anti_windup){
    pid = s.anti_windup;
  }
  if(pid < -s.anti_windup){
    pid = -s.anti_windup;
  }
  if(pidin != pid && ((pidin > 0 && error >0)|| (pidin < 0 && error < 0))){
    clamp = 0;
  }
  else {
    clamp = 1;
  }
  pid = s.p * error + clamp * s.i * T * s.integral + s.d * (error - s.last_error)/T;

return pid;
}

void reset_integrator(pid_settings_t &s) {
  //code needs to be added here
}