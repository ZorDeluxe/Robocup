#ifndef lidarServo_h
#define lidarServo_h

//const int leftLidarServoPin = 7;
//const int rightLidarServoPin = 6;
const int rightServoAngles[4] = {65, 95, 125, 155};
const int leftServoAngles[4] =  {180, 150, 120, 80};

#define LEFT_LIDAR_SERVO_PIN    7
#define RIGHT_LIDAR_SERVO_PIN   6

extern int timerLidarSet, timerLidar, iLidar, weightFoundRight, LidarCount, timerCheck, FirstCheck, timerCheck2, stopped, watchDog;
extern int weightFoundLeft, FirstCheck1, timerCheck3, timerCheck4;

class lidarServoclass{
  public:
  lidarServoclass();
  void setupLidarServo();
  void runLidarServo();
};

extern lidarServoclass lidarServo;

#endif
