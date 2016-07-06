/*----------------------------------------------------------------------*
 * slideSwitch.cpp
 *
 *  Created on: May 23, 2016
 *      Author: dhrups
 *----------------------------------------------------------------------*/
#ifndef SLIDE_SWITCH_H
#define SLIDE_SWITCH_H

#include "evive.h"

class SlideSwitch
{
    public:
        SlideSwitch();
        SlideSwitch(uint8_t pin1, uint8_t _pin2);
		SlideSwitch(uint8_t pin1, uint8_t _pin2,  uint8_t puEnable, uint8_t invert);
		bool readPin1();
		bool readPin2();

    private:
        uint8_t _pin1;           //arduino pin number
        uint8_t _pin2;           //arduino pin number
        bool _puEnable;      //internal pullup resistor enabled
        bool _invert;        //if 0, interpret high state as pressed, else interpret low state as pressed
        bool _state1;         //current button state
        bool _state2;         //current button state
//        uint8_t _lastState;     //previous button state
//        uint8_t _changed;       //state changed since last read
//        uint32_t _time;         //time of current state (all times are in ms)
//        uint32_t _lastChange;   //time of last state change
//        uint32_t _dbTime;       //debounce time
};

extern SlideSwitch slideSw1, slideSw2;
#endif
