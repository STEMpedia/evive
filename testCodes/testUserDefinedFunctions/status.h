#ifndef STATUS_H
#define STATUS_H

#include "evive.h"

//No vaible can be assigned any value here as variables are
//actually declared in status.cpp
extern bool _MOTOR1_EN;
extern bool _MOTOR2_EN;
extern bool _STEPPER_EN;
extern bool _SERVO1_EN;
extern bool _SERVO2_EN;
extern int8_t _SLIDESW1_D1_OUTPIN;
extern int8_t _SLIDESW1_D2_OUTPIN;
extern int8_t _SLIDESW1_VAL;
extern int8_t _SLIDESW2_D1_OUTPIN;
extern int8_t _SLIDESW2_D2_OUTPIN;
extern int8_t _SLIDESW2_VAL;
extern int8_t _POT1_OUTPIN;
extern int _POT1_VAL;
extern int8_t _POT2_OUTPIN;
extern int _POT2_VAL;
extern int8_t _TACTILESW1_OUTPIN;
extern int8_t _TACTILESW2_OUTPIN; 

/* extern bool _MOTOR1_EN;
extern bool _MOTOR2_EN;
extern int _SLIDESW1_D1_OUTPIN;
extern int _SLIDESW1_D2_OUTPIN;
extern int _SLIDESW1_VAL;
extern int _SLIDESW2_D1_OUTPIN;
extern int _SLIDESW2_D2_OUTPIN;
extern int _SLIDESW2_VAL;
extern int _POT1_OUTPIN;
extern int _POT1_VAL;
extern int _POT2_OUTPIN;
extern int _POT2_VAL;
extern int _TACTILESW1_OUTPIN;
extern int _TACTILESW2_OUTPIN;
 */
#endif
