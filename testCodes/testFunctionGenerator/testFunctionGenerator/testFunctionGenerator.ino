#include "dac_MCP4725.h"
//Or Adafruit_MCP4725 library can be used
#include "navKey.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

#define MCP4725_ADDR 0x60

//TFT pins (other than SPI MOSI, SCLK)
#define LCD_CS  	48          // Chip select line for TFT display
#define LCD_DC  	49          // Data/command line for TFT
#define LCD_RST  	47   
#define ROW_HEIGHT 	10
#define TOP_MARGIN 	14
#define LEFT_MARGIN 		2
#define POT1	 			A9
#define POT2 				A10

// Define various ADC prescaler (Used to speed up ADC read action)
const unsigned char PS_16 = (1 << ADPS2);
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0);
const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

Adafruit_ST7735 lcd = Adafruit_ST7735(LCD_CS, LCD_DC, LCD_RST);
dac_MCP4725 dac;

const int MENU_TOTAL_ITEMS = 6;
uint8_t menu = 1;
const char *waves[] = {"Sine Wave", "Sqaure Wave", "Traingular Wave",
"Saw-tooth Wave (Up)", "Saw-tooth Wave (Down)", "Analog Output"};

uint16_t increment = 1, oldIncrement;
float amplitude =  1, oldAmplitude;
int16_t i;
uint16_t lookup = 0;		//varaible for navigating through the tables
volatile bool dacOnOff = 0;

