/*
 * Arduino Oscilloscope using a graphic LCD
 * The max sampling rates are 4.3ksps with 2 channels and 8.6ksps with a channel.
 * http://n.mtng.org/ele/arduino/oscillo.html
 * Copyright (c) 2009-2014, Noriaki Mitsunaga 
 * changed sketch by vaupell: http://www.element14.com/community/groups/arduino/blog/2014/12/26/a-simple-diy-oscilloscope-with-arduino-uno-and-mega?CMP=SOM-BLOG-MVAUPELL-ARDUINO-TW
 * rechanged by niq_ro: http://nicuflorica.blogspot.ro/
 * or http://arduinotehniq.blogspot.com/
 * rechanged by evive http://evive.cc (contact@evive.cc)
 * or Dhrupal R Shah, Agilo Technologies on July 1, 2016.
 * Modifications:
 * * Added scroll menu for better visibility and control
 * * Added Digital Joystick (Navigation Key) (alternatively 5 push buttons can be used)
 * * Updated for 1.8" ST7735R TFT screen
 * 
 * Sensing Pins are by default: Channel 0 on Analog 0 and Channel 1 on Analog 1.
 * Tested with Arduino MEGA and 1.8" SPI TFT ST7735R
 */

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include "navKey.h"          // Library for checking user control/setting input 

//colors for TFT
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//TFT pins (other than SPI MOSI, SCLK)
#define TFT_CS  48          // Chip select line for TFT display
#define TFT_DC   49          // Data/command line for TFT
#define TFT_RST  47   

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

#define txtLINE0   0
#define txtLINE1   16
#define txtLINE2   30
#define txtLINE3   46

//TFT specs
const int LCD_WIDTH = 160;
const int LCD_HEIGHT = 128;
const int SAMPLES = 160;
const int DOTS_DIV = 20;
//range0, range1, rate, TRIG_Modes, TRIG_E_DN/UP ch0_off, ch1_off, trig_lv, Send, Save
const int MENU_TOTAL_ITEMS = 10;

#define LEFT_MARGIN			0
#define TOP_MARGIN			9               //Pixels for scroll menu on top
#define RIGHT_MARGIN		0
#define BOTTOM_MARGIN		0
#define LCD_HEIGHT_TOP_MARGIN 119       //Pixels for plotting (LCD Height - Top Margin)

//const int ad_sw = A11;                    // Analog 3 pin for switches

//Set as per user's requirement
const int ad_ch0 = A0;                   // Analog 0 pin for channel 0
const int ad_ch1 = A1;                   // Analog 1 pin for channel 1
const unsigned long VREF[] = {100, 200, 500, 1000, 2000}; // reference voltage 5.0V ->  100 :   1V/div range (100mV/dot)
                                        // It means 5.0 * DOTS_DIV = 100 : 1V/div   (Use 4.9 if reference voltage is 4.9[V])
                                        //                        -> 200 : 0.5V/div
                                        //                        -> 750 : 0.2V/div
                                        //                        ->1500 : 100mV/div
                                        //                       -> 3000 :  50mV/div
const int MILLIVOL_per_dot[] = {50, 25, 10, 5, 2.5}; // mV/dot
const int MODE_ON = 0;
const int MODE_INV = 1;
const int MODE_OFF = 2;
const char *Modes[] = {"NORM", "INV", "OFF"};

const int TRIG_AUTO = 0;
const int TRIG_NORM = 1;
const int TRIG_SCAN = 2;
const int TRIG_ONE  = 3;
const char *TRIG_Modes[] = {"Auto", "Norm", "Scan", "One"};
const int TRIG_E_UP = 0;
const int TRIG_E_DN = 1;

#define RATE_MIN 0
#define RATE_MAX 13
///////////////////////0 (single)/1///////2///////3///////4///////5///////6////////7//////8//////9///////10////11////12////13
//const char *Rates[] = {"F1-1", "F1-2 ", "F2  ", "5ms", "10ms", "20ms", "50ms", "0.1s", "0.2s", "0.5s", "1s", "2s", "5s", "10s"};
const char *Rates[] = {"1-2.5", "2-2.5", "F2  ", "5ms", "10ms", "20ms", "50ms", "0.1s", "0.2s", "0.5s", "1s", "2s", "5s", "10s"};

