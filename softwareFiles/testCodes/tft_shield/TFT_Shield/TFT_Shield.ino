/* 
 Hobbytronics Arduino TFT Shield Example Program
 
 Requires the Adafruit GFX and ST7735 Libraries, please see product page for download links
 
 This program demonstrates the main features of the TFT shield and the Adafruit Graphics Libraries
 
*/
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>

#define TFT_CS  48          // Chip select line for TFT display
#define TFT_DC   49          // Data/command line for TFT
#define TFT_RST  47       // Reset line for TFT (or connect to +5V)
#define lcdBacklight  NULL
#define SD_CS    34          // Chip select line for SD card

/* For those of you interested in creating a Menu system, we have defined
   two arrays here. One holds the Menu Title and menu headings, and the other
   holds the associated function to be called. This is a great way to simplify
   the configuration of a menu especially when multiple menu's are rquired
*/   
char* menu[] = {"       udo Main Menu",
                "Motor",
                "Potentiometer     ",
                "Switches          ",
                "IO3V3     ",
                "Sensing      ",
                "Logging        ",
                "Plotting  ",
                "Wireless Communication     ",
              "user defined mode",
                 "mmmmmmmmmmmmmmmmmmmmmmmmmmm",
                 "abcdefghijklmnopqrstuvwxyza",
                 "Wireless Communicationabcdeffffffff",
               };
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
// It's usefult to know the number of menu items without hardcoding it
// We can calculate it thus.. (subtract 1 for the menu heading)
#define numMenu (sizeof(menu)/sizeof(char *))-1 //array size       

#define menu_top 12   // Postition of first menu item from top of screen
char menu_select;     // Currently elected menu item
char keydown=0;       // Jog key pressed?
char sd_card=0;       // SD Card inserted?
  
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup(void) {
  Serial.begin(9600);
  // Set TFT and SD Chip Select pins as output
  pinMode(TFT_CS, OUTPUT);
  pinMode(SD_CS, OUTPUT);
  
  // If your TFT's plastic wrap has a Red Tab, use the following:
  //tft.initR(INITR_REDTAB);   // initialize a ST7735R chip, red tab
  // If your TFT's plastic wrap has a Green Tab, use the following:
  //tft.initR(INITR_GREENTAB); // initialize a ST7735R chip, green tab
  // If your TFT's plastic wrap has a Black Tab, use the following:
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735R chip, black tab    
  
  tft.setRotation(1);               // Set to landscape mode
  analogWrite(lcdBacklight, 255);   // Turn Backlight on full
  
  // Check for SD Card
  if (!SD.begin(SD_CS)) 
  {
    // No SD card, or failed to initialise card
    sd_card=0;
    // Arduino SD library does something to SPI speed when it fails
    // So need to reset otherwise screen is slow.
    SPI.setClockDivider(SPI_CLOCK_DIV4); // 16/4 MHz
  }  
  else sd_card=1;
  
  tft.fillScreen(ST7735_BLACK);     // Fill screen with black

  tftMenuInit();                    // Draw menu
  menu_select=1;                    // Select 1st menu item 
  tftMenuSelect(menu_select);       // Highlight selected menu item
  pinMode(A9,INPUT);
}

void loop() {
  int x,navKeyPress;
  navKeyPress=digitalRead(28);
  x = analogRead (9);               // Read Jog switch input
  Serial.println(x);
  /* With the resistor network the voltage generated for each key press are (approx, based on 5V supply)
     key       voltage   ADC value
     SELECT    0.0V         0
     UP        0.7V       143
     LEFT      1.6V       327
     DOWN      2.5V       512
     RIGHT     3.6V       737
  */
  if (navKeyPress==1 && keydown==0) {
    // Select
    keydown=1;
    menu_func[menu_select]();       // Call the appropriate menu function from array
                                    // Note the syntax for doing this
    delay(2000);
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

void tftMenuInit()
{
  // Clear screen and display the menu
  char i;
  
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextSize(1);
  
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_GREEN, ST7735_BLACK); 
  tft.println(menu[0]);

  tft.drawLine(0, 9, tft.width()-1, 9, ST7735_GREEN);
  
  tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);  
  for(i=1;i<=numMenu;i++)
  {
     tft.setCursor(0, ((i-1)*10)+menu_top);    
     tft.println(menu[i]);
  }  
}

