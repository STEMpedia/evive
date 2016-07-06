#ifndef ACTION_H
#define ACTION_H
#include "evive.h"

typedef void (*actionFunc)();	// Function pointer to action functions.
extern actionFunc actionFuncList[20];
extern uint8_t actionFuncListNum;

void actionAdd(actionFunc);
void actionAdd(actionFunc, bool);
void actionRemove(actionFunc);
void actionRemove(uint8_t);
void action();

#endif
