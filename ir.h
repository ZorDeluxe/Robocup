#ifndef ir_h
#define ir_h

// These constants won't change. They're used to give names to the pins used:
//const int RightFrontIR = A0;  // Analog input pin that the potentiometer is attached to
//const int LeftFrontIR = A1;
//const int MiddleFrontIR = A2;

#define RIGHT_FRONT_IR    A0
#define LEFT_FRONT_IR     A1
#define MIDDLE_FRONT_IR   A2

#define RIGHT_SERVO_TOP_IR A4
#define RIGHT_SERVO_BOT_IR A5


#define LEFT_SERVO_TOP_IR A10
#define LEFT_SERVO_BOT_IR A11
#define CIRC_BUFF_SIZE 25

#define LEFTDIGIR 12
#define RIGHTDIGIR 13

// Left Front IR
extern int sensorValue, outputValue, sensorValue1, outputValue1, sensorValue2, outputValue2;       // value read from the pot
extern int sensorValue3, outputValue3, sensorValue4, outputValue4, sensorValue5, outputValue5, sensorValue6, outputValue6;
extern bool  LeftIR, RightIR, MiddleIR, A, B;

extern int RBotIndex, RTopIndex, RBotTotal, RTopTotal, RBotAverage, RTopAverage;
static int IRBotRight[CIRC_BUFF_SIZE] = {0};
static int IRTopRight[CIRC_BUFF_SIZE] = {0};

extern int LBotIndex, LTopIndex, LBotTotal, LTopTotal, LBotAverage, LTopAverage;
static int IRBotLeft[CIRC_BUFF_SIZE] = {0};
static int IRTopLeft[CIRC_BUFF_SIZE] = {0};

extern int LeftDigIR, RightDigIR;

class irclass{
  public:
  irclass();
  void setupIR();
  void readIR();
};

extern irclass ir;

#endif
