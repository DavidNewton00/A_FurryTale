#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Math.h>


AccelStepper stepper1(AccelStepper::DRIVER, 2, 5); // Define stepper 1 on pins 2 and 5
AccelStepper stepper2(AccelStepper::DRIVER, 3, 6); // Define stepper 2 on pins 3 and 6

int joystickYPin = A0;  // Analog pin for Y-axis of joystick
int joystickXPin = A1;  // Analog pin for X-axis of joystick
int joystickCenter = 512;  // The center position of the joystick


void setup() {
  //Serial.begin(115200);
  stepper1.setMaxSpeed(1000); // Set the maximum speed of stepper 1 in steps per second
  stepper2.setMaxSpeed(1000); // Set the maximum speed of stepper 2 in steps per second

}

void loop() {
  int joystickXValue = analogRead(joystickXPin); // Read the X-axis value of the joystick
  int joystickYValue = analogRead(joystickYPin); // Read the Y-axis value of the joystick

  // Map joystick values to motor speeds for both motors
  int speedX = -map(joystickXValue, 0, 1023, -100, 100);
  int speedY = map(joystickYValue, 0, 1023, -100, 100);

  //calculate magnitude of speed vector created by joystick
  long sqSpeedX = sq(speedX);
  long sqSpeedY = sq(speedY);
  float floatSpeedMag = sqrt(sqSpeedX + sqSpeedY);
  int speedMag = (int)floatSpeedMag;

  //calculate angle of speed vector

  float angleRad = atan2((joystickYValue - 512), (joystickXValue - 512));
  float angleDeg = angleRad * 180.0 / PI;
  if (angleDeg < 0) {
    angleDeg += 360.0;
  }
  
  float theta = angleRad;
  if (angleRad < 0) {
    theta = angleRad += 2*M_PI;  
  }
  float grad = speedY/speedX;
  //float theta = atan(grad);
  //float degree = theta * 180/M_PI;
//  Serial.println("Degree:");
//  Serial.println(angleDeg);
  //M_PI/2
  if (speedMag > 30 ) {
    stepper1.setSpeed(-10*speedMag*sin(theta + M_PI/4));
    stepper2.setSpeed(10*speedMag*sin(theta - M_PI/4));
//    Serial.println("Speed X and Y");
//    Serial.println(10*speedMag*sin(theta + M_PI/4));
//    Serial.println(10*speedMag*sin(theta - M_PI/4));
    //Serial.println(theta + M_PI/2);
    //Serial.println(theta - M_PI/2);
    //delay(1000);

    stepper1.runSpeed();
    stepper2.runSpeed();
  }
}