#define RANGE_MIN 0
#define RANGE_MAX 5
//////////////////////////0///////1//////2//////3////////4//////5
const char *Ranges[] = {" 1V", "0.5V", "0.2V", "0.1V", "50mV", "OFF"};

unsigned long startMillis;
byte data[4][SAMPLES];                   // keep twice of the number of channels to make it a double buffer
byte sample=0;                           // index for double buffer

///////////////////////////////////////////////////////////////////////////////////////////////

// Define colors here
#define	BGCOLOR   0x0000
#define GRIDCOLOR 0xFFFF
#define CH1COLOR  ST7735_GREEN
#define CH2COLOR  0xFFE0

// Declare variables and set defaults here
byte range0 = RANGE_MIN, ch0_mode = MODE_ON;  // CH0
short ch0_off = 0;                            //offset
byte range1 = RANGE_MIN, ch1_mode = MODE_OFF;  // CH1
short ch1_off = 0;                           //offset
byte rate = 8;                               // sampling rate
byte trig_mode = TRIG_AUTO, trig_lv = 50, trig_edge = TRIG_E_UP, trig_ch = 1; // trigger settings

byte Start = 1;  // Start sampling
byte menu = 1;  // Default menu
///////////////////////////////////////////////////////////////////////////////////////////////

void setup(){
  Serial.begin(250000);
  pinMode(TFT_CS, OUTPUT);
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.fillScreen(ST7735_BLACK);
  delay(1);
  tft.setTextColor(RED);
	tft.setTextWrap(0);
  tft.setTextSize(4);
  tft.setCursor(20, 40);
  tft.print("evive");
  delay(100);
  tft.fillScreen(BGCOLOR);
  DrawGrid();
  DrawText();

//To get PWM output on pin5 for testing
//  pinMode(5, OUTPUT);
//  analogWrite(5,0);
}

void CheckSW() {
  //navKey library handles the joystick input.
  //menuMove is an extern bool variable in navekey library for 4 directions
  //Up = 1
  //Right = 2
  //Down = 3
  //Left = 4
  //menuPress is an extern bool variable in navekey library for center press
	navKeyUpdate();
	if (menuMove==0)
		return;
	else if(menuMove == 2){
		if(menu+1>MENU_TOTAL_ITEMS)
			menu = 1;
		else
			menu++;
		DrawText();
	}
	else if(menuMove == 4){
		if(menu<2)
			menu = MENU_TOTAL_ITEMS;
		else
			menu--;
	  DrawText();		
	}
	else if(menuMove == 3 || menuMove == 1){
		menuUpdate();
		DrawText();
	}
}

