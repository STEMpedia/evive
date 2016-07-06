#include "setPinMode.h"

void setPinModeDefault(){	
	pinMode(SLIDESW1_D1,INPUT);
	pinMode(SLIDESW1_D2,INPUT);
	pinMode(SLIDESW2_D1,INPUT);
	pinMode(SLIDESW2_D2,INPUT);
	pinMode(POT1,INPUT);
	pinMode(POT2,INPUT);
	pinMode(TACTILESW1,INPUT);
	pinMode(TACTILESW2,INPUT);
	pinMode(LED13,OUTPUT);
	pinMode(LED13,HIGH);
	pinMode(NAVKEY_PRESS,INPUT);
	pinMode(NAVKEY_MOVE,INPUT);
}