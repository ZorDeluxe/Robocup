#ifndef dcMotor_h
#define dcMotor_h

extern int timerMotorCheck, timerMotor, n;

class dcMotorclass{
	public:
	dcMotorclass();
	void setupDCMotor();
  void spinCWFast();
  void spinCCWFast();
  void turnRightSlow();
  void turnLeftSlow();
  void turnRightSlowLidar();
  void turnLeftSlowLidar();
  void Reverse();
  void turnRightFast();
  void turnLeftFast();
  void runRobot();
  void Stop();
};

extern dcMotorclass dcMotor;

#endif
