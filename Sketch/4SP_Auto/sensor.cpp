#include "sensor.hpp"
#include <Arduino.h>

void sensor_setup(sensor_settings_t &s) {
  pinMode(s.pin, INPUT);
  s.value = 0;
  s.avg.pos = 0;
  s.avg.sum = 0;

  for (int i = 0; i < AVG_SIZE; i++) {
    s.avg.measurements[i] = 0;
  }
}

void sensor_read(sensor_settings_t &s) {
  unsigned int new_reading = analogRead(s.pin);

  // Remove old value from sum
  s.avg.sum -= s.avg.measurements[s.avg.pos];

  // Store new reading
  s.avg.measurements[s.avg.pos] = new_reading;

  // Add new value to sum
  s.avg.sum += new_reading;

  // Advance circular buffer position
  s.avg.pos = (s.avg.pos + 1) % AVG_SIZE;

  // Calculate average (bit shift divides by AVG_SIZE)
  s.value = s.avg.sum >> AVG_SHIFT;
}
