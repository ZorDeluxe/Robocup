#include "Arduino.h"
#include "armServo.h"
#include "Servo.h"
#include "dcMotor.h"

Servo leftServo, rightServo;

armServoclass::armServoclass() {
}

void armServoclass::setupArmServo (void) {
  // We need to attach the servo to the used pin number
  leftServo.attach(LEFT_ARM_SERVO_PIN);
  rightServo.attach(RIGHT_ARM_SERVO_PIN);
  servoOpen = 0;
  servoSensValue = 0;
  servoIROutput = 0;
  servoCalibrated = 0;
  slowDown = 0;
  count5 = 0;
  time6 = 0;

}

void armServoclass::calibrateArmServo (void) {
  leftServo.write(42);
  delay(50);
  rightServo.write(100);
  delay(50);
  servoCalibrated = 1;
}

void armServoclass::runArmServo (void) {
  time1 = millis();
  servoSensValue = analogRead(SERVO_ANALOG_IN_PIN);
  servoIROutput = map(servoSensValue, 0, 1023, 0, 255);

  if ((servoOpen == 0) && (servoIROutput >= 140))
  {
    rightServo.write(55);
    leftServo.write(100);
    if (count5 < 1) 
    {
      dcMotor.Stop();
      time6 = time1;
    }
    delay(1000);
    servoOpen = 1;
    count5++;
  }

  // Servo Arms Close
  if (servoOpen == 1 && servoIROutput <= 140)
  {
    rightServo.write(100);
    leftServo.write(42);
    servoOpen = 0;
  }

  if ((time1 - time3) > 5000)
  {
   slowDown = 0;
  }

  if ((time1 - time6) >= 4000)
  {
    count5 = 0;
  }
}

armServoclass armServo = armServoclass();
