#ifndef  SERVO_CONTROL_H
#define  SERVO_CONTROL_H

#include "evive.h"
#include <Servo.h>

extern Servo servo1, servo2;

void controlServo();			//auto motor control from pots and slide switches
void addServo1();
void addServo2();
void addServo12();
int prevValueServo1();
int prevValueServo2();

#endif
