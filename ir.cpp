#include "Arduino.h"
#include "ir.h"
irclass::irclass(){
}

void irclass::setupIR (void) {
 // Left Front IR
 sensorValue = 0;        // value read from the pot
 outputValue = 0;
 LeftIR = 0;
 
// Right Front IR
 sensorValue1 = 0;
 outputValue1 = 0;
 RightIR = 0;
  
// Middle Front IR
 sensorValue2 = 0;
 outputValue2 = 0;
 MiddleIR = 0;
 A,B = 0;  

 sensorValue3 = 0;
 outputValue3 = 0;
 sensorValue4 = 0;
 outputValue4 = 0;
 sensorValue5 = 0;
 outputValue5 = 0;
 sensorValue6 = 0;
 outputValue6 = 0;  

 // Index of the current readings
 RBotIndex = 0;
 RTopIndex = 0;
 LBotIndex = 0;
 LTopIndex = 0;
 
 // Sum of the circular buffer size
 RBotTotal = 0;
 RTopTotal = 0;
 LBotTotal = 0;
 LTopTotal = 0;

 // Average value of the circular buffers
 RBotAverage = 0;
 RTopAverage = 0;
 LBotAverage = 0;
 LTopAverage = 0;

 // IR 
 LeftDigIR = 1;
 RightDigIR = 1;
 
 // Set the buffer array values to zero
 for (int IRBotCount = 0; IRBotCount < 25; IRBotCount++) {
    IRBotRight[IRBotCount] = 0;
    IRTopRight[IRBotCount] = 0;
    IRBotLeft[IRBotCount] = 0;
    IRTopLeft[IRBotCount] = 0;
  }
}

void irclass::readIR(void){

  // read the analog in value:
  sensorValue = analogRead(LEFT_FRONT_IR);       //The Left-most Sensor
  sensorValue1 = analogRead(RIGHT_FRONT_IR);     //The Central Sensor
  sensorValue2 = analogRead(MIDDLE_FRONT_IR);    //The Right-most Sensor
  sensorValue3 = analogRead(RIGHT_SERVO_TOP_IR); //The Right-most Sensor
  sensorValue4 = analogRead(RIGHT_SERVO_BOT_IR); //The Right-most Sensor
  sensorValue5 = analogRead(LEFT_SERVO_TOP_IR);  //The Right-most Sensor
  sensorValue6 = analogRead(LEFT_SERVO_BOT_IR);  //The Right-most Sensor

  LeftDigIR = digitalRead(LEFTDIGIR);
  RightDigIR = digitalRead(RIGHTDIGIR); 

 
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  outputValue1 = map(sensorValue1, 0, 1023, 0, 255);
  outputValue2 = map(sensorValue2, 0, 1023, 0, 255);  

  // Circular Buffer Calculations
  RBotTotal = RBotTotal - IRBotRight[RBotIndex];
  RTopTotal = RTopTotal - IRTopRight[RTopIndex];
  LBotTotal = LBotTotal - IRBotLeft[LBotIndex];
  LTopTotal = LTopTotal - IRTopLeft[LTopIndex];

  IRTopRight[RTopIndex] = map(sensorValue3, 0, 1023, 0, 255);
  IRBotRight[RBotIndex] = map(sensorValue4, 0, 1023, 0, 255);
  IRTopLeft[LTopIndex] = map(sensorValue5, 0, 1023, 0, 255);
  IRBotLeft[LBotIndex] = map(sensorValue6, 0, 1023, 0, 255);
  
  RBotTotal = RBotTotal + IRBotRight[RBotIndex++];
  RTopTotal = RTopTotal + IRTopRight[RTopIndex++];
  LBotTotal = LBotTotal + IRBotLeft[LBotIndex++];
  LTopTotal = LTopTotal + IRTopLeft[LTopIndex++];

  if (RBotIndex >= CIRC_BUFF_SIZE) {
    // ...wrap around to the beginning:
    RBotIndex = 0;
    RTopIndex = 0;
    LBotIndex = 0;
    LTopIndex = 0;
  }
  
   RBotAverage = RBotTotal / CIRC_BUFF_SIZE;
   RTopAverage = RTopTotal / CIRC_BUFF_SIZE;
   LBotAverage = LBotTotal / CIRC_BUFF_SIZE;
   LTopAverage = LTopTotal / CIRC_BUFF_SIZE;
}

irclass ir = irclass();
