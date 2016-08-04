/*
 * userDefinedFunctions.cpp
 *
 *  Created on: Jul 30, 2016
 *      Author: dhrups
 */
 #ifndef USER_DEFINED_FUNCTION_H
#define USER_DEFINED_FUNCTION_H

//IMPORTANT: uncomment the desired user defined functions and give desired name
#define USER_DEFINED_FUNCTION_1 	"Eg->Basics: Blink"
#define USER_DEFINED_FUNCTION_2 	"Eg->Analog: AnalogInput"
#define USER_DEFINED_FUNCTION_3 	"Line Follower Calibrate"
#define USER_DEFINED_FUNCTION_4 	"Line Follower"
// #define USER_DEFINED_FUNCTION_5 	"User Def fun name 5"


#include "evive.h"

void loop_user_def_fun_1();
void loop_user_def_fun_2();
void loop_user_def_fun_3();
void loop_user_def_fun_4();
void loop_user_def_fun_5();

void add_user_def_fun(uint8_t);



#endif
