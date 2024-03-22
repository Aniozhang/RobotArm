/* Include the HCPCA9685 library */
#include "HCPCA9685.h"

/* I2C slave address for the device/module. For the HCMODU0097 the default I2C address
   is 0x40 */
#define  I2CAdd 0x40


/* Create an instance of the library */
HCPCA9685 HCPCA9685(I2CAdd);


void setup() 
{
  Serial.begin(9600);
  /* Initialise the library and set it to 'servo mode' */ 
  HCPCA9685.Init(SERVO_MODE);

  /* Wake the device up */
  HCPCA9685.Sleep(false);
}

// min and max values. 
const unsigned int MINValue = 10; // 0 degress 
const unsigned int MAXValue = 450; // 180 degrees
const unsigned int MIDValue = (MINValue + MAXValue)/2; // 90 degress


// Utility function to do some mapping.
int mapAngles(float angle) {
  return (int) map(angle,0, 180, MINValue, MAXValue);
}


// Function to open the gripper.
void closeArm() {
  HCPCA9685.Servo(0, mapAngles(30));
}


// Function to close the gripper.
void openArm() {
  HCPCA9685.Servo(0, mapAngles(120));
}

void moveElbow(float angle) {
  Serial.println(angle);
  if (angle >= 135.0) {
    angle = 135.0;
  }
  if (angle <= 45.0) {
    angle = 45.0;
  }
  HCPCA9685.Servo(1, mapAngles(angle));
}

void moveShoulder(float angle) {
  Serial.println(angle);
  if (angle >= 120.0) {
    angle = 120.0;
  }
  if (angle <= 0.0) {
    angle = 0.0;
  }
  HCPCA9685.Servo(2, mapAngles(angle));
}

void moveChest(float angle) {
  Serial.println(angle);
  if (angle >= 180.0) {
    angle = 180.0;
  }
  if (angle <= 0.0) {
    angle = 0.0;
  }
  HCPCA9685.Servo(3, mapAngles(angle));
}

char t;
int c=90,s=60,e=90;

int precision = 5;

void loop() 
{
  if(Serial.available()){
    t = Serial.read();
    Serial.println(t);
  }


  switch(t) {
    case 'O':
      Serial.print("Open\n");
      openArm();
      break;
    case 'C':
      Serial.print("Close\n");
      closeArm();
      break;
    //COUNTER CLOCKWISE
    case 'W':
      if (c < 180 && c > 0) {
          c += precision;
          moveChest(c);
      }
      break;
    //CLOCKWISE
    case 'S':
      if (c < 180 && c > 0) {
          c -= precision;
          moveChest(c);
      } 
      break;
    //
    case 'A':
      if (s < 120 && s > 0) {
          s += precision;
          moveShoulder(s);
      }
      break;
    //MOVE THE WHOLE PART BACKWORDS
    case 'D':
      if (s < 120 && s > 0) {
          s -= precision;
          moveShoulder(s);
      } 
      break;
    //MOVE UP
    case 'K':
      if (e < 135 && e > 45) {
          e += precision;
          moveElbow(e);
      }
      break;
    //MOVE DOWN
    case 'L':
      if (e < 135 && e > 45) {
          e -= precision;
          moveElbow(e);
      } 
      break;
  }  
  // moveElbow(90);
  // moveShoulder(45);
  // moveChest(0);
  // delay(1000);

  // moveElbow(90);
  // moveShoulder(120);
  // moveChest(0);
  // delay(1000);
}
