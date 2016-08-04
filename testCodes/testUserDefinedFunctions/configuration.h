#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#define SENSING
#define SCREEN
//#define SDSUPPORT

#define BAUDRATE 115200

//////////macros////////////////
// Macros to support option testing
#define _CAT(a, ...) a ## __VA_ARGS__
#define SWITCH_ENABLED_0 0
#define SWITCH_ENABLED_1 1
#define SWITCH_ENABLED_  1
#define ENABLED(b) _CAT(SWITCH_ENABLED_, b)
#define DISABLED(b) (!_CAT(SWITCH_ENABLED_, b))

//Min time between simultaneous process
#define MIN_TIME1 100
#define MIN_TIME2 200
#define MIN_TIME3 300
#define MIN_TIME5 500

// Macros for bit masks
#define BIT(b) (1<<(b))
#define TEST(n,b) (((n)&BIT(b))!=0)
#define SET_BIT(n,b,value) (n) ^= ((-value)^(n)) & (BIT(b))

// Macros for maths shortcuts
#define RADIANS(d) ((d)*M_PI/180.0)
#define DEGREES(r) ((r)*180.0/M_PI)

#define COUNT(a) (sizeof(a)/sizeof(*a))

#define ROW_HEIGHT       10
#define CHAR_HEIGHT     8
#define CHAR_WIDTH      6
#define LEFT_MARGIN     2
#define RIGHT_MARGIN    2
#define TOP_MARGIN      14
#define BOTTOM_MARGIN     2
#define LCD_HEIGHT      128
#define LCD_WIDTH       160
#define LCD_WIDTH_BY_2  80
//#define LCD_STR_UPLEVEL   '^'
#define LCD_STR_ARROW_RIGHT ">"
#define LCD_STR_UPLEVEL     "\x03"
#define BATT_X        140
#define BATT_Y        4
#define BATT_WIDTH      17
#define BATT_HEIGHT     7
#define BATT_COLOR      ST7735_CYAN

#endif

