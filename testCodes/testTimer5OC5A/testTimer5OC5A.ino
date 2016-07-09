/*
 *  Timer5 library example
 *  June 2008 | jesse dot tane at gmail dot com
 */
     
#include "TimerFive.h"

#define ledPin 13
#define timerPin 46     
void setup()
{
   pinMode(ledPin, OUTPUT);
   pinMode(timerPin, OUTPUT);
   Timer5.initialize(1000);         // initialize timer1, and set a 1 milli second period
   Timer5.pwm(46, 512);                // setup pwm on pin 9, 50% duty cycle
   Timer5.attachInterrupt(callback);  // attaches callback() as a timer overflow interrupt
}
     
void callback()
{
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
}
     
void loop()
{
  // your program here...
}
     

