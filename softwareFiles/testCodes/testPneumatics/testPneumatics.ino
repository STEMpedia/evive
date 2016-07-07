#include <motor.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

Motor pneumatics1(28,29,44);
Motor pneumatics2(30,31,45);
#define TFT_CS     48
#define TFT_RST    47 // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     49
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

void setup() {

  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(1);
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
  tft.setTextSize(2);
  tft.setCursor(0,40);
  tft.print("Cylinder1");
  tft.setCursor(0,80);
  tft.print("Cylinder2");
  tft.setTextColor(ST7735_YELLOW
  
  
  , ST7735_BLACK);
}

#define TIME1 300
void loop() {
  pneumatics2.freeMotor();
  pneumatics1.moveMotor(255);
  tft.setCursor(120,40);
  tft.print("OUT");
  tft.setCursor(120,80);
  tft.print("IN ");
  delay(TIME1);
  pneumatics2.moveMotor(255);
  pneumatics1.freeMotor();
  tft.setCursor(120,40);
  tft.print("IN ");
  tft.setCursor(120,80);
  tft.print("OUT");  
  delay(TIME1);
}
