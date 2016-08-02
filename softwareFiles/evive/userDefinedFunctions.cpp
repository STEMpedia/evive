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
  // put your setup code here, to run once:
}
// the loop function runs continuously when you select the user defined function
void loop_user_def_fun_1(){
	// put your user defined (custom) code here, to run repeatedly:
	Serial.println("Hurray! User Def Fun 1 Works");
}

// the setup function runs once when you select the user defined function
void setup_user_def_fun_2(){
  // put your setup code here, to run once:
}
// the loop function runs continuously when you select the user defined function
void loop_user_def_fun_2(){
	// put your user defined (custom) code here, to run repeatedly:
	Serial.println("Hurray! User Def Fun 2 Works");
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
