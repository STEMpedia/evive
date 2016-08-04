//Derived from ultralcd.cpp in Marlin-RC used in 3D printers
//Modified for http://evive.cc by Dhrupal R Shah and Akshat Agarwal
#include "screen.h"

#if ENABLED(SCREEN)
//#include "language.h"
//#include "status.h"
#include "screenImplementation.h"
//#define LCD_UPDATE_INTERVAL 100
#define LCD_NUM_LINES  11
#define LCD_CLICKED (menuMove==2)

#ifndef ENCODER_STEPS_PER_MENU_ITEM
  #define ENCODER_STEPS_PER_MENU_ITEM 1
#endif

#ifndef ENCODER_PULSES_PER_STEP
  #define ENCODER_PULSES_PER_STEP 1
#endif

unsigned long lastStatusUpdateTime = 0;
/* extern bool _MOTOR1_EN = 0;
extern bool _MOTOR2_EN = 0;
extern int8_t _SLIDESW1_D1_OUTPIN = -1;
extern int8_t _SLIDESW1_D2_OUTPIN = -1;
extern int8_t _SLIDESW1_VAL = -1;
extern int8_t _SLIDESW2_D1_OUTPIN = -1;
extern int8_t _SLIDESW2_D2_OUTPIN = -1;
extern int8_t _SLIDESW2_VAL = -1;
extern int8_t _POT1_OUTPIN = -1;
extern int _POT1_VAL = -1;
extern int8_t _POT2_OUTPIN = -1;
extern int _POT2_VAL = -1;
extern int8_t _TACTILESW1_OUTPIN = -1;
extern int8_t _TACTILESW2_OUTPIN = -1; */

typedef void (*menuFunc_t)(); // Function pointer to menu functions.

static void lcd_home_menu();
static void lcd_control_menu();
static void lcd_control_motors_menu();
static void lcd_control_servos_menu();
//static void lcd_control_pot_menu();
//static void lcd_control_slidesw_menu();
//static void lcd_control_tactilesw_menu();
static void lcd_sensing_menu();
static void lcd_log_menu();
static void lcd_pin_state();
static void lcd_evive_oscilloscope();
static void lcd_dac_menu();
static void lcd_user_def_menu();
static void lcd_remove_function_menu();
static void lcd_control_motor1();
static void lcd_control_motor2();
static void lcd_control_motor12();
static void lcd_control_servo1();
static void lcd_control_servo2();
static void lcd_control_servo12();
static void lcd_control_stepper();
static void lcd_control_status();
static void lcd_sensing_VV();
static void lcd_sensing_VI();
static void lcd_sensing_status_VV();
static void lcd_sensing_status_VI();
static void lcd_dac_analog_out();
static void lcd_dac_sine();
static void lcd_dac_sqaure();
static void lcd_dac_triangular();
static void lcd_dac_sawtooth();
static void add_user_def_fun_1();
static void add_user_def_fun_2();
static void add_user_def_fun_3();
static void add_user_def_fun_4();
static void add_user_def_fun_5();
static void actionRemove();


#if ENABLED(SDSUPPORT)
  static void lcd_sdcard_menu();
    static void menu_action_sdfile(const char* filename, char* longFilename);
    static void menu_action_sddirectory(const char* filename, char* longFilename);
#endif

static void menu_action_back(menuFunc_t data);
static void menu_action_submenu(menuFunc_t data);
static void menu_action_function(menuFunc_t data);
static void menu_action_setting_edit_bool(const char* pstr, bool* ptr);
static void menu_action_setting_edit_int(const char* pstr, int* ptr, int minValue, int maxValue);
static void menu_action_setting_edit_callback_int3(const char* pstr, int* ptr, int minValue, int maxValue, menuFunc_t callbackFunc);

uint8_t currentMenuViewOffset=0;              /* scroll offset in the current menu */
//removed menupress and menumove, lastKeyMoveTime to navkey.h
int8_t encoderPosition;

