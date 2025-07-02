#include "motor.hpp"
#include "Arduino.h"

void motor_setup(motor_settings_t &s) {
  pinMode(s.pin, OUTPUT); // Set motor control pin as output
}

void motor_set_speed(motor_settings_t &s, unsigned int speed) {
  // Clamp the input speed to the allowed range
  if (speed > s.max_speed) speed = s.max_speed;
  if (speed < s.min_speed) speed = s.min_speed;

  // Map speed to PWM range (0–255)
  unsigned int pwm_value = map(speed, s.min_speed, s.max_speed, 0, 255);

  // Output PWM signal
  analogWrite(s.pin, pwm_value);
}
