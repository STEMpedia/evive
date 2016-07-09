#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>

#define TFT_CS  48          // Chip select line for TFT display
#define TFT_DC   49          // Data/command line for TFT
#define TFT_RST  47       // Reset line for TFT (or connect to +5V)

char* menu[] = {"       udo Main Menu",
                "Motor",
                "Potentiometer     ",
                "Switches          ",
                "IO3V3     ",
                "Sensing      ",
                "Logging        ",
                "Plotting  ",
                "Wireless Communication     "
              "user defined mode"};
typedef void (* MenuFuncPtr) (); // this is a typedef to the menu functions
MenuFuncPtr menu_func[] = {0,
                tftTextTest,
                tftPrintTest,
                tftLinesTest,
                tftRectTest,
                tftBarGraphTest,
                tftCirclesTest,
                tftMediaButtonsTest,
                tftBitmapTest};   

#define numMenu (sizeof(menu)/sizeof(char *))-1 //array size       

#define menu_top 12   // Postition of first menu item from top of screen
char menu_select;     // Currently elected menu item
char keydown=0;       // Jog key pressed?

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(9600);
  pinMode(TFT_CS, OUTPUT);
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735R chip, black tab    
  tft.setRotation(1);               // Set to landscape mode
  tft.fillScreen(ST7735_BLACK);     // Fill screen with black
  tftMenuInit();                    // Draw menu
  menu_select=1;                    // Select 1st menu item 
  tftMenuSelect(menu_select);       // Highlight selected menu item
  pinMode(A9,INPUT);
}

void loop() {
  int x,navKeyPress;
  navKeyPress=digitalRead(28);
  x = analogRead (9);               // Read navigation key switch input
  if (navKeyPress==1 && keydown==0) {
    // Select
    keydown=1;
    menu_func[menu_select]();       // Call the appropriate menu function from array
                                    // Note the syntax for doing this
    tftMenuInit();                  // Redraw the Menu
    tftMenuSelect(menu_select);     // Highlight the current menu item
  }
  else if (x<20){
    keydown=0;
  }
  else if ((x>190)&&(x<230) && (keydown==0)) {
    // Up
    // move up one menu item, if at top wrap to bottom
    keydown=1;    
    if (menu_select>1) tftMenuSelect(menu_select-1);
    else tftMenuSelect(numMenu);
  }
  else if ((x>385)&&(x<425) && (keydown==0)){
    // Right
    keydown=1;    
  }
  else if ((x>585)&&(x<625) && (keydown==0)){
    // Down
    // move down one menu item, if at bottom wrap to top
    keydown=1;    
    if (menu_select<numMenu) tftMenuSelect(menu_select+1);
    else tftMenuSelect(1);   
  }
  else if ((x>820)&&(x<860) && (keydown==0)){
    // Left
    keydown=1;    
  }
}


