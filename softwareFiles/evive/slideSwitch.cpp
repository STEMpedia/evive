/*
 * slideSwitch.cpp
 *
 *  Created on: May 23, 2016
 *      Author: dhrups
 */


#include "Button.h"

/*----------------------------------------------------------------------*
 * SlideSwitch(pin1, pin2, puEnable, invert,) instantiates a SlideSwitct object.  *
 * pinX      Is the Arduino pin the button is connected to.              *
 * puEnable Enables the AVR internal pullup resistor if != 0 (can also  *
 *          use true or false).                                         *
 * invert   If invert == 0, interprets a high state as pressed, low as  *
 *          released. If invert != 0, interprets a high state as        *
 *          released, low as pressed  (can also use true or false).     *

 * (Note that invert cannot be implied from puEnable since an external  *
 *  pullup could be used.)                                              *
 *----------------------------------------------------------------------*/
SlideSwitch::SlideSwitch(uint8_t pin1, uint8_t pin2, uint8_t puEnable, uint8_t invert)
{
    _pin1 = pin1;
    _pin2 = pin2;
    _puEnable = puEnable;
    _invert = invert;

    pinMode(_pin1, INPUT);
    pinMode(_pin2, INPUT);
    if (_puEnable != 0){
        digitalWrite(_pin1, HIGH);       //enable pullup resistor
        digitalWrite(_pin2, HIGH);       //enable pullup resistor
    }
    _state1 = digitalRead(_pin1);
    _state2 = digitalRead(_pin2);
    if (_invert != 0) {
    	_state1 = !_state1;
    	_state2 = !_state2;
    }
}

SlideSwitch::SlideSwitch(uint8_t pin1, uint8_t pin2){
    _pin1 = pin1;
    _pin2 = pin2;
    _puEnable = 0;
    _invert = 0;

    pinMode(_pin1, INPUT);
    pinMode(_pin2, INPUT);
    _state1 = digitalRead(_pin1);
    _state2 = digitalRead(_pin2);
}

SlideSwitch::SlideSwitch(){
}

/*----------------------------------------------------------------------*
 * readPin1() returns the state of the SlideSwitch Pin1, 1==pressed, 0==released, *
 *----------------------------------------------------------------------*/
bool SlideSwitch::readPin1(void)
{
    _state1 = digitalRead(_pin1);
    if (_invert != 0) {
    	_state1 = !_state1;
    }
    return _state1;
}

/*----------------------------------------------------------------------*
 * readPin2() returns the state of the SlideSwitch Pin2, 1==pressed, 0==released, *
 *----------------------------------------------------------------------*/
bool SlideSwitch::readPin2(void)
{
    _state2 = digitalRead(_pin2);
    if (_invert != 0) {
    	_state2 = !_state2;
    }
    return _state2;
}

SlideSwitch slideSw1(SLIDESW1_D1, SLIDESW1_D2), slideSw2(SLIDESW2_D1, SLIDESW2_D2);
