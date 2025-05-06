/////////////////////////////////////////////////////////
///// This file does not need any modification, /////////
///// if needed it can be extended //////////////////////
///////////////////////////////////////////////////////// 
#pragma once
#include "Arduino.h"
#include "DirectionControl.h"
#include "motorControl.h"


#define BUFFER_SIZE 50
#define CMD_END ';'

struct{
  char inputBuffer[BUFFER_SIZE];
  uint8_t bufferPos;
  uint8_t voidCallbackCount;//number of callback function (will be auto initiated)
  uint8_t intCallbackCount;//number of callback function (will be auto initiated)
  DirectionControl* directionControl;
  MotorControl* motorControl;
}uartControl = {{0},0,0};


void initUart(DirectionControl*, MotorControl*);
void handleSerialInput(void);
