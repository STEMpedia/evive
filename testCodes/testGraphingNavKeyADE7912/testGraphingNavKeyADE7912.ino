/*
 * Arduino Oscilloscope using a graphic LCD
 * The max sampling rates are 4.3ksps with 2 channels and 8.6ksps with a channel.
 * http://n.mtng.org/ele/arduino/oscillo.html
 * Copyright (c) 2009-2014, Noriaki Mitsunaga
 changed sketch by vaupell: http://www.element14.com/community/groups/arduino/blog/2014/12/26/a-simple-diy-oscilloscope-with-arduino-uno-and-mega?CMP=SOM-BLOG-MVAUPELL-ARDUINO-TW
 rechanged by niq_ro: http://nicuflorica.blogspot.ro/
 or http://arduinotehniq.blogspot.com/
 rechanged by evive http://evive.cc
 or Dhrupal R Shah, Agilo Technologies
 */

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include "navKey.h"

//colors for TFT
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//TFT pins
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
//range0, range1, rate, TRIG_Modes, TRIG_E_DN/UP ch0_off, ch1_off, trig_lv, Send, log
const int MENU_TOTAL_ITEMS = 10;

#define LEFT_MARGIN			0
#define TOP_MARGIN			9
#define RIGHT_MARGIN		0
#define BOTTOM_MARGIN		0
#define LCD_HEIGHT_TOP_MARGIN 119
#define LCD_GRAPH_MID		69
#define LCD_GRPAH_MID_TOP_MARGIN 60

//const int ad_sw = A11;                    // Analog 3 pin for switches
const int ad_ch0 = A5;                   // Analog 4 pin for channel 0
const int ad_ch1 = A10;                   // Analog 5 pin for channel 1
const unsigned long VREF[] = {10, 20, 50, 100, 200, 500, 1000, 2000, 5000}; // reference voltage 5.0V ->  100 :   1V/div range (100mV/dot)
                                        // It means 5.0 * DOTS_DIV = 100 : 1V/div   (Use 4.9 if reference voltage is 4.9[V])
                                        //                        -> 200 : 0.5V/div
                                        //                        -> 750 : 0.2V/div
                                        //                        ->1500 : 100mV/div
                                        //                       -> 3000 :  50mV/div
const int MILLIVOL_per_dot[] = {500, 250, 100, 50, 25, 10, 5, 2.5, 1, 0, 1, 2.5, 5, 10, 25, 50}; // mV/dot
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
#define RANGE_MAX_CH0 9
#define RANGE_MAX_CH1 15
const char *Ranges[] = {" 10V/D", "  5V/D", "  2V/D", "  1V/D", "0.5V/D", "0.2V/D", "0.1V/D", "50mV/D", "20mV/D", " OFF",
	"20mA/D", "50mA/D", "0.1A/D", "0.2A/D", "0.5A/D", "1A/D"};

unsigned long startMillis;
int data[4][SAMPLES];                   // keep twice of the number of channels to make it a double buffer
byte sample=0;                           // index for double buffer

///////////////////////////////////////////////////////////////////////////////////////////////

// Define colors here
#define	BGCOLOR   0x0000
#define GRIDCOLOR 0xFFFF
#define CH1COLOR  ST7735_GREEN
#define CH2COLOR  0xFFE0

// Declare variables and set defaults here
byte range0 = RANGE_MIN+2, ch0_mode = MODE_ON;  // CH0
short ch0_off = 0; //614+15;                 //offset
byte range1 = RANGE_MIN+2, ch1_mode = MODE_ON;  // CH1
short ch1_off = 0; //614+15;                 //offset
byte rate = 5;                                // sampling rate
byte trig_mode = TRIG_AUTO, trig_lv = 50, trig_edge = TRIG_E_UP, trig_ch = 1; // trigger settings

byte Start = 1;  // Start sampling
byte menu = 1;  // Default menu
///////////////////////////////////////////////////////////////////////////////////////////////

/*---------ADE//start----------*/
#define __DEBUG__    /* comment this line to disable debugging messages over serial console*/

// inslude the SPI library:
#include <SPI.h>

