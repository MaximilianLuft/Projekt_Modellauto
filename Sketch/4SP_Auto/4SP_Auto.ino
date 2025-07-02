#include "Arduino.h"
#include "motor.hpp"
#include "pid.hpp"
#include "sensor.hpp"
#include "servo.hpp"
#include "uart.hpp"
#include "system.hpp"
#include "speed_sens.hpp"

//the entries should not rearranged (compiler error)
servo_settings_t servo = {
  .pin = 5,
  .full_left = 40,
  .full_right = 140,
  .center = 90,
};

//the entries should not rearranged (compiler error)
motor_settings_t motor = {
  .pin = 3,
  .max_speed = 200, // max 255
  .min_speed = 0
};

//the entries should not rearranged (compiler error)
sensor_settings_t left_sensor = {
  .pin = A2,
  .value = 0,
  .avg = {}
};

//the entries should not rearranged (compiler error)
sensor_settings_t right_sensor = {
  .pin = A1,
  .value = 0,
  .avg = {}
};

//the entries should not rearranged (compiler error)
pid_settings_t direction_control = {
  .p = 0.7*0.6,
  .i = (0.7*0.6)/(0.5*1.1),
  .d = 0.125*1.1*0.7*0.6,
  .anti_windup = 50.0,
  .integral = 0.0,
  .last_error = 0.0
};

//the entries should not rearranged (compiler error)
pid_settings_t speed_control = {
  .p = 0.0,
  .i = 0.0,
  .d = 0.0,
  .anti_windup = 0.0,
  .integral = 0.0,
  .last_error = 0.0
};

//the entries should not rearranged (compiler error)
system_settings_t settings = {
  .off_track_detection = 0,
  .idle_speed = 0,
  .plot_analog_readings = false
};

speed_sense_settings_t speed_sense = {
  .pin = 2,
  .time_diff = 0,
  .last_time = 0
};

void setup() {
  setup_uart();
  Serial.begin(9600);
  servo_setup(servo);
  //servo_test(servo);
  motor_setup(motor);
  sensor_setup(left_sensor);
  sensor_setup(right_sensor);
  setup_speed_sense(speed_sense);

  //code needs to be added here
}

int count = 0;

//interrupt for measuring speed from speed sensor
void speed_interrupt() {
  unsigned long now = millis();
  speed_sense.time_diff = now - speed_sense.last_time;
  speed_sense.last_time = now;
  count++;
  //Serial.println(count);

  EIFR = (1 << INTF0);
}


void loop() {
  //code needs to be added here
  float direction = 0;
  sensor_read(left_sensor);
  sensor_read(right_sensor);
  float steer_pid = pid(direction_control, 0.0, right_sensor.value-left_sensor.value);
  Serial.println(right_sensor.value-left_sensor.value);
  steer_pid += 90;
  servo_set_position(servo, steer_pid);

  //motor_set_speed(motor, 30);  // 50% speed
  //delay(1000);
  motor_set_speed(motor, 30); // full speed
  //delay(1000);
  


  if (settings.plot_analog_readings) {
    Serial.print("Left_avg:");
    Serial.print(left_sensor.value);
    Serial.print(",Right_avg:");
    Serial.print(right_sensor.value);
    Serial.print(",Left:");
    Serial.print(analogRead(left_sensor.pin));
    Serial.print(",Right:");
    Serial.print(analogRead(right_sensor.pin));
    Serial.print(",Speed:");
    Serial.print(digitalRead(speed_sense.pin));
    Serial.print(",Controller:");
    Serial.print(direction);
    
    delay(5);
  
    
  }
  //unsigned long dt = speed_sense.time_diff;
  //Serial.print("dt: ");
  //Serial.println(speed_sense.time_diff);
  Serial.print(",Left:");
  Serial.println(analogRead(left_sensor.pin));
  Serial.print(",Right:");
  Serial.println(analogRead(right_sensor.pin));
  Serial.print(",pid:");
  Serial.println(steer_pid);
  
  //code needs to be added here
  handle_serial_input();
}