menuFunc_t currentMenu = lcd_home_menu; /* function pointer to the currently active menu, assgined to home menu. Default: home menu*/
uint8_t lcdDrawUpdate = 2;                  /* Set to none-zero when the LCD needs to draw, decreased after every draw. 
Set to 2 in LCD routines so the LCD gets at least 1 full redraw (first redraw is partial) */
//prevMenu and prevEncoderPosition are used to store the previous menu location when editing settings.
menuFunc_t prevMenu=NULL;
uint16_t prevEncoderPosition;
//Variables used when editing values (There are more in ultralcd, if ever edit menu is included)
menuFunc_t callbackFunc;

/* Helper macros for menu */
#define START_MENU() do { \
    if (encoderPosition < currentMenuViewOffset) currentMenuViewOffset = encoderPosition;\
    uint8_t _lineNr = currentMenuViewOffset, _menuItemNr;\
    bool wasClicked = LCD_CLICKED; \
    for(uint8_t _drawLineNr = 0; _drawLineNr < LCD_NUM_LINES; _drawLineNr++, _lineNr++) { \
        _menuItemNr = 0;
    
#define MENU_ITEM(type, label, args...) do { \
    if (_menuItemNr == _lineNr) { \
        if (lcdDrawUpdate) { \
          /*Serial.print("encoder position: ");\
          Serial.println(encoderPosition);\
          Serial.print("Current menu view offset: ");\
          Serial.println(currentMenuViewOffset);\
          Serial.print("menuItemNr: ");\
          Serial.println(_menuItemNr);\
          Serial.print("lineNr ");\
          Serial.println(_lineNr);\
          Serial.print("_drawLineNr ");\
          Serial.println(_drawLineNr);\*/\
            const char* _label_pstr = PSTR(label); \
            if ((encoderPosition) == _menuItemNr) { \
              lcd_implementation_text_and_background_color(ST7735_BLACK, ST7735_RED);\
              lcd_implementation_drawmenu_ ## type ## _selected (_drawLineNr, _label_pstr , ## args ); \
            }\
            else{\
              lcd_implementation_text_and_background_color(ST7735_RED, ST7735_BLACK);\
              lcd_implementation_drawmenu_ ## type (_drawLineNr, _label_pstr , ## args ); \
            }\
        }\
        if (wasClicked && (encoderPosition == _menuItemNr)) {\
          menu_action_ ## type ( args ); \
          return;\
        }\
    }\
    _menuItemNr++;\
} while(0)
#define MENU_ITEM_DUMMY() do { _menuItemNr++; } while(0)
#define MENU_ITEM_EDIT(type, label, args...) MENU_ITEM(setting_edit_ ## type, label, PSTR(label) , ## args )
#define MENU_ITEM_EDIT_CALLBACK(type, label, args...) MENU_ITEM(setting_edit_callback_ ## type, label, PSTR(label) , ## args )
#define END_MENU() \
    if (encoderPosition >= _menuItemNr) {\
      lcdDrawUpdate=2; \
      encoderPosition = 0; \
      currentMenuViewOffset=0; \
      _lineNr=0;\
    }\
    else if (encoderPosition<0) {\
      lcdDrawUpdate=2; \
      encoderPosition=_menuItemNr-1; \
      currentMenuViewOffset=(encoderPosition-LCD_NUM_LINES+1>0)?encoderPosition-LCD_NUM_LINES+1:currentMenuViewOffset;\
      _lineNr=0;\
    }\
    else if (encoderPosition >= currentMenuViewOffset + LCD_NUM_LINES) { \
      currentMenuViewOffset = encoderPosition  - LCD_NUM_LINES + 1; \
      lcdDrawUpdate = 2; \
      _lineNr = currentMenuViewOffset - 1; \
      _drawLineNr = -1; } \
    } } while(0)

#define EXIT_MENU(args) back_menu_process(args)

