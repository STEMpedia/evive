/*
 * servoControl.cpp
 *
 *  Created on: May 6, 2016
 *      Author: dhrups
 */
#include "servoControl.h"

Servo servo1, servo2;
int prevAngleServo1, prevAngleServo2;

void controlServo(){
	Serial.println("ServoCtrl");
	 if(_SERVO1_EN)
	 { prevAngleServo1 = servo1.read();
	 	 servo1.write(int(map(pot1.getValue(),0, 1023, 0, 170)));
	 	 //Serial.println(servo1.read());
	 }
	 if(_SERVO2_EN)
	 { prevAngleServo2 = servo2.read();
		 servo2.write(int(map(pot2.getValue(),0, 1023, 0, 170)));
	 }
}

int prevValueServo1(){
	return prevAngleServo1;
}

int prevValueServo2(){
	return prevAngleServo2;
}

void addServo1(){
	_SERVO1_EN = 1;
	_POT1_OUTPIN = SERVO1_ATTACH;
	servo1.attach(SERVO1_ATTACH);
	actionAdd(controlServo, 1);
  prevAngleServo1 = servo1.read();
  prevAngleServo2 = servo2.read();
}

void addServo2(){
	_SERVO2_EN = 1;
	_POT2_OUTPIN = SERVO2_ATTACH;
	servo2.attach(SERVO2_ATTACH);
	actionAdd(controlServo, 1);
  prevAngleServo1 = servo1.read();
  prevAngleServo2 = servo2.read();
}

void addServo12(){
	addServo1();
	addServo2();
}
