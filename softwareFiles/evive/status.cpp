#include "status.h"

/* bool _MOTOR1_EN = 0;
bool _MOTOR2_EN = 0;
int _SLIDESW1_D1_OUTPIN = -1;
int _SLIDESW1_D2_OUTPIN = -1;
int _SLIDESW1_VAL = -1;
int _SLIDESW2_D1_OUTPIN = -1;
int _SLIDESW2_D2_OUTPIN = -1;
int _SLIDESW2_VAL = -1;
int _POT1_OUTPIN = -1;
int _POT1_VAL = -1;
int _POT2_OUTPIN = -1;
int _POT2_VAL = -1;
int _TACTILESW1_OUTPIN = -1;
int _TACTILESW2_OUTPIN = -1; */

bool _MOTOR1_EN = 0;
bool _MOTOR2_EN = 0;
bool _STEPPER_EN = 0;
bool _SERVO1_EN = 0;
bool _SERVO2_EN = 0;
int8_t _SLIDESW1_D1_OUTPIN = -1;
int8_t _SLIDESW1_D2_OUTPIN = -1;
int8_t _SLIDESW1_VAL = -1;			// 0/1/2
int8_t _SLIDESW2_D1_OUTPIN = -1;
int8_t _SLIDESW2_D2_OUTPIN = -1;
int8_t _SLIDESW2_VAL = -1;			// 0/1/2
int8_t _POT1_OUTPIN = -1;
int _POT1_VAL = -1;					// 0 to 1023
int8_t _POT2_OUTPIN = -1;
int _POT2_VAL = -1;					// 0 to 1023
int8_t _TACTILESW1_OUTPIN = -1;
int8_t _TACTILESW1_STATE = -1;		// 0 or 1
int8_t _TACTILESW2_OUTPIN = -1;
int8_t _TACTILESW2_STATE = -1;		// 0 or 1
volatile bool DAC_ON_OFF = 0;
volatile bool OSCILLOSCOPE_ON_OFF = 0;
