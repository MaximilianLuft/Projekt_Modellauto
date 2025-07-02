#include "pid.hpp"


float pid(pid_settings_t &s, float soll, float in) {
  //code needs to be added here
  float pid;
  float  error = soll-in;
  s.clamp = 1;
  if (!s.clamp) {
    s.integral += error;
  }
  pid = s.p * error + s.clamp * s.i * s.T * s.integral + s.d * (error - s.last_error)/s.T;
  float pidin = pid;

  if(pid > s.anti_windup){
    pid = s.anti_windup;
  }
  if(pid < -s.anti_windup){
    pid = -s.anti_windup;
  }
  if(pidin != pid && ((pidin >= 0 && error >= 0)|| (pidin <= 0 && error <= 0))){
    s.clamp = 0;
  }
  else {
    s.clamp = 1;
  }
  s.last_error = error;
return pid;
}

void reset_integrator(pid_settings_t &s) {
  //code needs to be added here
}