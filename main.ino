/*
  This is the main code for the project.
  The header files are all the modules for the sensors and actuators.
*/
#include "Arduino.h"
#include "armServo.h"
#include "dcMotor.h"
#include "ir.h"
#include "lidarServo.h"
#include "stepperMotor.h"

volatile int weightStoredBack = 0;                       // The back weight has been collected
volatile int weightStoredFront = 0;                      // The front weight has been collected
volatile int weightOneCollected = 0;
volatile int weightStored = 0;
volatile int backWeightCollected = 0;

// Weight collection interupt variables
volatile int collectWeightNow = 0;
int calibration = 0;

// Call the external global IR bstacle navigation variables
int sensorValue, outputValue, sensorValue1, outputValue1, sensorValue2, outputValue2;
int sensorValue3, outputValue3, sensorValue4, outputValue4, sensorValue5, outputValue5, sensorValue6, outputValue6;
bool LeftIR, RightIR, MiddleIR;
bool A, B;

// Circular Buffer for Lidar
int RBotIndex, RTopIndex, RBotTotal, RTopTotal, RBotAverage, RTopAverage;
int LBotIndex, LTopIndex, LBotTotal, LTopTotal, LBotAverage, LTopAverage;
int LeftDigIR, RightDigIR;

// Servo Arm variables
int servoCalibrated, angle1, angle2, servoSensValue, servoIROutput, servoOpen;
int time1, time2, time3, time6, count5, start0, slowDown;

// Interrupts Globals
int risingEdgePin = 2;
int fallingEdgePin = 3;
int digitalProxyPin = 21;

// DC motor control
int timerMotorCheck, timerMotor, n;

// Lidar IR Global Variables
int timerLidarSet, timerLidar, iLidar, weightFoundRight, LidarCount, timerCheck, FirstCheck, timerCheck2, watchDog;
int weightFoundLeft, FirstCheck1, timerCheck3, timerCheck4;
int stopped = 0;

// Celebration Scheme
int weightsCollected = 0;
void setup()
{
  // Given setup
  pinMode(49, OUTPUT);                 //Pin 49 is used to enable IO power
  digitalWrite(49, 1);                 //Enable IO power on main CPU board

  // Module Set-ups
  stepperMotor.setupStepper();
  dcMotor.setupDCMotor();
  ir.setupIR();
  armServo.setupArmServo();
  lidarServo.setupLidarServo();

  // Interrupt Set-ups
  pinMode(risingEdgePin, INPUT);
  pinMode(fallingEdgePin, INPUT);
  pinMode(digitalProxyPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(risingEdgePin), proxyIntRising, RISING);
  attachInterrupt(digitalPinToInterrupt(fallingEdgePin), proxyIntFalling, FALLING);
  attachInterrupt(digitalPinToInterrupt(digitalProxyPin), digitalProxTrigger, FALLING);

  Serial.begin(9600);
}

void loop()
{
  if (!servoCalibrated) {
    armServo.calibrateArmServo();       // Run calibration for the funnel arm servos
    for (int b = 0; b < 25; b++) {
      ir.readIR();                          // See if there
    }
  }
  ir.readIR();                          // See if there are obstacles
  armServo.runArmServo();               // Start looping for arm servos
  if (collectWeightNow && (weightsCollected <= 1)) {
    stepperMotor.collectWeight();       // Weight collection from interrupts
    weightsCollected++;
  }
  lidarServo.runLidarServo();           // Try to find a weight
  
  if (weightFoundRight || weightFoundLeft)
  {
    if (stopped == 0)
    {
      dcMotor.Stop();
      delay(100);
      stopped = 1;
    }
    if (weightFoundRight)
    {
      dcMotor.turnRightSlowLidar();
    }
    if (weightFoundLeft)
    {
      dcMotor.turnLeftSlowLidar();
    }
  } else {
    dcMotor.runRobot();                   // Run it straight
  }

  Serial.println(outputValue2);
}


void proxyIntRising (void) {            // Rising edge trigger proxy for front weight

  if (weightStoredBack == 1) {
    dcMotor.Stop();
    collectWeightNow = 1;
  }
}

void proxyIntFalling (void) {           // Falling edge trigger for back weight

  if (!weightStoredBack) {
    dcMotor.Stop();
    collectWeightNow = 1;
  }
}

void digitalProxTrigger (void) {        // Digital proxy interrupt to slow robot down
  slowDown = 1;
  time3 = time1;
}
