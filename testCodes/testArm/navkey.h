#ifndef NAVKEY_H
#define NAVKEY_H

//set range after min/max for all cases like battery powered, USB, VIN
#define NAVKEYMOVE_UP_LOW       190
#define NAVKEYMOVE_UP_HIGH      230
#define NAVKEYMOVE_RIGHT_LOW    385
#define NAVKEYMOVE_RIGHT_HIGH   425
#define NAVKEYMOVE_DOWN_LOW     585
#define NAVKEYMOVE_DOWN_HIGH    625
#define NAVKEYMOVE_LEFT_LOW     820
#define NAVKEYMOVE_LEFT_HIGH    860

//#include "evive.h"
#include <Arduino.h>
#define NAVKEY_PRESS						19
#define NAVKEY_MOVE							A11
#define MIN_KEY_PRESS_TIME			200
extern bool menuPress;					//If ever put into an interrupt, make these variables volatile
extern uint8_t menuMove;				// 1-2-3-4 in clockwise direction
extern unsigned long lastKeyMoveTime;

void navKeyUpdate();

#endif