void back_menu_process(menuFunc_t data)
{
  if(menuMove == 4)  
  {
//    lcd_quick_feedback(); 
    menu_action_back(data);
  }
}
    
/**
 * General function to go directly to a menu
 */
static void lcd_goto_menu(menuFunc_t menu, const bool feedback = false, const uint32_t encoder = 0) {
  if (currentMenu != menu) {
    lcd_implementation_clear_menu();
    lcdDrawUpdate=2;
    currentMenu = menu;
    encoderPosition = encoder;
  }
}
//See function lcd_status_screen() for examples of how to handle pages without any menus on them

static void lcd_returnto_home() {lcd_goto_menu(lcd_home_menu);}
  
void lcd_update(){      //will be called in idle, etc
  navKeyUpdate();
  if (menuMove != 0 || menuPress != 0){
    lcdDrawUpdate = 1;
    
    if (menuPress == 1)
    { lcd_implementation_clear_menu();
      currentMenu = lcd_home_menu;
      encoderPosition = 0;
    }
    else if(menuMove == 3)
      encoderPosition++;
    else if(menuMove == 1)
      encoderPosition--;
    
  }
    (*currentMenu)(); 
    //if (lcdDrawUpdate == 2)
        //lcd_implementation_clear_menu();          //implement in lcd implementation
    if (lcdDrawUpdate)
        lcdDrawUpdate--;
    if (millis()>lastStatusUpdateTime+MIN_TIME2)
    {
      batteryUpdate();
      vvrUpdate();
      lastStatusUpdateTime =millis();
    }
}
/**
*
*"Home" menu
*
*/
static void lcd_home_menu(){
  START_MENU();
  MENU_ITEM(submenu, MSG_CONTROL, lcd_control_menu);
  MENU_ITEM(submenu, MSG_SENSING, lcd_sensing_menu);
  MENU_ITEM(function, MSG_OSCILLOSCOPE, lcd_evive_oscilloscope);
  MENU_ITEM(submenu, MSG_LOG, lcd_log_menu);
  MENU_ITEM(function, MSG_PIN_STATE, lcd_pin_state);
  MENU_ITEM(submenu, MSG_DAC, lcd_dac_menu);
  MENU_ITEM(submenu, MSG_USER_DEF, lcd_user_def_menu);
//  MENU_ITEM(submenu, MSG_REMOVE_FUNCTION, lcd_remove_function_menu);
  //add menu
  END_MENU();
}
  
static void lcd_control_menu(){
  START_MENU();
  MENU_ITEM(submenu, MSG_CONTROL_MOTOR, lcd_control_motors_menu);
  MENU_ITEM(submenu, MSG_CONTROL_SERVO, lcd_control_servos_menu);
  MENU_ITEM(function, MSG_CONTROL_STEPPER_MOTOR, lcd_control_stepper);
    END_MENU(); 
  EXIT_MENU(lcd_home_menu);
}

static void lcd_control_motors_menu(){
  START_MENU();
  MENU_ITEM(function, MSG_CONTROL_MOTOR1, lcd_control_motor1 );
  MENU_ITEM(function, MSG_CONTROL_MOTOR2, lcd_control_motor2 );
  MENU_ITEM(function, MSG_CONTROL_MOTOR12, lcd_control_motor12 );
  END_MENU();
  EXIT_MENU(lcd_control_menu);
}

static void lcd_control_motor1(){
  addMotor1();
  lcd_control_status_template();
  currentMenu = lcd_control_status;
    //add this function to list of active functions
  //lcd_implementation_ ..... ()        //display motors and servo  
}

static void lcd_control_motor2(){
  addMotor2();
  lcd_control_status_template();
  currentMenu = lcd_control_status;
  //add this function to list of active functions
  //lcd_implementation_ ..... ()        //display motors and servo
}

static void lcd_control_motor12(){
  addMotor12();
  lcd_control_status_template();
  currentMenu = lcd_control_status;
  //add this function to list of active functions
  //lcd_implementation_ ..... ()        //display motors and servo  
}