int SPI_ADC_SS = 35;    // SPI ADC SS
int ADC_RDY = 32;      // ADC Ready pin
#define ADC_SPIMaxSpeed 5600000
#define ADC_SPIMode SPI_MODE3
#define ADC_SPIDataOrder MSBFIRST

// Command Definitions
#define ADE791X_READ    0x04
#define ADE791X_WRITE   0x00

// Register Definitions
#define ADE791X_REG_IWV            0x00    /* Instantaneous value of Current I. */
#define ADE791X_REG_V1WV           0x01    /* Instantaneous value of Voltage V1 */
#define ADE791X_REG_V2WV           0x02    /* Instantaneous value of Voltage V2 */
#define ADE791X_MUL_V1WV           0.006485
#define ADE791X_OFFSET_V1WV        362760   
#define ADE791X_MUL_VIMWV          0.0011901
#define ADE791X_OFFSET_VIMWV			 349319
#define ADE791X_MUL_IWV            0.0005921
#define ADE791X_OFFSET_IWV				 349319

#define ADE791X_REG_ADC_CRC        0x04    /* CRC value of IWV, V1WV, and V2WV registers. See the ADC Output Values CRC section for details */
#define ADE791X_REG_CTRL_CRC       0x05    /* CRC value of configuration registers. See the CRC of Configuration Registers  for details. */

#define ADE791X_REG_CNT_SNAPSHOT   0x07    /* Snapshot value of the counter used in synchronization operation. */
#define ADE791X_REG_CONFIG         0x08    /* Configuration register. See Table 15 for details */
#define ADE791X_REG_STATUS0        0x09    /* Status register */
#define ADE791X_REG_LOCK           0x0A    /* Memory protection register */
#define ADE791X_REG_SYNC_SNAP      0x0B    /* Synchronization register */
#define ADE791X_REG_COUNTER0       0x0C    /* Contains the least significant eight bits of the internal synchronization counter */
#define ADE791X_REG_COUNTER1       0x0D    /* COUNTER1[3:0] bits contain the most significant four bits of the internal synchronization counter */
#define ADE791X_REG_EMI_CTRL       0x0E    /* EMI control register. */
#define ADE791X_REG_STATUS1        0x0F    /* Status register */

#define ADE791X_REG_TEMPOS         0x18    /* Temperature sensor offset */

/* configuration register constants */
#define CLKOUT_EN                  0x01
#define PWRDWN_EN                  0x04    /* Shuts down the dc-to-dc converter. When PWRDWN_EN = 0, the default value, the */
#define TEMP_EN                    0x08    /* This bit selects the second voltage channel measurement. */
#define ADC_FREQ_8KHZ              0x00    /* These bits select the ADC output frequency to 8khz. */
#define ADC_FREQ_4KHZ              0x10    /* These bits select the ADC output frequency.4khz */
#define ADC_FREQ_2KHZ              0x20    /* These bits select the ADC output frequency.2khz */
#define ADC_FREQ_1KHZ              0x30    /* These bits select the ADC output frequency.1khz */
#define SWRST                      0x40    /* When this bit is set to 1, a software reset is initiated. This bit clears itself to 0 after */
#define BW                         0x80    /* Selects the bandwidth of the digital low-pass filter of the ADC. When BW = 0, the */

/*Status0 registers (address 0x9*/
#define RESET_ON                  0x00
#define CRC_STAT                  0x01
#define IC_PROT                   0x02

/* lock register constants(address 0xA */
#define LOCKED                    0xCA    /*locks configuration register writing */
#define UNLOCKED                  0x9C    /*unlocks configuration register writing */

SPISettings ADCSetting(ADC_SPIMaxSpeed,ADC_SPIDataOrder,ADC_SPIMode);
/*---------ADE//end----------*/

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
  ade791x_init();
  delay(100);
  tft.fillScreen(BGCOLOR);
	tft.setTextSize(1);
  DrawGrid();
  DrawText();

  pinMode(5, OUTPUT);
  analogWrite(5,0);
}

