#include "Arduino.h"
#include "stepperMotor.h"
#include "dcMotor.h"

fclass::fclass() {
}


void fclass::setupStepper(void) {
  //Setup step and direction pin for output
  pinMode(M1dirpin, OUTPUT);
  pinMode(M1steppin, OUTPUT);
  digitalWrite(M1steppin, LOW);

  pinMode(M2dirpin, OUTPUT);
  pinMode(M2steppin, OUTPUT);
  digitalWrite(M2steppin, LOW);

  weightStoredBack, weightStoredFront = 0;
}

void fclass::runMotor(void) {
  if (weightStoredBack == 0)
  {
    digitalWrite(M1steppin, LOW);
    delayMicroseconds(650);
    digitalWrite(M1steppin, HIGH);
    delayMicroseconds(650);
  }
  else
  {
    digitalWrite(M2steppin, LOW);
    delayMicroseconds(650);
    digitalWrite(M2steppin, HIGH);
    delayMicroseconds(650);
  }
}

void fclass::collectWeight(void) {
  //Set direction
  dcMotor.Stop();
  if (weightStoredBack == 0)
  {
    digitalWrite(M1dirpin, HIGH);
    int j;
    for (j = 0; j <= 3750; j++)     //Move 1000 steps
    {
      stepperMotor.runMotor();
    }
    digitalWrite(M1steppin, LOW);
    collectWeightNow = 0;
    weightStoredBack = 1;
  }
  else
  {
    digitalWrite(M2dirpin, HIGH);
    int j;
    for (j = 0; j <= 3750; j++)     //Move 1000 steps
    {
      stepperMotor.runMotor();
    }
    digitalWrite(M2steppin, LOW);
    collectWeightNow = 0;
  }
}

fclass stepperMotor = fclass();
