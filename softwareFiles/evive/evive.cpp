/*
 * evive.cpp
 * Created on: April 16, 2016
 * Author: dhrups
 * Last update: May 10, 2016
 * Version: 1.0
 */
#include "evive.h"

void setup(){
	Serial.begin(BAUDRATE);
	Serial.println("In the setup loop now");
	lcd_init();

	setPinModeDefault();
	Serial.println("setup ends");
}

void loop(){
	lcd_update();
	action();
}
