/*
 * userDefinedFunctions.cpp
 *
 *  Created on: Jul 30, 2016
 *      Author: dhrups
 */
 #include "userDefinedFunctions.h"

/////////////////Setup and loop functions for user defined funcctions/////////////////

// the setup function runs once when you select the user defined function
void setup_user_def_fun_1(){
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
}
// the loop function runs continuously when you select the user defined function
void loop_user_def_fun_1(){
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}

// the setup function runs once when you select the user defined function
void setup_user_def_fun_2(){
  // put your setup code here, to run once:
}
// the loop function runs continuously when you select the user defined function
void loop_user_def_fun_2(){
	// put your user defined (custom) code here, to run repeatedly:
}

// the setup function runs once when you select the user defined function
void setup_user_def_fun_3(){
  // put your setup code here, to run once:
}
// the loop function runs continuously when you select the user defined function
void loop_user_def_fun_3(){
	// put your user defined (custom) code here, to run repeatedly:
}

// the setup function runs once when you select the user defined function
void setup_user_def_fun_4(){
  // put your setup code here, to run once:
}
// the loop function runs continuously when you select the user defined function
void loop_user_def_fun_4(){
	// put your user defined (custom) code here, to run repeatedly:
}

// the setup function runs once when you select the user defined function
void setup_user_def_fun_5(){
  // put your setup code here, to run once:
}
// the loop function runs continuously when you select the user defined function
void loop_user_def_fun_5(){
	// put your user defined (custom) code here, to run repeatedly:
}

void add_user_def_fun(uint8_t funNum){
  if(funNum==1){
    setup_user_def_fun_1();
    actionAdd(loop_user_def_fun_1, 1);
  }
  else if(funNum==2){
    setup_user_def_fun_2();
    actionAdd(loop_user_def_fun_2, 1);
  }
  else if(funNum==3){
    setup_user_def_fun_3();
    actionAdd(loop_user_def_fun_3, 1);
  }
  else if(funNum==4){
    setup_user_def_fun_4();
    actionAdd(loop_user_def_fun_4, 1);
  }
  else if(funNum==5){
    setup_user_def_fun_5();
    actionAdd(loop_user_def_fun_5, 1); 
  }
}

///////////////////// Write other sub functions below this ////////////////////
