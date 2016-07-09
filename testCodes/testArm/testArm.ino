/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
#include <Stepper.h>

Servo servo1, servo2, servo3, servo4;  // create servo object to control a servo
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
Stepper myStepper(stepsPerRevolution, 28, 29, 30, 31);

#define servo1Pin 2
#define servo2Pin 3
#define servo3Pin 4
#define servo4Pin 5
#define tactile1Pin 38
#define tactile2Pin 39
#define pot1  A9
#define pot2  A10
#define slideSw1D1 40
#define slideSw1D2 41
#define slideSw2D1 42
#define slideSw2D2 43

int posStepper = 0;    // variable to store the servo position

void setup() {
  servo1.attach(servo1Pin);  // attaches the servo on pin 9 to the servo object
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin);
  pinMode(tactile1Pin, INPUT);
  pinMode(tactile2Pin, INPUT);
  pinMode(slideSw1D1, INPUT);
  pinMode(slideSw1D2, INPUT);
  pinMode(slideSw2D1, INPUT);
  pinMode(slideSw2D2, INPUT);  
}


void loop() {
  servo1.write(map(analogRead(pot1), 0, 1023, 0, 180));
  servo2.write(map(analogRead(pot2), 0, 1023, 0, 180));
  if(digitalRead(slideSw1D1)) { servo3.write(50);}
  if(digitalRead(slideSw1D2)) { servo3.write(90);}
  if(digitalRead(slideSw2D1)) { myStepper.step(10);}
  if(digitalRead(slideSw2D2)) { myStepper.step(-10);}
  delay(100);
}