//lookup table for Sine Function stored in Flash memory
const PROGMEM uint16_t sineLookUp[1024]= 
{
2048,2061,2073,2086,2098,2111,2123,2136,
2148,2161,2174,2186,2199,2211,2224,2236,
2249,2261,2274,2286,2299,2311,2324,2336,
2349,2361,2373,2386,2398,2411,2423,2435,
2448,2460,2472,2484,2497,2509,2521,2533,
2546,2558,2570,2582,2594,2606,2618,2630,
2643,2655,2667,2678,2690,2702,2714,2726,
2738,2750,2762,2773,2785,2797,2808,2820,
2832,2843,2855,2866,2878,2889,2901,2912,
2924,2935,2946,2958,2969,2980,2991,3002,
3013,3024,3036,3047,3057,3068,3079,3090,
3101,3112,3122,3133,3144,3154,3165,3175,
3186,3196,3207,3217,3227,3238,3248,3258,
3268,3278,3288,3298,3308,3318,3328,3337,
3347,3357,3367,3376,3386,3395,3405,3414,
3423,3433,3442,3451,3460,3469,3478,3487,
3496,3505,3514,3523,3531,3540,3548,3557,
3565,3574,3582,3591,3599,3607,3615,3623,
3631,3639,3647,3655,3663,3670,3678,3685,
3693,3700,3708,3715,3722,3730,3737,3744,
3751,3758,3765,3772,3778,3785,3792,3798,
3805,3811,3817,3824,3830,3836,3842,3848,
3854,3860,3866,3872,3877,3883,3888,3894,
3899,3905,3910,3915,3920,3925,3930,3935,
3940,3945,3950,3954,3959,3963,3968,3972,
3976,3980,3985,3989,3993,3997,4000,4004,
4008,4011,4015,4018,4022,4025,4028,4032,
4035,4038,4041,4043,4046,4049,4052,4054,
4057,4059,4061,4064,4066,4068,4070,4072,
4074,4076,4077,4079,4081,4082,4084,4085,
4086,4087,4088,4089,4090,4091,4092,4093,
4094,4094,4095,4095,4095,4095,4095,4095,
4095,4095,4095,4095,4095,4095,4095,4094,
4094,4093,4092,4091,4090,4089,4088,4087,
4086,4085,4084,4082,4081,4079,4077,4076,
4074,4072,4070,4068,4066,4064,4061,4059,
4057,4054,4052,4049,4046,4043,4041,4038,
4035,4032,4028,4025,4022,4018,4015,4011,
4008,4004,4000,3997,3993,3989,3985,3980,
3976,3972,3968,3963,3959,3954,3950,3945,
3940,3935,3930,3925,3920,3915,3910,3905,
3899,3894,3888,3883,3877,3872,3866,3860,
3854,3848,3842,3836,3830,3824,3817,3811,
3805,3798,3792,3785,3778,3772,3765,3758,
3751,3744,3737,3730,3722,3715,3708,3700,
3693,3685,3678,3670,3663,3655,3647,3639,
3631,3623,3615,3607,3599,3591,3582,3574,
3565,3557,3548,3540,3531,3523,3514,3505,
3496,3487,3478,3469,3460,3451,3442,3433,
3423,3414,3405,3395,3386,3376,3367,3357,
3347,3337,3328,3318,3308,3298,3288,3278,
3268,3258,3248,3238,3227,3217,3207,3196,
3186,3175,3165,3154,3144,3133,3122,3112,
3101,3090,3079,3068,3057,3047,3036,3024,
3013,3002,2991,2980,2969,2958,2946,2935,
2924,2912,2901,2889,2878,2866,2855,2843,
2832,2820,2808,2797,2785,2773,2762,2750,
2738,2726,2714,2702,2690,2678,2667,2655,
2643,2630,2618,2606,2594,2582,2570,2558,
2546,2533,2521,2509,2497,2484,2472,2460,
2448,2435,2423,2411,2398,2386,2373,2361,
2349,2336,2324,2311,2299,2286,2274,2261,
2249,2236,2224,2211,2199,2186,2174,2161,
2148,2136,2123,2111,2098,2086,2073,2061,
2048,2035,2023,2010,1998,1985,1973,1960,
1948,1935,1922,1910,1897,1885,1872,1860,
1847,1835,1822,1810,1797,1785,1772,1760,
1747,1735,1723,1710,1698,1685,1673,1661,
1648,1636,1624,1612,1599,1587,1575,1563,
1550,1538,1526,1514,1502,1490,1478,1466,
1453,1441,1429,1418,1406,1394,1382,1370,
1358,1346,1334,1323,1311,1299,1288,1276,
1264,1253,1241,1230,1218,1207,1195,1184,
1172,1161,1150,1138,1127,1116,1105,1094,
1083,1072,1060,1049,1039,1028,1017,1006,
995,984,974,963,952,942,931,921,
910,900,889,879,869,858,848,838,
828,818,808,798,788,778,768,759,
749,739,729,720,710,701,691,682,
673,663,654,645,636,627,618,609,
600,591,582,573,565,556,548,539,
531,522,514,505,497,489,481,473,
465,457,449,441,433,426,418,411,
403,396,388,381,374,366,359,352,
345,338,331,324,318,311,304,298,
291,285,279,272,266,260,254,248,
242,236,230,224,219,213,208,202,
197,191,186,181,176,171,166,161,
156,151,146,142,137,133,128,124,
120,116,111,107,103,99,96,92,
88,85,81,78,74,71,68,64,
61,58,55,53,50,47,44,42,
39,37,35,32,30,28,26,24,
22,20,19,17,15,14,12,11,
10,9,8,7,6,5,4,3,
2,2,1,1,1,0,0,0,
0,0,0,0,1,1,1,2,
2,3,4,5,6,7,8,9,
10,11,12,14,15,17,19,20,
22,24,26,28,30,32,35,37,
39,42,44,47,50,53,55,58,
61,64,68,71,74,78,81,85,
88,92,96,99,103,107,111,116,
120,124,128,133,137,142,146,151,
156,161,166,171,176,181,186,191,
197,202,208,213,219,224,230,236,
242,248,254,260,266,272,279,285,
291,298,304,311,318,324,331,338,
345,352,359,366,374,381,388,396,
403,411,418,426,433,441,449,457,
465,473,481,489,497,505,514,522,
531,539,548,556,565,573,582,591,
600,609,618,627,636,645,654,663,
673,682,691,701,710,720,729,739,
749,759,768,778,788,798,808,818,
828,838,848,858,869,879,889,900,
910,921,931,942,952,963,974,984,
995,1006,1017,1028,1039,1049,1060,1072,
1083,1094,1105,1116,1127,1138,1150,1161,
1172,1184,1195,1207,1218,1230,1241,1253,
1264,1276,1288,1299,1311,1323,1334,1346,
1358,1370,1382,1394,1406,1418,1429,1441,
1453,1466,1478,1490,1502,1514,1526,1538,
1550,1563,1575,1587,1599,1612,1624,1636,
1648,1661,1673,1685,1698,1710,1723,1735,
1747,1760,1772,1785,1797,1810,1822,1835,
1847,1860,1872,1885,1897,1910,1922,1935,
1948,1960,1973,1985,1998,2010,2023,2035
};

void setFrequencyAmplitude(){
  //Set the Frequency and Amplitude
  oldIncrement = increment;
	oldAmplitude = amplitude;
	increment = (analogRead(POT1)>>4)+1;
	amplitude = ((analogRead(POT2)>>4)/64.0);
}

void displayFrequenccyAmplitude(){
	//Only update on screen, if values are changed
	if(oldIncrement!=increment){
		lcd.setCursor(10,60);
		lcd.print(8.5+8.3*(increment-1));
		lcd.print("  ");
	//   Serial.println(increment);    
  }
  if(oldAmplitude!=amplitude){
    lcd.setCursor(10,90);
    lcd.print(amplitude*2.5);
	//   Serial.println(amplitude);
  } 
}

