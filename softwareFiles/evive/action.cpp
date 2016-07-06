/*
 * action.cpp
 *
 *  Created on: Apr 16, 2016
 *      Author: dhrups
 */
#include "action.h"

actionFunc actionFuncList[20] = {};			//maximum 20 functions
uint8_t actionFuncListNum	 = 0;			//must be greater than or equals to 0

void actionAdd(actionFunc addFun){
	actionFuncList[actionFuncListNum++] = addFun	;
	Serial.print("funList: ");
	Serial.println(actionFuncListNum);
//	Serial.print("funAdd: ");
//	Serial.println(addFun);
	return;
}

//for avoiding multiple includes of same function for multiple times in one loop
//if flag = 1, checks for repetition
void actionAdd(actionFunc addFun, bool flag){
	if (flag)
	{
		for (uint8_t i = 0; i<actionFuncListNum;i++	)
		{    if (actionFuncList[i] == addFun)	return;
		}
	}
	actionFuncList[actionFuncListNum++] = addFun	;
	Serial.print("funList: ");
	Serial.println(actionFuncListNum);
	return;
}

void actionRemove(actionFunc removeFun){
	for (uint8_t i = 0; i < actionFuncListNum; i++)
	{	if (actionFuncList[i] == removeFun){
			for (; i < actionFuncListNum-1; i++)
				actionFuncList[i] = actionFuncList[i+1];
			actionFuncListNum--;
			return;						//remove single entry of same function
		}
	}
}

void actionRemove(uint8_t removeFunNum){
	for (uint8_t i = removeFunNum; i < actionFuncListNum-1; i++)
		actionFuncList[i] = actionFuncList[i+1];
	actionFuncListNum--;
}
void action(){
//	Serial.println(actionFuncListNum);
	for (uint8_t i = 0; i<actionFuncListNum;i++	)
	{    (*actionFuncList[i])();
	}
}
