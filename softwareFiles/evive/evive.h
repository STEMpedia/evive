#ifndef EVIVE_H
#define EVIVE_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <inttypes.h>

#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "fastio.h"

// Added to fix Arduino 1.0 compile issues 12/11/11 - TVHeadedRobots
//#if defined(ARDUINO) && ARDUINO < 100
//#include <WProgram.h>
//#else
//#include <Arduino.h>
//#endif

#include <Arduino.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ST7735.h"
#include <SPI.h>

#include "configuration.h"
#include "evivePins.h"
#include "language.h"
#include "language_en.h"
#include "bitmaps.h"
#include "screen.h"
#include "status.h"
#include "navkey.h"
#include "button.h"
#include "potentiometer.h"
#include "slideSwitch.h"
#include "setPinMode.h"
#include "motor.h"
#include "servoControl.h"
#include "stepper.h"
#include "action.h"
#include "adc_ade7912.h"
#include "userDefinedFunctions.h"
//#include "screenImplementation.h"

#endif
