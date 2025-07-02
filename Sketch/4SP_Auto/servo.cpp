#include "servo.hpp"
#include <Servo.h>
#include "Arduino.h"

// Global Servo object
Servo servo_object;

void servo_setup(servo_settings_t &s) {
  servo_object.attach(s.pin);     // Attach the servo to the specified pin
  servo_object.write(s.center);   // Move to center position by default
}

void servo_set_position(servo_settings_t &s, int pos) {
  // Clamp position within full_left and full_right
  if (pos < s.full_left) pos = s.full_left;
  if (pos > s.full_right) pos = s.full_right;
  servo_object.write(pos);        // Move servo to the desired position
}

void servo_test(servo_settings_t &s) {
  // Sweep from left to right and back
  servo_set_position(s, s.full_left);
  delay(500);

  servo_set_position(s, s.center);
  delay(500);

  servo_set_position(s, s.full_right);
  delay(500);

  servo_set_position(s, s.center);
  delay(500);
}
