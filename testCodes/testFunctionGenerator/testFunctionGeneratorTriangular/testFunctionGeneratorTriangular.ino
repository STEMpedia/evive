/*
 * Sine Wave generator with Frequency and Amplitude Adjustment
 * Frequency Range: 10Hz ~ 500Hz
 * Amplitude: 0 to 2.5V
 * Hardware used: Arduino MEGA 2560, Potentiometer (X 2), MCP4725 (DAC), TFT (1.8" SPI)
 * Created by: Dhrupal R Shah
 * Contact: contact@evive.cc
 * Dated: 2016/08/01
 */

//Modified Library of Adaruit_MCP4725 to speed up the IIC Communication
#include "dac_MCP4725.h"

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

// These pins will also work for the 1.8" TFT shield
#define TFT_CS     48
#define TFT_RST    47 // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     49

// Define various ADC prescaler (Used to speed up ADC read action)
const unsigned char PS_16 = (1 << ADPS2);
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0);
const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

uint8_t increment = 1, oldIncrement;
float amplitude =  1, oldAmplitude;
int16_t i;
uint16_t lookup = 0;		//varaible for navigating through the tables

Adafruit_ST7735 lcd = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

//Variable of class dac_MCP4725
dac_MCP4725 dac;

void setup() {
  Serial.begin(115200);
  Serial.println("Generating a Triangluar wave");
  
  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61
  // For MCP4725A2 the address is 0x64 or 0x65
  dac.begin(0x60);

  /*Speed up ADC*/
  // set up the ADC
  ADCSRA &= ~PS_128;  // remove bits set by Arduino library
  // you can choose a prescaler from above.
  // PS_16, PS_32, PS_64 or PS_128
  ADCSRA |= PS_32;    // set our own prescaler to 64

  // Use this initializer if you're using a 1.8" TFT
  lcd.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  lcd.setRotation(1);
  lcd.fillScreen(ST7735_BLACK);
  lcd.setCursor(10,50);
  lcd.print("Frequency (Hz):");  
  lcd.setCursor(10,80);
  lcd.print("Amplitude (V):");
  lcd.setTextColor(ST7735_GREEN);
  lcd.setCursor(10,30);
  lcd.print("Triangular Wave");  
  lcd.setTextColor(ST7735_YELLOW, ST7735_BLACK);

  //Set the Frequency and Amplitude
  oldIncrement = increment;
	oldAmplitude = amplitude;
	increment = (analogRead(A9)>>4)+1;
	amplitude = ((analogRead(A10)>>4)/64.0);

	lcd.setCursor(10,60);
	lcd.print(8.5+8.15*(increment-1));
	lcd.print("  ");
	lcd.setCursor(10,90);
	lcd.print(amplitude*2.5);
}

void loop() {
  //Set the Frequency and Amplitude
  oldIncrement = increment;
	oldAmplitude = amplitude;
	increment = (analogRead(A9)>>4)+1;
	amplitude = ((analogRead(A10)>>4)/64.0);
  //Only update on screen, if values are changed
	if(oldIncrement!=increment){
		lcd.setCursor(10,60);
		lcd.print(8.5+8.15*(increment-1));
		lcd.print("  ");
//   Serial.println(increment);    
	}
	if(oldAmplitude!=amplitude){
		lcd.setCursor(10,90);
		lcd.print(amplitude*2.5);
//   Serial.println(amplitude);
	}	
  //loop to run one wave complete wave form
  for (i = 0; i < 512; i= i + increment)
  {
    dac.setVoltage(i*8*amplitude, false);
  }
  for (i = 512; i > 0; i= i - increment)
  {
    dac.setVoltage(i*8*amplitude, false);
  }  
}