static void lcd_control_servos_menu(){
  START_MENU();
  MENU_ITEM(function, MSG_CONTROL_SERVO1, lcd_control_servo1 );
  MENU_ITEM(function, MSG_CONTROL_SERVO2, lcd_control_servo2 );
  MENU_ITEM(function, MSG_CONTROL_SERVO12, lcd_control_servo12 );
  END_MENU();
  EXIT_MENU(lcd_control_menu);
}

static void lcd_control_servo1(){
  addServo1();
  lcd_control_status_template();
  currentMenu = lcd_control_status;
  //add this function to list of active functions
  //lcd_implementation_ ..... ()        //display motors and servo
}

static void lcd_control_servo2(){
  addServo2();
  lcd_control_status_template();
  currentMenu = lcd_control_status;
  //add this function to list of active functions
  //lcd_implementation_ ..... ()        //display motors and servo
}

static void lcd_control_servo12(){
  addServo12();
  lcd_control_status_template();
  currentMenu = lcd_control_status;
  //add this function to list of active functions
  //lcd_implementation_ ..... ()        //display motors and servo
}

static void lcd_control_stepper(){
  addStepper();
  lcd_control_status_template();
  currentMenu = lcd_control_status;
  //lcd_implementation_ ..... ()        //display motors and servo
}

static void lcd_control_status(){
  if(_MOTOR1_EN)  lcd_implementation_control_status_motor(0);
  else if(_SERVO1_EN) lcd_implementation_control_status_servo(0);
  if(_MOTOR2_EN)  lcd_implementation_control_status_motor(1);
  else if(_SERVO2_EN) lcd_implementation_control_status_servo(1);
  if(_STEPPER_EN) lcd_implementation_control_status_stepper();
}

static void lcd_sensing_menu(){
  START_MENU();
  MENU_ITEM(function, MSG_SENSING_PROBE_VV, lcd_sensing_VV );
  MENU_ITEM(function, MSG_SENSING_PROBE_VI, lcd_sensing_VI );
  END_MENU();
  EXIT_MENU(lcd_control_menu);
}

static void lcd_sensing_VV(){
  lcd_sensing_status_template(0);
  currentMenu=lcd_sensing_status_VV;
}

static void lcd_sensing_status_VV(){
  lcd_implementation_sensing_status(0);
}

static void lcd_sensing_VI(){
  lcd_sensing_status_template(1);
  currentMenu=lcd_sensing_status_VI;
}

static void lcd_sensing_status_VI(){
  lcd_implementation_sensing_status(1);
}

static void lcd_log_menu(){
  //add code here
}

static void lcd_pin_state(){
  //add code here
}

static void lcd_dac_menu(){
  START_MENU();
  MENU_ITEM(function, MSG_ANALOG_OUT, lcd_dac_analog_out );
  MENU_ITEM(function, MSG_SINE, lcd_dac_sine );
  MENU_ITEM(function, MSG_SQUARE, lcd_dac_sqaure );
  MENU_ITEM(function, MSG_TRIANGULAR, lcd_dac_triangular );
  MENU_ITEM(function, MSG_SAWTOOTH, lcd_dac_sawtooth ); 
  END_MENU();
  EXIT_MENU(lcd_control_menu);
}

static void lcd_dac_analog_out(){
  //add code here 
}

static void lcd_dac_sine(){
  //add code here 
}

static void lcd_dac_sqaure(){
  //add code here 
}

static void lcd_dac_triangular(){
  //add code here 
}

static void lcd_dac_sawtooth(){
  //add code here 
}

