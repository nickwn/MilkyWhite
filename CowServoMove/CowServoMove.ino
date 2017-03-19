#include <SoftwareSerial.h>
#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN 150
#define SERVOMAX 600

enum class Direction {FORWARD, BACKWARD, STOPPED};

struct CowServo 
{
  int pin;
  int pos;
  int low;
  int high;
  int spd;
  bool shouldStop;
  Direction dir;
};

Adafruit_PWMServoDriver pwm;
SoftwareSerial bt(50, 51);
Servo lMotor;
Servo rMotor;

CowServo lEar = {0, 60, 0, 180, 2, false, Direction::STOPPED};
CowServo rEar = {1, 120, 0, 80, 2, false, Direction::STOPPED};
CowServo lEye = {2, 60, 60, 120, 2, false, Direction::STOPPED};
CowServo rEye = {3, 60, 60, 120, 2, false, Direction::STOPPED};
CowServo lEyeL = {4, 60, 60, 120, 2, false, Direction::STOPPED};
CowServo rEyeL = {5, 60, 60, 120, 2, false, Direction::STOPPED};
CowServo tail = {6, 60, 60, 150, 2, false, Direction::STOPPED};
CowServo cowServos[] = {lEar, rEar, lEye, rEye, lEyeL, rEyeL, tail};

int timeOfLastMsg = 0;
void setup() 
{
  bt.begin(9600);
  Serial.begin(9600);
  Serial.println("setting up");
  lMotor.attach(49);
  rMotor.attach(48);
  pwm.begin();
  pwm.setPWMFreq(60);
  while(!bt.available());
  bt.print("connected");
  Serial.print("connected");
  timeOfLastMsg = millis();
}

void loop() 
{
  if(bt.available())
  {
    timeOfLastMsg = millis();
    char msg = (char)bt.read();
    Serial.println(msg);
    switch(msg)
    {
    case 'F':
      lMotor.writeMicroseconds(1300);
      rMotor.writeMicroseconds(1700);
      break;
    case 'B':
      lMotor.writeMicroseconds(1700);
      rMotor.writeMicroseconds(1300);
      break;
    case 'L':
      lMotor.writeMicroseconds(1300);
      rMotor.writeMicroseconds(1300);
      break;
    case 'R':
      lMotor.writeMicroseconds(1700);
      rMotor.writeMicroseconds(1700);
      break;
    case 'S':
      lMotor.writeMicroseconds(1500);
      rMotor.writeMicroseconds(1500);
      break;
    }
  }
  else
  {
    if(millis()-timeOfLastMsg > 500)
    {
      bt.println("exiting");
      Serial.println("exiting");
      lMotor.writeMicroseconds(1500);
      rMotor.writeMicroseconds(1500);
      exit(1);
    }
  }

  int r = random(0,200000);
  switch(r)
  {
  case 0:
    cowServos[0].dir = Direction::FORWARD;
    cowServos[1].dir = Direction::BACKWARD;
    break;
  case 1:
    cowServos[2].dir = Direction::FORWARD;
    cowServos[3].dir = Direction::BACKWARD;
  case 2:
    cowServos[4].dir = Direction::BACKWARD;
    cowServos[5].dir = Direction::FORWARD;
  case 3:
    cowServos[6].dir = Direction::FORWARD;
  }

  for(int i = 0; i < 7; i++)
  {
    updateMovement(i);
  }
}

void updateMovement(int i)
{
  if(cowServos[i].dir == Direction::FORWARD)
  {
    pwmServoWrite(cowServos[i].pin, ++cowServos[i].pos, cowServos[i].spd);
    if(cowServos[i].pos >= cowServos[i].high)
    {
      if(cowServos[i].shouldStop)
        cowServos[i].dir = Direction::STOPPED;
      else
      {
        cowServos[i].dir = Direction::BACKWARD;
        cowServos[i].shouldStop = true;
      }
    }
       
  }
  else if(cowServos[i].dir == Direction::BACKWARD)
  {
    pwmServoWrite(cowServos[i].pin, --cowServos[i].pos, cowServos[i].spd);
    if(cowServos[i].pos <= cowServos[i].low)
    {
      if(cowServos[i].shouldStop)
        cowServos[i].dir = Direction::STOPPED;
      else
      {
        cowServos[i].dir = Direction::FORWARD;
        cowServos[i].shouldStop = true;
      }
    }
  }
  else
  {
    cowServos[i].shouldStop = false;
  }
}


void pwmServoWrite(int pin, int pos, int spd)
{
  pwm.setPWM(pin, 0, map(pos, 0, 180, SERVOMIN, SERVOMAX));
}

