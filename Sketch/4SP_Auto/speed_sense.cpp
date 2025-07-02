#include "speed_sens.hpp"
#include "Arduino.h"

void setup_speed_sense(speed_sense_settings_t &s) {
  pinMode(s.pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(s.pin), speed_interrupt, RISING);
}
