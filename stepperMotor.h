
#ifndef stepperMotor_h
#define stepperMotor_h

const int M1dirpin = 45;
const int M1steppin = 42;

const int M2dirpin = 32;
const int M2steppin = 30;

extern volatile int weightStoredBack, weightStoredFront, weightOneCollected, collectWeightNow;


class fclass{
	public:
	fclass();
	void setupStepper();
	void runMotor();
  void collectWeight();
};

extern fclass stepperMotor;

#endif