//Function to output one wave complete sine wave form
void generateSineWave(){
  for (i = 0; i < 1024; i= i + increment)
  {
    dac.setVoltage(pgm_read_word(&(sineLookUp[i]))*amplitude, false);
  }
}

//Function to output one wave complete sqaure wave form
void generateSquareWave(){
  for (i = 0; i < 512; i= i + increment)
  {
    dac.setVoltage(amplitude*4095, false);
  }
  for (i = 512; i > 0; i= i - increment)
  {
    dac.setVoltage(0, false);
  } 
}

//Function to output one wave complete triangular wave form
void generateTraingularWave(){
  for (i = 0; i < 512; i= i + increment)
  {
    dac.setVoltage(i*8*amplitude, false);
  }
  for (i = 512; i > 0; i= i - increment)
  {
    dac.setVoltage(i*8*amplitude, false);
  }  
}

//Function to output one wave complete sawtooth wave (up) form
void generateSawtoothWaveUp(){
  for (i = 0; i < 1024; i= i + increment)
  {
    dac.setVoltage(i*4*amplitude, false);
  }
}

//Function to output one wave complete sawtooth wave (down) form
void generateSawtoothWaveDown(){
  for (i = 1023; i > 0; i= i - increment)
  {
    dac.setVoltage(i*4*amplitude, false);
  }
}

//Function to output one wave complete sqaure wave form
void generateAnalogOutput(){
	dac.setVoltage(4095*amplitude, false);
}

void setup() {
  Serial.begin(250000);
	Serial.println("Function Generator Started");
  lcd.initR(INITR_BLACKTAB);
  lcd.setRotation(1);
  lcd.fillScreen(ST7735_BLACK);
	menuUpdate();
}

void loop() {
	Serial.println("loop");
	CheckSW();
}

void navKeyInterruptCenterPress(){
	dacOnOff = 0;
//	Serial.println("Dettached Interrupt");
}

void CheckSW() {
	Serial.println("CheckSW");
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
	else if(menuMove == 3){
		if(menu+1>MENU_TOTAL_ITEMS)
			menu = 1;
		else
			menu++;
		menuUpdate();
	}
	else if(menuMove == 1){
		if(menu<2)
			menu = MENU_TOTAL_ITEMS;
		else
			menu--;
	  menuUpdate();		
	}
	else if(menuMove == 2){
		startFunctionGenerator();
	}
}

//Update menu based on the user input
void menuUpdate(){
	Serial.println("menuUpdate");
	for(int i = 0; i<MENU_TOTAL_ITEMS; i++){
		lcd.setCursor(LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT*i);
		if(i+1 == menu){
			lcd.setTextColor(ST7735_BLACK,ST7735_YELLOW);
			lcd.print(waves[i]);
		}
		else{
			lcd.setTextColor(ST7735_YELLOW, ST7735_BLACK);
			lcd.print(waves[i]);
		}
	}
}

void startFunctionGenerator(){
	Serial.println("startFunctionGenerator");
	navKeyAttachInterruptMenuPress();
	
	dac.begin(MCP4725_ADDR);
	lcd.fillScreen(ST7735_BLACK);
  lcd.setTextColor(ST7735_GREEN);
  lcd.setCursor(10,30);
  lcd.print(waves[menu-1]);
	lcd.setTextColor(ST7735_WHITE);
  lcd.setCursor(10,50);
  lcd.print("Frequency (Hz):");  
  lcd.setCursor(10,80);
  lcd.print("Amplitude (V):");
  lcd.setTextColor(ST7735_YELLOW, ST7735_BLACK);
	
  /*Speed up ADC*/
  // set up the ADC
  ADCSRA &= ~PS_128;  // remove bits set by Arduino library
  // you can choose a prescaler from above.
  // PS_16, PS_32, PS_64 or PS_128
  ADCSRA |= PS_32;    // set our own prescaler to 64	

	setFrequencyAmplitude();
	lcd.setCursor(10,60);
	if(menu==6)	lcd.print("-");
	else  lcd.print(8.5+8.3*(increment-1));
  lcd.print("  ");
  lcd.setCursor(10,90);
  lcd.print(amplitude*2.5);
	
	dacOnOff = 1;

	while(dacOnOff){
		setFrequencyAmplitude();
		displayFrequenccyAmplitude();
		switch(menu){
			case 1:
				generateSineWave();
				break;
			case 2:
				generateSquareWave();
				break;
			case 3:
				generateTraingularWave();
				break;
			case 4:
				generateSawtoothWaveUp();
				break;
			case 5:
				generateSawtoothWaveDown();
				break;
			case 6:
				generateAnalogOutput();
				break;				
		}
	}
	navKeyDettachInterruptMenuPress();
	lcd.fillScreen(ST7735_BLACK);
	menuUpdate();
}