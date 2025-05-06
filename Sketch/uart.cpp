/////////////////////////////////////////////////////////
///// This file does not need any modification, /////////
///// if needed it can be extended with more handlers ///
///////////////////////////////////////////////////////// 

#include "uart.h"

void getMotorP(double inputNumber){
  Serial.print("motorControl P = ");
  Serial.println(uartControl.motorControl->getControllerP());
  Serial.flush();//wait for outgoing serial transmission to end
}
void getMotorI(double inputNumber){
  Serial.print("motorControl I = ");
  Serial.println(uartControl.motorControl->getControllerI());
  Serial.flush();//wait for outgoing serial transmission to end
}
void getMotorD(double inputNumber){
  Serial.print("motorControl D = ");
  Serial.println(uartControl.motorControl->getControllerD());
  Serial.flush();//wait for outgoing serial transmission to end
}
void setMotorP(double inputNumber){
  uartControl.motorControl->setControllerP(inputNumber);
  getMotorP(inputNumber);
}
void setMotorI(double inputNumber){
  uartControl.motorControl->setControllerI(inputNumber);
  getMotorI(inputNumber);
}
void setMotorD(double inputNumber){
  uartControl.motorControl->setControllerD(inputNumber);
  getMotorD(inputNumber);
}


void getDirP(double inputNumber){
  Serial.print("directionControl P = ");
  Serial.println(uartControl.directionControl->getControllerP());
  Serial.flush();//wait for outgoing serial transmission to end
}
void getDirI(double inputNumber){
  Serial.print("directionControl I = ");
  Serial.println(uartControl.directionControl->getControllerI());
  Serial.flush();//wait for outgoing serial transmission to end
}
void getDirD(double inputNumber){
  Serial.print("directionControl D = ");
  Serial.println(uartControl.directionControl->getControllerD());
  Serial.flush();//wait for outgoing serial transmission to end
}
void setDirP(double inputNumber){
  uartControl.directionControl->setControllerP(inputNumber);
  getDirP(inputNumber);
}
void setDirI(double inputNumber){
  uartControl.directionControl->setControllerI(inputNumber);
  getDirI(inputNumber);
}
void setDirD(double inputNumber){
  uartControl.directionControl->setControllerD(inputNumber);
  getDirD(inputNumber);
}

void help(double inputNumber){
  Serial.println("BEGIN OF HELP");
  Serial.println("");
  Serial.println("Commands must be terminated with ;!");
  Serial.println("With set command the value comes immidiately after command!");
  Serial.println("Example: setDirP12.5;");
  Serial.println("");
  Serial.println("Available commands:");
  Serial.println("getMotorP: get P of motor control");
  Serial.println("getMotorI: get I of motor control");
  Serial.println("getMotorD: get D of motor control");
  Serial.println("setMotorP: set P of motor control");
  Serial.println("setMotorI: set I of motor control");
  Serial.println("setMotorD: set D of motor control");
  Serial.println("getDirP: get P of direction control");
  Serial.println("getDirI: get I of direction control");
  Serial.println("getDirD: get D of direction control");
  Serial.println("setDirP: set P of direction control");
  Serial.println("setDirI: set I of direction control");
  Serial.println("setDirD: set D of direction control");
  Serial.println("help: show help");
  Serial.println("");
  Serial.println("END OF HELP");
  Serial.flush();//wait for outgoing serial transmission to end
}

//the following two arrays have to have the SAME number of elements each command corrosbinding to one function pointer
//list of commands
const char *callbackName[] = {"getDirP","getDirI","getDirD","setDirP","setDirI","setDirD","getMotorP","getMotorI","getMotorD","setMotorP","setMotorI","setMotorD","help"};
//list of function pointer from above
void (*callbackFunc[])(double inputNumber) = {getDirP,getDirI,getDirD,setDirP,setDirI,setDirD,getMotorP,getMotorI,getMotorD,setMotorP,setMotorI,setMotorD,help};



//////////////////////////////////////////////////////
//////////before this only handler functions /////////
//////////////////////////////////////////////////////


void initUart(DirectionControl* directionControlIn, MotorControl* motorControlIn){
  uartControl.directionControl = directionControlIn;
  uartControl.motorControl = motorControlIn;

  
  Serial.begin(9600); // for serial communication
  while (!Serial){;}//wait for serial to be available

  Serial.println("Beginning Serial Transmission");
  Serial.flush();//wait for outgoing serial transmission to end
  
}

void handleSerialInput(){
  uartControl.intCallbackCount = sizeof(callbackFunc)/sizeof(callbackFunc[0]);

    
    if(Serial.available()>0){
      char c = Serial.read();
      if (c != CMD_END && uartControl.bufferPos < BUFFER_SIZE) {
        uartControl.inputBuffer[uartControl.bufferPos++] = c;
      } else {
          //Serial.println(byteBuffer);
          for (int i = 0; i < uartControl.intCallbackCount; i++) {

            if (strncmp(callbackName[i], uartControl.inputBuffer, strlen(callbackName[i])) == 0) {
              double num = atof(uartControl.inputBuffer+strlen(callbackName[i]));
              callbackFunc[i](num);
              break;
            }
          }
          memset(uartControl.inputBuffer,0,BUFFER_SIZE);
          uartControl.bufferPos = 0;
      
      }
    }

}