void tftMenuSelect(char menuitem) 
{
  // Highlight a selected menu item
  char i;
  // Remove highlight of current item
  tft.setCursor(0, ((menu_select-1)*10)+menu_top);
  tft.setTextColor(ST7735_YELLOW, ST7735_BLACK); 
  tft.println(menu[menu_select]); 
  // Highlight new menu item
  tft.setCursor(0, ((menuitem-1)*10)+menu_top);
  tft.setTextColor(ST7735_YELLOW, ST7735_BLUE); 
  tft.println(menu[menuitem]);
  // change menu_select to new item  
  menu_select=menuitem;

}

void tftTextTest(void)
{
  // Print some small text
  char * lorem="Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat.";
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextWrap(true);
  tft.println(lorem);
  tft.println(lorem); 
  tft.println(lorem);    
  delay(2000);
}  

void tftPrintTest() 
{
  // Print different font sizes
  char * hello="Hello World!";
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST7735_MAGENTA);
  tft.setTextSize(1);
  tft.println(hello);
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(2);
  tft.println(hello);
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(3);
  tft.println(hello);
  tft.setTextColor(ST7735_BLUE);
  tft.setTextSize(4);
  tft.print(1234.567); 
}

void tftLinesTest(void) 
{
  // Print lines
  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) 
  {
    tft.drawLine(0, 0, x, tft.height()-1, ST7735_YELLOW);
  }
  for (int16_t y=0; y < tft.height(); y+=6) 
  {
    tft.drawLine(0, 0, tft.width()-1, y, ST7735_YELLOW);
  }

  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) 
  {
    tft.drawLine(tft.width()-1, 0, x, tft.height()-1, ST7735_YELLOW);
  }
  for (int16_t y=0; y < tft.height(); y+=6) 
  {
    tft.drawLine(tft.width()-1, 0, 0, y, ST7735_YELLOW);
  }

  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) 
  {
    tft.drawLine(0, tft.height()-1, x, 0, ST7735_YELLOW);
  }
  for (int16_t y=0; y < tft.height(); y+=6) 
  {
    tft.drawLine(0, tft.height()-1, tft.width()-1, y, ST7735_YELLOW);
  }

  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) 
  {
    tft.drawLine(tft.width()-1, tft.height()-1, x, 0, ST7735_YELLOW);
  }
  for (int16_t y=0; y < tft.height(); y+=6) 
  {
    tft.drawLine(tft.width()-1, tft.height()-1, 0, y, ST7735_YELLOW);
  }
}

void tftRectTest(void) 
{
  // Print Rectangles
  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) 
  {
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, ST7735_GREEN);
  }
}

void tftBarGraphTest(void) 
{
  // Print Bar Graph
  int16_t x;
  unsigned char origin_x=10;  
  unsigned char origin_y=115;
  unsigned char width=15;
  unsigned char spacing=20;
  unsigned char height=10;
  tft.fillScreen(ST7735_BLACK);
  
  tft.drawLine(origin_x, origin_y, origin_x, 1, ST7735_BLUE);
  tft.drawLine(origin_x, origin_y, tft.width(), origin_y, ST7735_BLUE);  

  for (int16_t x=origin_x+1; x <tft.width()-spacing; x+=spacing) 
  {
    tft.fillRect(x, origin_y-height , width, height, ST7735_GREEN);
    height+=10;
  }


  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.setCursor(0, origin_y);
  tft.print("0");
  tft.setCursor(0, 1);
  tft.print("10");  
  for (char i=0; i <7; i++) 
  {
    x=origin_x+8+(spacing*i);
    tft.setCursor(x, origin_y+3);
    tft.print(i+1);     
  } 
  tft.setCursor(40, 20);
  tft.print("Bar Graph");   
  
  delay(2000);
}