static void lcd_user_def_menu(){
  START_MENU();
  #ifdef USER_DEFINED_FUNCTION_1
    MENU_ITEM(function, USER_DEFINED_FUNCTION_1, add_user_def_fun_1 );
  #endif
  #ifdef USER_DEFINED_FUNCTION_2
    MENU_ITEM(function, USER_DEFINED_FUNCTION_2, add_user_def_fun_2 );
  #endif
  #ifdef USER_DEFINED_FUNCTION_3
    MENU_ITEM(function, USER_DEFINED_FUNCTION_3, add_user_def_fun_3 );
  #endif
  #ifdef USER_DEFINED_FUNCTION_4
    MENU_ITEM(function, USER_DEFINED_FUNCTION_4, add_user_def_fun_4 );
  #endif
  #ifdef USER_DEFINED_FUNCTION_5
    MENU_ITEM(function, USER_DEFINED_FUNCTION_5, add_user_def_fun_5 );
  #endif  

  END_MENU();
  EXIT_MENU(lcd_home_menu);
}

static void add_user_def_fun_1(){
  add_user_def_fun(1);
}

static void add_user_def_fun_2(){
  add_user_def_fun(2);
}

static void add_user_def_fun_3(){
  add_user_def_fun(3);
}

static void add_user_def_fun_4(){
  add_user_def_fun(4);
}

static void add_user_def_fun_5(){
  add_user_def_fun(5);
}

static void lcd_remove_function_menu(){
//  START_MENU();
//  for(uint8_t i = 0; i < actionFuncListNum; i++)
//    MENU_ITEM(function, actionFuncList[i], actionRemove);
//  END_MENU();
//  EXIT_MENU(lcd_home_menu);
}

static void actionRemove(){
  actionRemove(encoderPosition+1);
}


static void lcd_evive_oscilloscope(){
  evive_oscilloscope();
}

/**
There are certain #defines for menu_edit type entries, if we end up including those in our code, include the #defines near line 1326
*/
/**
*Menu actions
*/
static void menu_action_back(menuFunc_t func) { lcd_goto_menu(func); }
static void menu_action_submenu(menuFunc_t func) { lcd_goto_menu(func); }
static void menu_action_function(menuFunc_t func) { (*func)(); }

#if ENABLED(SDSUPPORT)

  static void menu_action_sdfile(const char* filename, char* longFilename) {
    char cmd[30];
    char* c;
    sprintf_P(cmd, PSTR("M23 %s"), filename);
    for (c = &cmd[4]; *c; c++) *c = tolower(*c);
    enqueuecommand(cmd);
    enqueuecommands_P(PSTR("M24"));
    lcd_return_to_status();
  }

  static void menu_action_sddirectory(const char* filename, char* longFilename) {
    card.chdir(filename);
    encoderPosition = 0;
  }

#endif //SDSUPPORT

static void menu_action_setting_edit_bool(const char* pstr, bool* ptr) { *ptr = !(*ptr); }
static void menu_action_setting_edit_callback_bool(const char* pstr, bool* ptr, menuFunc_t callback) {
  menu_action_setting_edit_bool(pstr, ptr);
  (*callback)();
}

//Put a #define SCREENOFF which turns off all screen initialisations and everything for like a battery saver application
bool lcd_clicked() { return LCD_CLICKED; }

void lcd_init(){
  //Serial.println("in lcd_init");
  pinMode(LCD_CS,OUTPUT);
  lcd_implementation_init();
}
/*********************************/
/** Number to string conversion **/
/*********************************/

char conv[8];

// Convert float to rj string with 123 or -12 format
char *ftostr3(const float& x) { return itostr3((int)x); }

// Convert float to rj string with _123, -123, _-12, or __-1 format
char *ftostr4sign(const float& x) { return itostr4sign((int)x); }

// Convert int to string with 12 format
char* itostr2(const uint8_t& x) {
  //sprintf(conv,"%5.1f",x);
  int xx = x;
  conv[0] = (xx / 10) % 10 + '0';
  conv[1] = xx % 10 + '0';
  conv[2] = 0;
  return conv;
}