//Set settings based on the user input
void menuUpdate(){
	switch(menu){
		case 1:
			if(menuMove==3){
			  // CH0 RANGE +
				ch0_mode = MODE_ON;
				if (range0 > 0)
					range0 --;
			}
			else{
			  // CH0 RANGE -
				if (range0 < RANGE_MAX)
					range0 ++;
				if(range0 == RANGE_MAX)
				{	ch0_mode = MODE_OFF;
					tft.fillRect(0, TOP_MARGIN, LCD_WIDTH, LCD_HEIGHT_TOP_MARGIN,BGCOLOR);
					//DrawGrid;
				}
				}
			break;
		case 2:
			if(menuMove==3){
			  // CH1 RANGE +
				ch1_mode = MODE_ON;
				if (range1 > 0)
					range1 --;
			}
			else{
			  // CH1 RANGE -
				if (range1 < RANGE_MAX)
					range1 ++;
				if(range1 == RANGE_MAX)
				{
					ch1_mode = MODE_OFF;
					tft.fillRect(0, TOP_MARGIN, LCD_WIDTH, LCD_HEIGHT_TOP_MARGIN, BGCOLOR);
				}
				}
			break;
		case 3:
			if(menuMove == 3){
			  // RATE SLOW
				if (rate < RATE_MAX)
				rate ++;
			}
			else{
			  // RATE FAST
				if (rate > 0)
				rate --;
			}
			break;
		case 4:
			if(menuMove == 3) 
			 {// TRIG MODE
				if (trig_mode > TRIG_AUTO)
					trig_mode--;
				}
			else{
				if (trig_mode < TRIG_ONE)
					trig_mode++;
			}
			break;
		case 5:
			if (trig_edge == TRIG_E_DN)
				trig_edge = TRIG_E_UP;
			else
				trig_edge = TRIG_E_DN;
			break;
		case 6:
			if(menuMove == 3)
			{
				tft.setCursor(LCD_WIDTH-7,LCD_HEIGHT-ch0_off-3);
				tft.setTextColor(BGCOLOR);
				tft.print(char(174));
				ch0_off--;
				tft.setCursor(LCD_WIDTH-7,LCD_HEIGHT-ch0_off-3);
				tft.setTextColor(CH1COLOR);
				tft.print(char(174));				
			}
			else
			{
				tft.setCursor(LCD_WIDTH-7,LCD_HEIGHT-ch0_off-3);
				tft.setTextColor(BGCOLOR);
				tft.print(char(174));
				ch0_off++;
				tft.setCursor(LCD_WIDTH-7,LCD_HEIGHT-ch0_off-3);
				tft.setTextColor(CH1COLOR);
				tft.print(char(174));

			}
			break;
		case 7:
			if(menuMove == 3)
			{
				tft.setCursor(LCD_WIDTH-7,LCD_HEIGHT-ch1_off-3);
				tft.setTextColor(BGCOLOR);
				tft.print(char(174));
				ch1_off--;
				tft.setCursor(LCD_WIDTH-7,LCD_HEIGHT-ch1_off-3);
				tft.setTextColor(CH2COLOR);
				tft.print(char(174));				
			}
			else
			{
				tft.setCursor(LCD_WIDTH-7,LCD_HEIGHT-ch1_off-3);
				tft.setTextColor(BGCOLOR);
				tft.print(char(174));
				ch1_off++;
				tft.setCursor(LCD_WIDTH-7,LCD_HEIGHT-ch1_off-3);
				tft.setTextColor(CH2COLOR);
				tft.print(char(174));								
			}
			break;
		case 8:
			if(menuMove==3)
				trig_lv--;
			else
				trig_lv++;
			break;
		case 9:
			SendData();
			break;
		case 10:
			//ADD DATA LOGGING FUNCTION WITH SD CARD
			break;
		default :
			break;
	}
}

void SendData() {
  Serial.print(Rates[rate]);
  Serial.println("/div (20 samples)");
  for (int i=0; i<SAMPLES; i ++) {
      Serial.print(data[sample + 0][i]*MILLIVOL_per_dot[range0]);
      Serial.print(" ");
      Serial.println(data[sample + 1][i]*MILLIVOL_per_dot[range1]);
   } 
}

void DrawGrid() {
    for (int x=0; x<=SAMPLES; x += 2) { // Horizontal Line
      for (int y=TOP_MARGIN; y<=LCD_HEIGHT; y += DOTS_DIV) {
        tft.drawPixel(x, y, GRIDCOLOR);
        CheckSW();
      }
      if (LCD_HEIGHT == 128)
        tft.drawPixel(x, LCD_HEIGHT-1, GRIDCOLOR);
    }
    for (int x=0; x<=SAMPLES; x += DOTS_DIV ) { // Vertical Line
      for (int y=TOP_MARGIN; y<=LCD_HEIGHT; y += 2) {
        tft.drawPixel(x, y, GRIDCOLOR);
        CheckSW();
      }
    }
		
	tft.setCursor(LCD_WIDTH-7,LCD_HEIGHT-ch0_off-3);
	tft.setTextColor(CH1COLOR);
	tft.print(char(174));
	tft.setCursor(LCD_WIDTH-7,LCD_HEIGHT-ch1_off-3);
	tft.setTextColor(CH2COLOR);
	tft.print(char(174));
}

