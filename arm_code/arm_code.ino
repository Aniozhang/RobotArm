/* Include the HCPCA9685 library */
#include "HCPCA9685.h"

/* I2C slave address for the device/module. For the HCMODU0097 the default I2C address
   is 0x40 */
#define  I2CAdd 0x40


/* Create an instance of the library */
HCPCA9685 HCPCA9685(I2CAdd);


void setup() 
{
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
void openArm() {
  HCPCA9685.Servo(0, mapAngles(30));
}


// Function to close the gripper.
void closeArm() {
  HCPCA9685.Servo(0, mapAngles(120));
}

void moveElbow(float angle) {
  if (angle >= 135.0) {
    angle = 135.0;
  }
  if (angle <= 45.0) {
    angle = 45.0;
  }
  HCPCA9685.Servo(1, mapAngles(angle));
}

void moveShoulder(float angle) {
  if (angle >= 120.0) {
    angle = 120.0;
  }
  if (angle <= 0.0) {
    angle = 0.0;
  }
  HCPCA9685.Servo(2, mapAngles(angle));
}

void moveChest(float angle) {
  if (angle >= 180.0) {
    angle = 180.0;
  }
  if (angle <= 0.0) {
    angle = 0.0;
  }
  HCPCA9685.Servo(3, mapAngles(angle));
}

void loop() 
{
  openArm();
  moveElbow(90);
  moveShoulder(45);
  moveChest(0);
  delay(1000);

  closeArm();
  moveElbow(90);
  moveShoulder(120);
  moveChest(0);
  delay(1000);
}