void CheckSW() {
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
				if (range0 < RANGE_MAX_CH0)
					range0 ++;
				if(range0 == RANGE_MAX_CH0)
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
				if (range1 < RANGE_MAX_CH1)
					range1 ++;
				if(range1 == RANGE_MAX_CH1)
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
				tft.setCursor(LCD_WIDTH-7,LCD_GRAPH_MID-ch0_off-3);
				tft.setTextColor(BGCOLOR);
				tft.print(char(174));
				ch0_off--;
				tft.setCursor(LCD_WIDTH-7,LCD_GRAPH_MID-ch0_off-3);
				tft.setTextColor(CH1COLOR);
				tft.print(char(174));				
			}
			else
			{
				tft.setCursor(LCD_WIDTH-7,LCD_GRAPH_MID-ch0_off-3);
				tft.setTextColor(BGCOLOR);
				tft.print(char(174));
				ch0_off++;
				tft.setCursor(LCD_WIDTH-7,LCD_GRAPH_MID-ch0_off-3);
				tft.setTextColor(CH1COLOR);
				tft.print(char(174));

			}
			break;
		case 7:
			if(menuMove == 3)
			{
				tft.setCursor(LCD_WIDTH-7,LCD_GRAPH_MID-ch1_off-3);
				tft.setTextColor(BGCOLOR);
				tft.print(char(174));
				ch1_off--;
				tft.setCursor(LCD_WIDTH-7,LCD_GRAPH_MID-ch1_off-3);
				tft.setTextColor(CH2COLOR);
				tft.print(char(174));				
			}
			else
			{
				tft.setCursor(LCD_WIDTH-7,LCD_GRAPH_MID-ch1_off-3);
				tft.setTextColor(BGCOLOR);
				tft.print(char(174));
				ch1_off++;
				tft.setCursor(LCD_WIDTH-7,LCD_GRAPH_MID-ch1_off-3);
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
		
	tft.setCursor(LCD_WIDTH-7,LCD_GRAPH_MID-ch0_off-3);
	tft.setTextColor(CH1COLOR);
	tft.print(char(174));
	tft.setCursor(LCD_WIDTH-7,LCD_GRAPH_MID-ch1_off-3);
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
}