void DrawText() {
	int itr;
	tft.fillRect(0,0,160, 9, WHITE);
  tft.setTextSize(1);
	tft.fillRect(0,0,40,9,RED);
	tft.setTextColor(WHITE);
		
	for (itr = 0; itr<4; itr++)
	{	tft.setCursor((itr)*41, 1);
		if(itr+menu>MENU_TOTAL_ITEMS)
			PrintMenuItem(itr+menu-MENU_TOTAL_ITEMS);
		else
			PrintMenuItem(itr+menu);
			tft.setTextColor(RED);
	}
	
//  tft.setCursor(SAMPLES, 70);
//  tft.println(trig_ch == 0 ? "T:1" : "T:2"); 
#if 0
    GLCD.FillRect(101,txtLINE0,28,64, WHITE);  // clear text area that will be drawn below 
    
    switch (menu) {
      case 0:
        GLCD.GotoXY(SAMPLES + 1,txtLINE0);         // locate curser for printing text
        GLCD.Puts(Ranges[range0]); 
        GLCD.GotoXY(SAMPLES + 1,txtLINE1);         // locate curser for printing text
        GLCD.Puts(Ranges[range1]); 
        GLCD.GotoXY(SAMPLES + 1,txtLINE2);         // locate curser for printing text
        GLCD.Puts(Rates[rate]); 
        GLCD.GotoXY(SAMPLES + 1,txtLINE3);         // locate curser for printing text
        GLCD.Puts(TRIG_Modes[trig_mode]); 
        break;
      case 1:
        GLCD.GotoXY(SAMPLES + 1,txtLINE0);         // locate curser for printing text
        GLCD.Puts("OF1"); 
        GLCD.GotoXY(SAMPLES + 1,txtLINE1);         // locate curser for printing text
        GLCD.Puts("OF2");
        GLCD.GotoXY(SAMPLES + 1,txtLINE2);         // locate curser for printing text
        GLCD.Puts("Tlv"); 
        GLCD.GotoXY(SAMPLES + 1,txtLINE3);         // locate curser for printing text
        GLCD.Puts(trig_edge == TRIG_E_UP ? "UP" : "DN"); 
        break;
      case 2:
        GLCD.GotoXY(SAMPLES + 1,txtLINE0);         // locate curser for printing text
        GLCD.Puts(Modes[ch0_mode]); 
        GLCD.GotoXY(SAMPLES + 1,txtLINE1);         // locate curser for printing text
        GLCD.Puts(Modes[ch1_mode]);
        GLCD.GotoXY(SAMPLES + 1,txtLINE2);         // locate curser for printing text
        GLCD.Puts(trig_ch == 0 ? "T:1" : "T:2"); 
        break;
    }
#endif
}

void PrintMenuItem(int item){
	switch(item)
	{ case 1:
			tft.print(Ranges[range0]);
			if (range0 = 5) tft.println("/D");
			break;
		case 2:
			tft.print(Ranges[range1]);
			if (range1 = 5) tft.println("/D");
			break;
		case 3:
			tft.print(Rates[rate]);
			tft.println("/D");
			break;
		case 4:
			tft.println(TRIG_Modes[trig_mode]);
			break;
		case 5:
			tft.println(trig_edge == TRIG_E_UP ? "UP" : "DN"); 
			break;
		case 6:
			tft.print("01:");
			tft.println((ch0_off*MILLIVOL_per_dot[range0]>1000)?ch0_off*MILLIVOL_per_dot[range0]/1000.0:ch0_off*MILLIVOL_per_dot[range0]);
			break;
		case 7:
			tft.print("02:");
			tft.println((ch1_off*MILLIVOL_per_dot[range1]>1000)?ch1_off*MILLIVOL_per_dot[range1]/1000.0:ch1_off*MILLIVOL_per_dot[range1]);
			break;
		case 8:
			tft.print("TLV:");
			tft.println(trig_lv);
			break;
		case 9:
			tft.println("Send");
			break;
		case 10:
			tft.println("Save");
			break;
		default:
			break;
	}
}

//To draw grid at given x. Will be used while ploting
void DrawGrid(int x) {
    if ((x % 2) == 0)
      for (int y=TOP_MARGIN; y<=LCD_HEIGHT; y += DOTS_DIV)
        tft.drawPixel(x, y, GRIDCOLOR);
    if ((x % DOTS_DIV) == 0)
      for (int y=TOP_MARGIN; y<=LCD_HEIGHT; y += 2)
        tft.drawPixel(x, y, GRIDCOLOR);
}

