#include "pid.hpp"

float pid(pid_settings_t &s, float soll, float in) {
  //code needs to be added here
  float pid;

  float  error = soll-in;
  float T = 1.1;

  s.integral += error;
  if(s.integral > s.anti_windup){
    s.integral = s.anti_windup;
  }
  if(s.integral < -s.anti_windup){
    s.integral = -s.anti_windup;
  }

  pid = s.p * error + s.i * T * s.integral + s.d * (error - s.last_error)/T;
return pid;
}

void reset_integrator(pid_settings_t &s) {
  //code needs to be added here
}