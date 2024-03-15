#ifndef armServo_h
#define armServo_h

//const int leftArmServoPin = 11;
//const int rightArmServoPin = 10;
//const int analogInPin = A6;

#define LEFT_ARM_SERVO_PIN      11
#define RIGHT_ARM_SERVO_PIN     10
#define SERVO_ANALOG_IN_PIN     A6


extern int servoOpen, servoSensValue, servoIROutput, servoCalibrated;
extern int time1, time2, time3, time6, count5, start0, slowDown;

class armServoclass{
	public:
	armServoclass();
	void setupArmServo();
	void calibrateArmServo();
	void runArmServo();
};

extern armServoclass armServo;

#endif