void tftCirclesTest(void) 
{
  // Print Circles
  char radius=10;
  tft.fillScreen(ST7735_BLACK);  
  for (int16_t x=radius; x < tft.width(); x+=radius*2) 
  {
    for (int16_t y=radius; y < tft.height(); y+=radius*2) 
    {
      tft.fillCircle(x, y, radius, ST7735_BLUE);
    }
  }
  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) 
  {
    for (int16_t y=0; y < tft.height()+radius; y+=radius*2) 
    {
      tft.drawCircle(x, y, radius, ST7735_WHITE);
    }
  } 
}

void tftMediaButtonsTest(void) 
{
  // Media Buttons
  tft.setRotation(0); // Set to landscape   
  tft.fillScreen(ST7735_BLACK);
  tft.fillRoundRect(25, 10, 78, 60, 8, ST7735_WHITE);
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_RED);
  delay(500);
  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, ST7735_WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, ST7735_GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST7735_GREEN);
  delay(500);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, ST7735_RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST7735_RED);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_GREEN);
  tft.setRotation(3); // Set to landscape   
}

void tftBitmapTest(void)
{
  // Show bitmap information, then display bitmap
  tft.fillScreen(ST7735_BLACK);   
  tft.setTextColor(ST7735_YELLOW, ST7735_BLACK); 
  tft.setCursor(0, 0);  
  if(sd_card==1)
  {
     bmpDraw("ht_logo.bmp", 0, 0);
     delay(2000);
  }
  else
  {
     tft.println("No SD Card");
     tft.println("Detected");     
  }
}

// This function opens a Windows Bitmap (BMP) file and
// displays it at the given coordinates.  It's sped up
// by reading many pixels worth of data at a time
// (rather than pixel by pixel).  Increasing the buffer
// size takes more of the Arduino's precious RAM but
// makes loading a little faster.  20 pixels seems a
// good balance.

#define BUFFPIXEL 10

void bmpDraw(char *filename, uint8_t x, uint8_t y) {

  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel buffer (R+G+B per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0;

  if((x >= tft.width()) || (y >= tft.height())) return;

  // Open requested file on SD card
  if ((bmpFile = SD.open(filename)) == NULL) {
    tft.println("File not found");
    return;
  }
  tft.print("Name  : "); tft.println(filename);
  
  // Parse BMP header
  if(read16(bmpFile) == 0x4D42) { // BMP signature
    tft.print("Size  : "); tft.println(read32(bmpFile));
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    tft.print("Offset: "); tft.println(bmpImageoffset, DEC);
    // Read DIB header
    tft.print("Header: "); tft.println(read32(bmpFile));
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if(read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
      tft.print("Depth : "); tft.println(bmpDepth);
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

        goodBmp = true; // Supported BMP format -- proceed!
        tft.print("Image : ");
        tft.print(bmpWidth);
        tft.print('x');
        tft.println(bmpHeight);

        delay(4000);
        
        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= tft.width())  w = tft.width()  - x;
        if((y+h-1) >= tft.height()) h = tft.height() - y;

        // Set TFT address window to clipped image bounds
        tft.setAddrWindow(x, y, x+w-1, y+h-1);

        for (row=0; row<h; row++) { // For each scanline...

          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          if(flip) // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) { // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
          }

          for (col=0; col<w; col++) { // For each pixel...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) { // Indeed
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
            }

            // Convert pixel from BMP to TFT format, push to display
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            tft.pushColor(tft.Color565(r,g,b));
          } // end pixel
        } // end scanline
      } // end goodBmp
    }
  }

  bmpFile.close();
  if(!goodBmp) tft.println("BMP error.");
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t read16(File f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}
