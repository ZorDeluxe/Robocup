#include "Arduino.h"
#include "dcMotor.h"
#include <Servo.h>
#include "ir.h"
#include "armServo.h"
#include "lidarServo.h"

Servo myservoA;      // create servo object to control a servo
Servo myservoB;      // create servo object to control a servo

dcMotorclass::dcMotorclass() {
}

void dcMotorclass::setupDCMotor(void) {
  myservoA.attach(5);  // attaches the servo pin 5 to the servo object - Left
  myservoB.attach(4);  // attaches the servo pin 4 to the servo object - Right
  timerMotor = 0;
  timerMotorCheck = 0;
  n = 1;
}

void dcMotorclass::spinCWFast (void) {
  myservoB.writeMicroseconds(2000);      //
  myservoA.writeMicroseconds(1000);      //Spin Fast Clockwise
}

void dcMotorclass::spinCCWFast (void) {
  myservoA.writeMicroseconds(2000);      //Spin Fast Counter-Clockwise
  myservoB.writeMicroseconds(1000);      //
}

void dcMotorclass::turnRightSlow(void) {
  myservoA.writeMicroseconds(1100);
}

void dcMotorclass::turnLeftSlow(void) {
  myservoB.writeMicroseconds(1100);
}

void dcMotorclass::turnRightSlowLidar(void) {
  myservoA.writeMicroseconds(1100);
  myservoB.writeMicroseconds(1900);
}

void dcMotorclass::turnLeftSlowLidar(void) {
  myservoA.writeMicroseconds(1900);
  myservoB.writeMicroseconds(1100);
}

void dcMotorclass::Reverse(void) {
  myservoA.writeMicroseconds(1000);
  myservoB.writeMicroseconds(1000);
}

void dcMotorclass::turnRightFast (void) {
  if (slowDown == 0)
  {
    myservoA.writeMicroseconds(2000);
  } else {
    myservoA.writeMicroseconds(1850);
  }
}

void dcMotorclass::turnLeftFast (void) {
  if (slowDown == 0)
  {
    myservoB.writeMicroseconds(1975);
  } else {
    myservoB.writeMicroseconds(1825);
  }
}

void dcMotorclass::Stop (void) {
  myservoB.writeMicroseconds(1500);      //
  myservoA.writeMicroseconds(1500);      //Spin Fast Clockwise
}

void dcMotorclass::runRobot (void) {

  timerMotor = millis();
  if ((outputValue >= 90) || (!LeftDigIR))
  {
    LeftIR = 1;
  } else {
    LeftIR = 0;
  }
  if (outputValue2 >= 90) 
  {
    MiddleIR = 1;
  }
  else {
    MiddleIR = 0;
  }
  if ((outputValue1 >= 90) || (!RightDigIR))
  {
    RightIR = 1;
  }
  else {
    RightIR = 0;
  }

  if ((!LeftIR && !RightIR && MiddleIR) || (LeftIR && RightIR && MiddleIR))
  {
    Reverse();
    delay(250);
    if (outputValue >= outputValue1)
    {
      spinCWFast();
      delay(250 * n);
    } else
    {
      spinCCWFast();
      delay(250 * n);
    }
    timerMotorCheck = timerMotor;
    n++;
  }
  else {
    if (LeftIR && !RightIR)
    {
      A = 1;
      turnRightSlow();
    }
    else {
      A = 0;
      turnRightFast();
    }

    if (!LeftIR && RightIR)
    {
      B = 1;
      turnLeftSlow();
    }
    else
    {
      B = 0;
      turnLeftFast();
    }
  }

  if ((timerMotor - timerMotorCheck) >= 2500)
  {
    n = 1;
  }
}


dcMotorclass dcMotor = dcMotorclass();
