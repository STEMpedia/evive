#include "navkey.h"

volatile bool menuPress = 0;	//If ever put into an interrupt, make these variables volatile
uint8_t menuMove = 0;
unsigned long lastKeyMoveTime = 0;

void navKeyUpdate(){
	unsigned long thisTime=millis();
	if ((thisTime-lastKeyMoveTime)<MIN_TIME2){ //Too less time has passed
		menuPress=0;
		menuMove=0;
		return;
	}
	else{ //Enough time has passed
		if(digitalRead(NAVKEY_PRESS)){ //Press
			lastKeyMoveTime=thisTime;
			menuPress = 1;
			Serial.println("Navkey Press");
			menuMove=0;
			return;
		}
		else{
			menuPress = 0;
			uint16_t navKeyMove=analogRead(NAVKEY_MOVE);
			if (navKeyMove<20){ //No press, no move
				menuMove=0;
			}
			else{ //No press, yes move
				Serial.print("value of navKeyMove is: ");
				Serial.println(navKeyMove);
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

//Use/Attach Center Press key of Navigation Key (Joystick) as Interrupt
void navKeyAttachInterruptMenuPress(){
		attachInterrupt(digitalPinToInterrupt(NAVKEY_PRESS), navKeyInterruptCenterPress, RISING);
}

//Dettach Center Press key of Navigation Key (Joystick) as Interrupt
void navKeyDettachInterruptMenuPress(){
	detachInterrupt(digitalPinToInterrupt(NAVKEY_PRESS));
}

//Comment following function if ISR function is required
//and paste it at required destination (even outside this library)
// void navKeyInterruptCenterPress(){
	// put your ISR (intrrupt) code here.
// }