void ClearAndDrawGraph() {
  int clear = 0;
  if (sample == 0)
    clear = 2;
#if 0
   for (int x=0; x<SAMPLES; x++) {
     GLCD.SetDot(x, LCD_HEIGHT-data[clear+0][x], WHITE);
     GLCD.SetDot(x, LCD_HEIGHT-data[clear+1][x], WHITE);
     GLCD.SetDot(x, LCD_HEIGHT-data[sample+0][x], BLACK);
     GLCD.SetDot(x, LCD_HEIGHT-data[sample+1][x], BLACK);
  }
#else
   for (int x=0; x<(SAMPLES-1); x++) {
     if (ch0_mode != MODE_OFF){
			 //remove previous data
       tft.drawLine(x, LCD_HEIGHT-data[clear+0][x], x+1, LCD_HEIGHT-data[clear+0][x+1], BGCOLOR);
			 //display new data
			 tft.drawLine(x, LCD_HEIGHT-data[sample+0][x], x+1, LCD_HEIGHT-data[sample+0][x+1], CH1COLOR);
			 }
     if (ch1_mode != MODE_OFF){
       //remove previous data
			 tft.drawLine(x, LCD_HEIGHT-data[clear+1][x], x+1, LCD_HEIGHT-data[clear+1][x+1], BGCOLOR);			 
			 //display new data
			 tft.drawLine(x, LCD_HEIGHT-data[sample+1][x], x+1, LCD_HEIGHT-data[sample+1][x+1], CH2COLOR);
			 }
     CheckSW();
  }  
#endif
}

void ClearAndDrawDot(int i) {
  int clear = 0;
  if (i <= 1)
    return;
  if (sample == 0)
    clear = 2;
#if 0
   for (int x=0; x<SAMPLES; x++) {
     GLCD.SetDot(x, LCD_HEIGHT-data[clear+0][x], WHITE);
     GLCD.SetDot(x, LCD_HEIGHT-data[clear+1][x], WHITE);
     GLCD.SetDot(x, LCD_HEIGHT-data[sample+0][x], BLACK);
     GLCD.SetDot(x, LCD_HEIGHT-data[sample+1][x], BLACK);
  }
#else
  if (ch0_mode != MODE_OFF){
    tft.drawLine(i-1, LCD_HEIGHT-data[clear+0][i-1], i, LCD_HEIGHT-data[clear+0][i], BGCOLOR);
		tft.drawLine(i-1, LCD_HEIGHT-data[sample+0][i-1], i, LCD_HEIGHT-data[sample+0][i], CH1COLOR);
	}
  if (ch1_mode != MODE_OFF){
		tft.drawLine(i-1, LCD_HEIGHT-data[clear+1][i-1], i, LCD_HEIGHT-data[clear+1][i], BGCOLOR);
    tft.drawLine(i-1, LCD_HEIGHT-data[sample+1][i-1], i, LCD_HEIGHT-data[sample+1][i], CH2COLOR);
	}
#endif
  DrawGrid(i);
}

void DrawGraph() {
   for (int x=0; x<SAMPLES; x++) {
     tft.drawPixel(x, LCD_HEIGHT-data[sample+0][x], CH1COLOR);
     tft.drawPixel(x, LCD_HEIGHT-data[sample+1][x], CH2COLOR);
  }
}

void ClearGraph() {
  int clear = 0;
  
  if (sample == 0)
    clear = 2;
  for (int x=0; x<SAMPLES; x++) {
     tft.drawPixel(x, LCD_HEIGHT-data[clear+0][x], BGCOLOR);
     tft.drawPixel(x, LCD_HEIGHT-data[clear+1][x], BGCOLOR);
  }
}

inline unsigned long adRead(byte ch, byte mode, int off)
{
//		unsigned long st = micros();
  unsigned long a = analogRead(ch);				//takes 116us normally, change ADC clock presacllar to get faster
//		Serial.println(micros()-st);
	//nearest integer
	a = ((a*VREF[ch == ad_ch0 ? range0 : range1]+512) >> 10) + off;
  a = a>=(LCD_HEIGHT_TOP_MARGIN+1) ? LCD_HEIGHT_TOP_MARGIN: a;

  if (mode == MODE_INV)
    return LCD_HEIGHT_TOP_MARGIN - a;
  return a;
}

