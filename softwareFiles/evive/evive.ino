/*
 * This firmware is developed for evive [http://evive.cc].
 * This is licensed under Creative Commons 4.0
 * Written by Dhrupal R Shah and Akshat Agarwal for Agilo Technology.
 * Last update: 2016, Aug 20
 * 
 * NOTE: Works with Arduino IDE 1.6.6 or later [https://www.arduino.cc/en/Main/Software]
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
