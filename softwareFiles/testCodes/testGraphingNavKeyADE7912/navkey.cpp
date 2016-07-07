#include "navkey.h"
//#include <stdint.h>


bool menuPress = 0;	//If ever put into an interrupt, make these variables volatile
uint8_t menuMove = 0;
unsigned long lastKeyMoveTime = 0;

void navKeyUpdate(){
	unsigned long thisTime=millis();
	if ((thisTime-lastKeyMoveTime)<MIN_KEY_PRESS_TIME){ //Too less time has passed
		menuPress=0;
		menuMove=0;
		return;
	}
	else{ //Enough time has passed
		if(digitalRead(NAVKEY_PRESS)){ //Press
			lastKeyMoveTime=thisTime;
			menuPress = 1;
			Serial.println("Navkey Press");
			return;
		}
		else{
			menuPress = 0;
			uint16_t navKeyMove=analogRead(NAVKEY_MOVE);
			if (navKeyMove<20){ //No press, no move
				menuMove=0;
			}
			else{ //No press, yes move
				//Serial.print("value of navKeyMove is: ");
				//Serial.println(navKeyMove);
				if ((navKeyMove>NAVKEYMOVE_UP_LOW)&&(navKeyMove<NAVKEYMOVE_UP_HIGH)){ //Up
					menuMove=1;
					lastKeyMoveTime=thisTime;
				}
				else if ((navKeyMove>NAVKEYMOVE_RIGHT_LOW)&&(navKeyMove<NAVKEYMOVE_RIGHT_HIGH)){ //Right
					menuMove=2;
					lastKeyMoveTime=thisTime;
				}
				else if ((navKeyMove>NAVKEYMOVE_DOWN_LOW)&&(navKeyMove<NAVKEYMOVE_DOWN_HIGH)){ //Down
					menuMove=3;
					lastKeyMoveTime=thisTime;					
				}
				else if ((navKeyMove>NAVKEYMOVE_LEFT_LOW)&&(navKeyMove<NAVKEYMOVE_LEFT_HIGH)){ //Left
					menuMove=4;
					lastKeyMoveTime=thisTime;
				}

			}
		}
	}
}