// Convert float to string with +123.4 format
char* ftostr31(const float& x) {
  int xx = abs(x * 10);
  conv[0] = (x >= 0) ? '+' : '-';
  conv[1] = (xx / 1000) % 10 + '0';
  conv[2] = (xx / 100) % 10 + '0';
  conv[3] = (xx / 10) % 10 + '0';
  conv[4] = '.';
  conv[5] = xx % 10 + '0';
  conv[6] = 0;
  return conv;
}

// Convert float to string with 123.4 format, dropping sign
char* ftostr31ns(const float& x) {
  int xx = abs(x * 10);
  conv[0] = (xx / 1000) % 10 + '0';
  conv[1] = (xx / 100) % 10 + '0';
  conv[2] = (xx / 10) % 10 + '0';
  conv[3] = '.';
  conv[4] = xx % 10 + '0';
  conv[5] = 0;
  return conv;
}

// Convert float to string with 123.45 format
char *ftostr32(const float& x) {
  long xx = abs(x * 100);
  conv[0] = x >= 0 ? (xx / 10000) % 10 + '0' : '-';
  conv[1] = (xx / 1000) % 10 + '0';
  conv[2] = (xx / 100) % 10 + '0';
  conv[3] = '.';
  conv[4] = (xx / 10) % 10 + '0';
  conv[5] = xx % 10 + '0';
  conv[6] = 0;
  return conv;
}

// Convert float to string with 1.234 format
char* ftostr43(const float& x) {
  long xx = x * 1000;
  if (xx >= 0)
    conv[0] = (xx / 1000) % 10 + '0';
  else
    conv[0] = '-';
  xx = abs(xx);
  conv[1] = '.';
  conv[2] = (xx / 100) % 10 + '0';
  conv[3] = (xx / 10) % 10 + '0';
  conv[4] = (xx) % 10 + '0';
  conv[5] = 0;
  return conv;
}

// Convert float to string with 1.23 format
char* ftostr12ns(const float& x) {
  long xx = x * 100;
  xx = abs(xx);
  conv[0] = (xx / 100) % 10 + '0';
  conv[1] = '.';
  conv[2] = (xx / 10) % 10 + '0';
  conv[3] = (xx) % 10 + '0';
  conv[4] = 0;
  return conv;
}

// Convert float to space-padded string with -_23.4_ format
char* ftostr32sp(const float& x) {
  long xx = abs(x * 100);
  uint8_t dig;
  if (x < 0) { // negative val = -_0
    conv[0] = '-';
    dig = (xx / 1000) % 10;
    conv[1] = dig ? '0' + dig : ' ';
  }
  else { // positive val = __0
    dig = (xx / 10000) % 10;
    if (dig) {
      conv[0] = '0' + dig;
      conv[1] = '0' + (xx / 1000) % 10;
    }
    else {
      conv[0] = ' ';
      dig = (xx / 1000) % 10;
      conv[1] = dig ? '0' + dig : ' ';
    }
  }

  conv[2] = '0' + (xx / 100) % 10; // lsd always

  dig = xx % 10;
  if (dig) { // 2 decimal places
    conv[5] = '0' + dig;
    conv[4] = '0' + (xx / 10) % 10;
    conv[3] = '.';
  }
  else { // 1 or 0 decimal place
    dig = (xx / 10) % 10;
    if (dig) {
      conv[4] = '0' + dig;
      conv[3] = '.';
    }
    else {
      conv[3] = conv[4] = ' ';
    }
    conv[5] = ' ';
  }
  conv[6] = '\0';
  return conv;
}

// Convert int to lj string with +123.0 format
char* itostr31(const int& x) {
  conv[0] = x >= 0 ? '+' : '-';
  int xx = abs(x);
  conv[1] = (xx / 100) % 10 + '0';
  conv[2] = (xx / 10) % 10 + '0';
  conv[3] = xx % 10 + '0';
  conv[4] = '.';
  conv[5] = '0';
  conv[6] = 0;
  return conv;
}

