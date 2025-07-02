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
  .p = 0.42,//startpunkt: 0.42
  .i = 0.7636,//startpunkt: 0.7636
  .d = 0.05775, //startpunkt: 0.05775
  .anti_windup = 50.0,
  .integral = 0.0,
  .last_error = 0.0,
  .clamp = 1,
  .last_Time = millis(),
  .T = 1.0
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
  .last_time = 0,
  .last_state = 0
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
  int state = digitalRead(speed_sense.pin);
  //Serial.println(state);
  if(state != speed_sense.last_state){
    count++;
    unsigned long now = millis();
    speed_sense.time_diff = now - speed_sense.last_time;
    speed_sense.last_time = now;
    speed_sense.last_state = state;
    //Serial.println(count);
  }
}

float loopTime = 0;

void loop() {
  //code needs to be added here
  
  float direction = 0;
  sensor_read(left_sensor);
  sensor_read(right_sensor);
  direction_control.T = (millis() - direction_control.last_Time)/1000;
    
  int max_speed = 30;
  int min_speed = 30;
  /* TEST MIT DAMPING
  float steer_pid = pid(direction_control, 0.0, right_sensor.value-left_sensor.value);
  direction_control.last_Time = millis();
  
  //Verlangsamung bei großem fehler
  float norm_steer = min(1.0, abs(steer_pid) / direction_control.anti_windup);
  int motor_speed = max_speed - pow(norm_steer, 1.5) * (max_speed - min_speed);
  motor_set_speed(motor, motor_speed); // full speed

  //dämpfung bei hohen geschwindigkeiten
  float speed_factor = (float)(motor_speed - min_speed) / (max_speed - min_speed);
  float steer_damping = 1.0 - 0.3 * speed_factor;
  float final_steer = steer_pid * steer_damping + 90;
  
  steer_pid += 90;
  if(right_sensor.value + left_sensor.value > 50){
    servo_set_position(servo, final_steer);
  }
  */
  //motor_set_speed(motor, max_speed);  // 50% speed
  //delay(1000);
  
  //delay(1000);
  //PID FUNKTIONIERT
  float steer_pid = pid(direction_control, 0.0, right_sensor.value-left_sensor.value);
  direction_control.last_Time = millis();

  steer_pid += 90;
  if(right_sensor.value + left_sensor.value > 50){
  servo_set_position(servo, steer_pid);
  }
  motor_set_speed(motor, 30); // full speed

  


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
  Serial.print("T:");
  
  Serial.println(direction_control.T);
  
  //code needs to be added here
  handle_serial_input();
  
}
