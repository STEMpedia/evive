/*library tested 30 NOVEMBER
  Made by Deep Goel and Kartik Gupta
*/

#include "motor.h"

Motor::Motor()									//constructor
{	
	attachMotor(-1,-1,-1);
}

Motor::Motor(int Dir1, int Dir2, int Pwm )		// parametrised constructor
{	
	attachMotor(Dir1,Dir2,Pwm);
}

void Motor::attachMotor(int Dir1,int Dir2,int Pwm)
{
	pwm_pin= Pwm;
	dir1_pin		= Dir1;
	dir2_pin		= Dir2;
	if(dir1!=-1 && dir2!=-1 && pwm_pin!=-1)
	{	
		pinMode(pwm_pin,OUTPUT);
		pinMode(dir1_pin,OUTPUT);
		pinMode(dir2_pin,OUTPUT);
	}
	pwm			= 0;
	speed		= 0;
	mean_speed	= 255;
	//lockMotor();	//Lock the Motor initially
	damping=10;
	}


void Motor::moveMotor(int Pwm)			//+ve for CW and -ve for CCW.
{
	
	if(Pwm>=0)
	{	
		digitalWrite(dir1_pin,HIGH);
		digitalWrite(dir2_pin,LOW);
	}
	else
	{	
		digitalWrite(dir1_pin,LOW);
		digitalWrite(dir2_pin,HIGH);
	}
	changePWM(Pwm);
//	Serial.println("PWM=");
//	Serial.print(Pwm);
}

void Motor::moveMotor(int Dir1,int Dir2,int Pwm)
{
	dir1 = Dir1;
	dir2 = Dir2;
	digitalWrite(dir1_pin,Dir1);
	digitalWrite(dir2_pin,Dir2);
//	if(Dir1==1 && Dir2==0)
//		moveMotor(Pwm);
//	if(Dir1==0 && Dir2==1)
//		moveMotor(-Pwm);
	changePWM(Pwm);

}

void Motor::stopMotor() 				//By default stop motor will lock motor
{	
	lockMotor();
}

void Motor::lockMotor()
{
	digitalWrite(dir1_pin,HIGH);			//case of motor lock
	digitalWrite(dir2_pin,HIGH);
	analogWrite(pwm_pin,255);
	pwm=0;	
}

void Motor::freeMotor()
{
	digitalWrite(dir1_pin,LOW);			//case of motor free
	digitalWrite(dir2_pin,LOW);
	analogWrite(pwm_pin,0);
	pwm=0;
}
		
void Motor::setMeanSpeed(int Speed)			//Sets the meanspeed with which motor moves when speed=100%	
{	
	mean_speed=Speed;
}

void  Motor::setMotorSpeed(int Speed)				//+ve for CW and -ve for CCW. Speed in percentage of meanspeed
{	
	if(Speed>100)
		Speed=100;
	if(Speed<-100)
		Speed=-100;
	speed=Speed;
	
	moveMotor(Speed*mean_speed/100);
}

void  Motor::setMotorSpeed(int Dir1,int Dir2,int Speed)
{	
	if(Speed>100)
		Speed=100;
	if(Speed<-100)
		Speed=-100;
	speed=Speed;
	moveMotor(Dir1,Dir2,Speed*mean_speed/100);
}

void Motor::changePWM(int Pwm)					//Just to change the PWM
{
	pwm = Pwm>255 ? 255 : (Pwm < -255 ? -255 :Pwm);
	analogWrite(pwm_pin,abs(pwm));
}

void Motor::changeSpeed(int Speed)				//Just to change the speed (In percentage)
{	
	if(Speed>100)
		Speed=100;
	if(Speed<-100)
		Speed=-100;
	speed=Speed;
	changePWM(Speed*mean_speed/100);
}

int Motor::getDirection()
{
	dir1=digitalRead(dir1_pin);
	dir2=digitalRead(dir2_pin);
	if (dir1==dir2)
		return 0;
	else 
		return((dir1>dir2)?1:-1);
}

int Motor::isFree()
{
	return (getDirection()==0 && dir1==0);
}

int Motor::isLocked()
{
	return (getDirection()==0 && dir1==1);
}

int Motor::getSpeed()
{
	return(pwm*100/mean_speed);
}

int Motor::getPWM()
{
  return pwm;
}

 void Motor::startSmoothly(int Speed)
 {
    if(Speed>100)
		Speed=100;
	if(Speed<-100)
		Speed=-100;
	int i;
	if(Speed>=0)
	{	
		digitalWrite(dir1_pin,HIGH);
		digitalWrite(dir2_pin,LOW);
	}
	else
	{	
		digitalWrite(dir1_pin,LOW);
		digitalWrite(dir2_pin,HIGH);
	}
	for(i=0;i<=Speed;i=i+COUNT_CONST)
	{
		changeSpeed(i);
		delay(COUNT_CONST*damping);
		speed=i;
		pwm=speed*mean_speed/100;
	}
 }
 void Motor::stopSmoothly()
 {  int i;
	speed=getSpeed();
	for(i=speed;i>=0;i=i-COUNT_CONST)
	{
		changeSpeed(i);
		delay(COUNT_CONST*damping);
		speed=i;
		pwm=speed*mean_speed/100;
	}
	lockMotor();
 }

 Motor motor1, motor2;

 void controlMotor()
 {	Serial.println("MotorCtrl");
 	 if(_MOTOR1_EN)
 	 {	motor1.moveMotor(slideSw1.readPin1(),slideSw1.readPin2(),pot1.getValue()/4);
 	 }
 	 if(_MOTOR2_EN)
 	 {	motor2.moveMotor(slideSw2.readPin1(),slideSw2.readPin2(),pot2.getValue()/4);
 	 }
 }

 void addMotor1(){
	_MOTOR1_EN = 1;
	_SLIDESW1_D1_OUTPIN = MOTOR1_D1;
	_SLIDESW1_D2_OUTPIN = MOTOR1_D2;
	_POT1_OUTPIN = MOTOR1_EN;
	pinMode(SLIDESW1_D1,INPUT);
	pinMode(SLIDESW1_D2,INPUT);
	motor1.attachMotor(MOTOR1_D1, MOTOR1_D2, MOTOR1_EN);
	actionAdd(controlMotor, 1);
 }

 void addMotor2(){
	_MOTOR2_EN = 1;
	_SLIDESW2_D1_OUTPIN = MOTOR2_D1;
	_SLIDESW2_D2_OUTPIN = MOTOR2_D2;
	_POT2_OUTPIN = MOTOR2_EN;
	pinMode(SLIDESW2_D1,INPUT);
	pinMode(SLIDESW2_D2,INPUT);
 	motor2.attachMotor(MOTOR2_D1, MOTOR2_D2, MOTOR2_EN);
 	actionAdd(controlMotor, 1);
 }
 void addMotor12(){
	 addMotor1();
	 addMotor2();
 }