void  loop() {
  //Set PWM output on pin5 based on potentiometer on Pin A9 (for testing)
  //analogWrite(5,analogRead(A9)/4);
  if (trig_mode != TRIG_SCAN) {
      unsigned long st = millis();
      byte oad;
      if (trig_ch == 0)
        oad = adRead(ad_ch0, ch0_mode, ch0_off);
      else
        oad = adRead(ad_ch1, ch1_mode, ch1_off);
      //Wait till trigger detected
			for (;;) {
        byte ad;
        if (trig_ch == 0)
          ad = adRead(ad_ch0, ch0_mode, ch0_off);
        else
          ad = adRead(ad_ch1, ch1_mode, ch1_off);

        //Detect trigger
				if (trig_edge == TRIG_E_UP) {
           if (ad >= trig_lv && ad > oad)
            break; 
        } else {
           if (ad <= trig_lv && ad < oad)
            break; 
        }
        oad = ad;

        CheckSW();
        if (trig_mode == TRIG_SCAN)
          break;
        if (trig_mode == TRIG_AUTO && (millis() - st) > 100)
          break; 
      }
  }
  
  // sample and draw depending on the sampling rate
    if (rate <= 5 && Start) {
    // change the index for the double buffer
    if (sample == 0)
      sample = 2;
    else
      sample = 0;

    if (rate == 0) { // full speed, channel 0 only
      unsigned long st = millis();
      for (int i=0; i<SAMPLES; i ++) {
        data[sample+0][i] = adRead(ad_ch0, ch0_mode, ch0_off);
      }
      for (int i=0; i<SAMPLES; i ++)
        data[sample+1][i] = 0;
       Serial.println(millis()-st);
    } else if (rate == 1) { // full speed, channel 1 only
      unsigned long st = millis();
      for (int i=0; i<SAMPLES; i ++) {
        data[sample+1][i] = adRead(ad_ch1, ch1_mode, ch1_off);
      }
      for (int i=0; i<SAMPLES; i ++)
        data[sample+0][i] = 0;
      // Serial.println(millis()-st);
    } else if (rate == 2) { // full speed, dual channel
      unsigned long st = millis();
      for (int i=0; i<SAMPLES; i ++) {
        data[sample+0][i] = adRead(ad_ch0, ch0_mode, ch0_off);
        data[sample+1][i] = adRead(ad_ch1, ch1_mode, ch1_off);
      }
      // Serial.println(millis()-st);
    } else if (rate >= 3 && rate <= 5) { // .5ms, 1ms or 2ms sampling
      const unsigned long r_[] = {5000/DOTS_DIV, 10000/DOTS_DIV, 20000/DOTS_DIV};
      unsigned long st0 = millis();
      unsigned long st = micros();
      unsigned long r = r_[rate - 3];
			//DO NOT ADD ANY STATEMENT INSIDE FOR LOOP
      for (int i=0; i<SAMPLES; i ++) {
        while((st - micros())<r) ;
        st += r;
        data[sample+0][i] = adRead(ad_ch0, ch0_mode, ch0_off);
        data[sample+1][i] = adRead(ad_ch1, ch1_mode, ch1_off);
      }
      // Serial.println(millis()-st0);
    }
    ClearAndDrawGraph();
    CheckSW();
    DrawGrid();
    //DrawText();
  } else if (Start) { // 5ms - 500ms sampling
  // copy currently showing data to another
    if (sample == 0) {
      for (int i=0; i<SAMPLES; i ++) {
        data[2][i] = data[0][i];
        data[3][i] = data[1][i];
      }
    } else {
      for (int i=0; i<SAMPLES; i ++) {
        data[0][i] = data[2][i];
        data[1][i] = data[3][i];
      }      
    }

    const unsigned long r_[] = {50000/DOTS_DIV, 100000/DOTS_DIV, 200000/DOTS_DIV,
                      500000/DOTS_DIV, 1000000/DOTS_DIV, 2000000/DOTS_DIV, 
                      5000000/DOTS_DIV, 10000000/DOTS_DIV};
    unsigned long st0 = millis();
    unsigned long st = micros();
    for (int i=0; i<SAMPLES; i ++) {
      while((st - micros())<r_[rate-6]) {
        CheckSW();
        if (rate<6)
          break;
      }
      if (rate<6) { // sampling rate has been changed
        tft.fillScreen(BGCOLOR);
        break;
      }
      st += r_[rate-6];
      if (st - micros()>r_[rate-6])
          st = micros(); // sampling rate has been changed to shorter interval
      if (!Start) {
         i --;
         continue;
      }
      data[sample+0][i] = adRead(ad_ch0, ch0_mode, ch0_off);
      data[sample+1][i] = adRead(ad_ch1, ch1_mode, ch1_off);
      ClearAndDrawDot(i);     
    }
    // Serial.println(millis()-st0);
    DrawGrid();
    //DrawText();
  } else {
    CheckSW();
  }
  if (trig_mode == TRIG_ONE)
    Start = 0;
	else
		Start = 1;
}
