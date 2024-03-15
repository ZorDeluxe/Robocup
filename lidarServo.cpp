#include "Arduino.h"
#include "lidarServo.h"
#include "Servo.h"
#include "ir.h"

Servo leftLidarServo, rightLidarServo;

lidarServoclass::lidarServoclass() {
}

void lidarServoclass::setupLidarServo (void)
{
  // Setting the pins for the Servos
  leftLidarServo.attach(LEFT_LIDAR_SERVO_PIN);
  rightLidarServo.attach(RIGHT_LIDAR_SERVO_PIN);

  // Counting up on the angles
  iLidar = 0;
  LidarCount = 0;
  timerLidarSet = 1000;
  
  timerCheck = 0;
  timerCheck2 = 0;
  timerCheck3 = 0;
  timerCheck4 = 0;
  
  FirstCheck = 0;
  FirstCheck1 = 0;
  
  stopped = 0;
  watchDog = 0;
  
  // Weight Detection
  weightFoundRight = 0;
  weightFoundLeft = 0;
}

void lidarServoclass::runLidarServo (void)
{
  timerLidar = millis();
  
  // Checks if a weight was found on the right side of the robot
  if (((RBotAverage - RTopAverage) >= 70) && (!RightIR) && (FirstCheck == 0) && (((timerLidar - timerCheck2) >= 300) || (watchDog == 1)) && (!weightFoundLeft))
  {
    rightLidarServo.write(170);
    weightFoundRight = 1;
    FirstCheck = 1;
    timerCheck = timerLidar;
    watchDog = 0;
  }

    //  Checks if a weight was found on the left of the robot
  if (((LBotAverage - LTopAverage) >= 70) && (!LeftIR) && (FirstCheck1 == 0) && (((timerLidar - timerCheck4) >= 300) || (watchDog == 1)) && (!weightFoundRight))
  {
    leftLidarServo.write(55);
    weightFoundLeft = 1;
    FirstCheck1 = 1;
    timerCheck3 = timerLidar;
    watchDog = 0;
  }

  // Recheck - Right
  if ((weightFoundRight) && (timerLidar - timerCheck >= 300) && ((RBotAverage - RTopAverage) >= 70) && (!RightIR))
  {
    weightFoundRight = 0;
    FirstCheck = 0;
    timerCheck2 = timerLidar;
    stopped = 0;
    watchDog = 0;
  }

  // Recheck - Left
  if ((weightFoundLeft) && (timerLidar - timerCheck3 >= 300) && (((LBotAverage - LTopAverage) >= 70) && (!LeftIR)))
  {
    weightFoundLeft = 0;
    FirstCheck1 = 0;
    timerCheck4 = timerLidar;
    stopped = 0;
  }
  
  if ((weightFoundRight) && (timerLidar - timerCheck >= 3000) && (watchDog == 0))
  {
    weightFoundRight = 0;
    watchDog = 1;
    FirstCheck = 0;
  }

    if ((weightFoundLeft) && (timerLidar - timerCheck3 >= 3000) && (watchDog == 0))
  {
    weightFoundLeft = 0;
    watchDog = 1;
    FirstCheck1 = 0;
  }
  
  if (((timerLidar - timerLidarSet) >= 250) && (!weightFoundRight && !weightFoundLeft))
  {
    timerLidarSet = timerLidar;
    rightLidarServo.write(rightServoAngles[iLidar]);
    leftLidarServo.write(leftServoAngles[iLidar++]);
    if (iLidar >= 4) {
      iLidar = 0;
    }
  }
}

lidarServoclass lidarServo = lidarServoclass();
