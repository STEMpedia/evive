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