void PrintMenuItem(int item){
	switch(item)
	{ case 1:
			tft.print(Ranges[range0]);
//			tft.println("/D");
			break;
		case 2:
			tft.print(Ranges[range1]);
//			tft.println("/D");
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
      unsigned long st = micros();
   for (int x=0; x<(SAMPLES-1); x++) {
     if (ch0_mode != MODE_OFF){
    	 //remove previous data
		 if(data[clear][x+1]<=(LCD_GRPAH_MID_TOP_MARGIN-ch0_off+1))
			 tft.drawLine(x, LCD_GRAPH_MID-data[clear][x], x+1, LCD_GRAPH_MID-data[clear][x+1], BGCOLOR);
			 //display new data
		 if(data[sample][x+1]<=(LCD_GRPAH_MID_TOP_MARGIN-ch0_off+1))
			 tft.drawLine(x, LCD_GRAPH_MID-data[sample][x], x+1, LCD_GRAPH_MID-data[sample][x+1], CH1COLOR);
	 }
     if (ch1_mode != MODE_OFF){
       //remove previous data
	 	 if(data[clear+1][x+1]<=(LCD_GRPAH_MID_TOP_MARGIN-ch1_off+1))
	 		 tft.drawLine(x, LCD_GRAPH_MID-data[clear+1][x], x+1, LCD_GRAPH_MID-data[clear+1][x+1], BGCOLOR);
		 //display new data
		 if(data[sample+1][x+1]<=(LCD_GRPAH_MID_TOP_MARGIN-ch1_off+1))
			 tft.drawLine(x, LCD_GRAPH_MID-data[sample+1][x], x+1, LCD_GRAPH_MID-data[sample+1][x+1], CH2COLOR);
	 }
     CheckSW();
  }
Serial.println(micros()-st);  

}

void ClearAndDrawDot(int i) {
  int clear = 0;
  if (i <= 1)
    return;
  if (sample == 0)
    clear = 2;

  if (ch0_mode != MODE_OFF){
	  if(data[clear][i]<=(LCD_GRPAH_MID_TOP_MARGIN-ch0_off+1))
		  tft.drawLine(i-1, LCD_GRAPH_MID-data[clear][i-1], i, LCD_GRAPH_MID-data[clear][i], BGCOLOR);
	  if(data[sample+0][i]<=(LCD_GRPAH_MID_TOP_MARGIN-ch0_off+1))
			tft.drawLine(i-1, LCD_GRAPH_MID-data[sample][i-1], i, LCD_GRAPH_MID-data[sample][i], CH1COLOR);
	}
  if (ch1_mode != MODE_OFF){
	  if(data[clear+1][i]<=(LCD_GRPAH_MID_TOP_MARGIN-ch1_off+1))
			tft.drawLine(i-1, LCD_GRAPH_MID-data[clear+1][i-1], i, LCD_GRAPH_MID-data[clear+1][i], BGCOLOR);
	  if(data[sample+1][i]<=(LCD_GRPAH_MID_TOP_MARGIN-ch1_off+1))
			tft.drawLine(i-1, LCD_GRAPH_MID-data[sample+1][i-1], i, LCD_GRAPH_MID-data[sample+1][i], CH2COLOR);
	}

  DrawGrid(i);
}

void DrawGraph() {
   for (int x=0; x<SAMPLES; x++) {
		if(data[sample+0][x]<=(LCD_GRPAH_MID_TOP_MARGIN-ch0_off+1))
			tft.drawPixel(x, LCD_GRAPH_MID-data[sample+0][x], CH1COLOR);
		if(data[sample+1][x]<=(LCD_GRPAH_MID_TOP_MARGIN-ch1_off+1))
			tft.drawPixel(x, LCD_GRAPH_MID-data[sample+1][x], CH2COLOR);
  }
}

void ClearGraph() {
  int clear = 0;
  
  if (sample == 0)
    clear = 2;
  for (int x=0; x<SAMPLES; x++) {
     tft.drawPixel(x, LCD_GRAPH_MID-data[clear+0][x], BGCOLOR);
     tft.drawPixel(x, LCD_GRAPH_MID-data[clear+1][x], BGCOLOR);
  }
}

inline unsigned long adRead(byte ch, byte mode, int off)
{
//		unsigned long st = micros();
unsigned  long a = analogRead(ch);				//takes 116us normally, change ADC clock presacllar to get faster
//		Serial.println(micros()-st);
	//nearest integer
//  a = ((a+off)*VREF[ch == ad_ch0 ? range0 : range1]+512) >> 10;
	a = ((a*VREF[ch == ad_ch0 ? range0 : range1]+512) >> 10) + off;
  a = a>=(LCD_HEIGHT_TOP_MARGIN+1) ? LCD_HEIGHT_TOP_MARGIN: a;

  if (mode == MODE_INV)
    return LCD_HEIGHT_TOP_MARGIN - a;
  return a;
}

/* inline unsigned long adRead(byte ch, byte mode, int off)
{
//		unsigned long st = micros();
  unsigned long a = analogRead(ch);				//takes 116us normally, change ADC clock presacllar to get faster
//		Serial.println(micros()-st);
	//nearest integer
//  a = ((a+off)*VREF[ch == ad_ch0 ? range0 : range1]+512) >> 10;
	a = ((a*VREF[ch == ad_ch0 ? range0 : range1]+512) >> 10) + off;
  a = a>=(LCD_HEIGHT_TOP_MARGIN+1) ? LCD_HEIGHT_TOP_MARGIN: a;

  if (mode == MODE_INV)
    return LCD_HEIGHT_TOP_MARGIN - a;
  return a;
} */

/*---------ADE functions//start-------*/

void ade791x_init(void)
{
  pinMode(SPI_ADC_SS, OUTPUT);
  pinMode(ADC_RDY, INPUT);
  // take the SS pin high to de-select the chip:
//  digitalWrite(SPI_ADC_SS, HIGH);
  // initialize SPI:
//  SPI.begin();
  //delay(1);
//  delayMicroseconds(16);
  //SPI.setClockDivider(SPI_ADC_SS, 64);  // default is 4MHz clock
//  SPI.setBitOrder(MSBFIRST);        // default is MSBFIRST
//  SPI.setDataMode(SPI_MODE3);       // ADE791x chip uses SPI_MODE3

//DS: MAKE  THIS WORKING
  //  ade791x_write(ADE791X_REG_LOCK,UNLOCKED); 
//  ade791x_write(ADE791X_REG_CONFIG, ADC_FREQ_4KHZ | TEMP_EN);  // configures adc sampling frequency and enables temperature on V2WV register
}

long ade791x_read_v1(void)
{
	//unsigned long st = micros();
  unsigned char addr = ADE791X_REG_V1WV;
  long value = 0;  // stores value to return
  long tempValue1 = 0, tempValue2 = 0 , tempValue3 = 0;  
  unsigned char opcode; // stores opcode
  
  addr = addr << 3;  // left shift address by 3 bits
  opcode = (addr | ADE791X_READ);     // forms opcode byte
  // Serial.print ("opcode: ");    // for debug only
  // Serial.println(opcode, BIN);  // for debug only

  SPI.beginTransaction(ADCSetting);
  // take the SS pin low to select the chip:
//  digitalWrite(SPI_ADC_SS, LOW);  // bring SS2 pin low
	PORTC &= ~_BV(PC2);
  SPI.transfer(opcode);        // send out opcode
//  value  = SPI.transfer(0xFF) * 0x10000;  // read MS Byte
////  tempValue1=value;  
//  value |= SPI.transfer(0xFF) * 0x100;  // read mid Byte
////  tempValue2=value;  
//  value |= SPI.transfer(0xFF);  // LS Byte

  tempValue1 = SPI.transfer(0xFF);  // read MS Byte
//  tempValue1=value;  
  tempValue2 = SPI.transfer(0xFF);  // read mid Byte
//  tempValue2=value;  
  tempValue3 = SPI.transfer(0xFF);  // LS Byte

  // take the SS pin high to de-select the chip:
  //digitalWrite(SPI_ADC_SS, HIGH);  
	PORTC |= _BV(PC2);
	
  SPI.endTransaction();  

  tempValue1  = tempValue1 * 0x10000;
  tempValue2 = tempValue1 | tempValue2 * 0x100;
  value = tempValue2 | tempValue3;
    
  value = value <<8;        // sign extends value to 32 bit
  value = value / 0x100;    // converts back value to 24 bit but now sign extended

  value = (value - ADE791X_OFFSET_V1WV)*ADE791X_MUL_V1WV; //ADE791X_MUL_V1WV;
  #ifdef __DEBUG__

	
 // Serial.print ("V1: ");
 // Serial.println (value);
//    Serial.print ("V1: ");
//  Serial.println (value,BIN);
  #endif  

	value = value/(MILLIVOL_per_dot[range0]) + ch0_off;
	// Serial.println(value);
  value = value>=(LCD_HEIGHT_TOP_MARGIN-ch0_off+1) ? LCD_HEIGHT_TOP_MARGIN-ch0_off: value;

  // if (mode == MODE_INV)
    // return LCD_HEIGHT_TOP_MARGIN - value;
	//Serial.println(micros()-st);
  return value;  
}

long ade791x_read_vim(void)
{
  unsigned char addr = ADE791X_REG_IWV;
  long value = 0;  // stores value to return
  long tempValue1 = 0, tempValue2 = 0 , tempValue3 = 0;  
  unsigned char opcode; // stores opcode
  
  addr = addr << 3;  // left shift address by 3 bits
  opcode = (addr | ADE791X_READ);     // forms opcode byte
//  Serial.print ("opcode: ");    // for debug only
//  Serial.println(opcode, BIN);  // for debug only

  SPI.beginTransaction(ADCSetting);
  // take the SS pin low to select the chip:
  // digitalWrite(SPI_ADC_SS, LOW);  // bring SS2 pin low
		PORTC &= ~_BV(PC2);
  SPI.transfer(opcode);        // send out opcode
//  value  = SPI.transfer(0xFF) * 0x10000;  // read MS Byte
////  tempValue1=value;  
//  value |= SPI.transfer(0xFF) * 0x100;  // read mid Byte
////  tempValue2=value;  
//  value |= SPI.transfer(0xFF);  // LS Byte

  tempValue1 = SPI.transfer(0xFF);  // read MS Byte
//  tempValue1=value;  
  tempValue2 = SPI.transfer(0xFF);  // read mid Byte
//  tempValue2=value;  
  tempValue3 = SPI.transfer(0xFF);  // LS Byte

  // take the SS pin high to de-select the chip:
  // digitalWrite(SPI_ADC_SS, HIGH);  
	PORTC |= _BV(PC2);	
  SPI.endTransaction();  

  tempValue1  = tempValue1 * 0x10000;
  tempValue2 = tempValue1 | tempValue2 * 0x100;
  value = tempValue2 | tempValue3;
//  tempValue3=value;
	// Serial.print("RAW: ");
	// Serial.println (value);
	value = value <<8;        // sign extends value to 32 bit
  value = value / 0x100;    // converts back value to 24 bit but now sign extended
	if ( RANGE_MAX_CH1<9){
		value = (value - ADE791X_OFFSET_VIMWV)*ADE791X_MUL_VIMWV; //ADE791X_MUL_V1WV;
		// Serial.print ("VIM: ");
		// Serial.println (value);
		value = value/(MILLIVOL_per_dot[range1]) + ch1_off;
		// Serial.println(value);
		value = value>=(LCD_HEIGHT_TOP_MARGIN-ch1_off+1) ? LCD_HEIGHT_TOP_MARGIN-ch1_off: value;
	}
	else{
		value = (value - ADE791X_OFFSET_IWV)*ADE791X_MUL_IWV; //ADE791X_MUL_IWV;
		// Serial.print ("IM: ");
		// Serial.println (value);
		value = value/(MILLIVOL_per_dot[range1]) + ch1_off;
		// Serial.println(value);
		value = value>=(LCD_HEIGHT_TOP_MARGIN-ch1_off+1) ? LCD_HEIGHT_TOP_MARGIN-ch1_off: value;
	}
	
  // if (mode == MODE_INV)
    // return LCD_HEIGHT_TOP_MARGIN - value;
	//Serial.println(micros()-st);
  return value; 
}

/*--------ADE functions//end------------*/

void  loop() {
	//int value =  ade791x_read_v1 ();
	// value =  ade791x_read_vim ();
	// ade791x_read_i();
	analogWrite(5,analogRead(A9)/4);
  if (trig_mode != TRIG_SCAN) {
      unsigned long st = millis();
      int oad;
      if (trig_ch == 0)
        oad = ade791x_read_v1();
      else
        oad = ade791x_read_vim();
      //Wait till trigger detected
			for (;;) {
        int ad;
        if (trig_ch == 0)
          ad = ade791x_read_v1();
        else
          ad = ade791x_read_vim();

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
        data[sample+0][i] = ade791x_read_v1();
      }
      for (int i=0; i<SAMPLES; i ++)
        data[sample+1][i] = 0;
//       Serial.println(millis()-st);
    } else if (rate == 1) { // full speed, channel 1 only
      unsigned long st = millis();
      for (int i=0; i<SAMPLES; i ++) {
        data[sample+1][i] = ade791x_read_vim();
      }
      for (int i=0; i<SAMPLES; i ++)
        data[sample+0][i] = 0;
      Serial.println(millis()-st);
    } else if (rate == 2) { // full speed, dual channel
      unsigned long st = millis();
      for (int i=0; i<SAMPLES; i ++) {
        data[sample+0][i] = ade791x_read_v1();
        data[sample+1][i] = ade791x_read_vim();
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
        data[sample+0][i] = ade791x_read_v1();
        data[sample+1][i] = ade791x_read_vim();
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
      data[sample+0][i] = ade791x_read_v1();
      data[sample+1][i] = ade791x_read_vim();
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