// Convert int to rj string with 123 or -12 format
char* itostr3(const int& x) {
  int xx = x;
  if (xx < 0) {
    conv[0] = '-';
    xx = -xx;
  }
  else
    conv[0] = xx >= 100 ? (xx / 100) % 10 + '0' : ' ';

  conv[1] = xx >= 10 ? (xx / 10) % 10 + '0' : ' ';
  conv[2] = xx % 10 + '0';
  conv[3] = 0;
  return conv;
}

// Convert int to lj string with 123 format
char* itostr3left(const int& xx) {
  if (xx >= 100) {
    conv[0] = (xx / 100) % 10 + '0';
    conv[1] = (xx / 10) % 10 + '0';
    conv[2] = xx % 10 + '0';
    conv[3] = 0;
  }
  else if (xx >= 10) {
    conv[0] = (xx / 10) % 10 + '0';
    conv[1] = xx % 10 + '0';
    conv[2] = 0;
  }
  else {
    conv[0] = xx % 10 + '0';
    conv[1] = 0;
  }
  return conv;
}

// Convert int to rj string with 1234 format
char* itostr4(const int& xx) {
  conv[0] = xx >= 1000 ? (xx / 1000) % 10 + '0' : ' ';
  conv[1] = xx >= 100 ? (xx / 100) % 10 + '0' : ' ';
  conv[2] = xx >= 10 ? (xx / 10) % 10 + '0' : ' ';
  conv[3] = xx % 10 + '0';
  conv[4] = 0;
  return conv;
}

// Convert int to rj string with _123, -123, _-12, or __-1 format
char *itostr4sign(const int& x) {
  int xx = abs(x);
  int sign = 0;
  if (xx >= 100) {
    conv[1] = (xx / 100) % 10 + '0';
    conv[2] = (xx / 10) % 10 + '0';
  }
  else if (xx >= 10) {
    conv[0] = ' ';
    sign = 1;
    conv[2] = (xx / 10) % 10 + '0';
  }
  else {
    conv[0] = ' ';
    conv[1] = ' ';
    sign = 2;
  }
  conv[sign] = x < 0 ? '-' : ' ';
  conv[3] = xx % 10 + '0';
  conv[4] = 0;
  return conv;
}

// Convert float to rj string with 12345 format
char* ftostr5(const float& x) {
  long xx = abs(x);
  conv[0] = xx >= 10000 ? (xx / 10000) % 10 + '0' : ' ';
  conv[1] = xx >= 1000 ? (xx / 1000) % 10 + '0' : ' ';
  conv[2] = xx >= 100 ? (xx / 100) % 10 + '0' : ' ';
  conv[3] = xx >= 10 ? (xx / 10) % 10 + '0' : ' ';
  conv[4] = xx % 10 + '0';
  conv[5] = 0;
  return conv;
}

// Convert float to string with +1234.5 format
char* ftostr51(const float& x) {
  long xx = abs(x * 10);
  conv[0] = (x >= 0) ? '+' : '-';
  conv[1] = (xx / 10000) % 10 + '0';
  conv[2] = (xx / 1000) % 10 + '0';
  conv[3] = (xx / 100) % 10 + '0';
  conv[4] = (xx / 10) % 10 + '0';
  conv[5] = '.';
  conv[6] = xx % 10 + '0';
  conv[7] = 0;
  return conv;
}

// Convert float to string with +123.45 format
char* ftostr52(const float& x) {
  conv[0] = (x >= 0) ? '+' : '-';
  long xx = abs(x * 100);
  conv[1] = (xx / 10000) % 10 + '0';
  conv[2] = (xx / 1000) % 10 + '0';
  conv[3] = (xx / 100) % 10 + '0';
  conv[4] = '.';
  conv[5] = (xx / 10) % 10 + '0';
  conv[6] = xx % 10 + '0';
  conv[7] = 0;
  return conv;
}

#endif  //SCREEN
