/*
   userDefinedFunctions.cpp

    Created on: Jul 30, 2016
        Author: dhrups
*/
#include "userDefinedFunctions.h"
#include <Servo.h>
#include "motor.h"    //Used 

int sensorPin = A9;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

Servo servo;
Motor left(29, 28, 44);
Motor right(30, 31, 45);
int i;
int meanspeed = 180;
int speedleft = meanspeed;
int speedright = meanspeed;
int factor = 24;
int sense[] = {0, 0, 0, 0, 0, 0, 0};
int servoAngle = 90;
int servoDir = 1;
int error = 0;
int x = 0;

float detect(int ar[], int size);
void scan();
int sign(int n);

/////////////////Setup and loop functions for user defined funcctions/////////////////
// the setup function runs once when you select the user defined function
void setup_user_def_fun_1() {
  // put your setup code here, to run once:
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
}
// the loop function runs continuously when you select the user defined function
void loop_user_def_fun_1() {
  // put your user defined (custom) code here, to run repeatedly:
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}

// the setup function runs once when you select the user defined function
void setup_user_def_fun_2() {
  // put your setup code here, to run once:
  // initialize digital pin 13 as an output.
  pinMode(ledPin, OUTPUT);
}
// the loop function runs continuously when you select the user defined function
void loop_user_def_fun_2() {
  // put your user defined (custom) code here, to run repeatedly:
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  // turn the ledPin on
  digitalWrite(ledPin, HIGH);
  // stop the program for <sensorValue> milliseconds:
  delay(sensorValue);
  // turn the ledPin off:
  digitalWrite(ledPin, LOW);
  // stop the program for for <sensorValue> milliseconds:
  delay(sensorValue);
}

// the setup function runs once when you select the user defined function
void setup_user_def_fun_3() {
  // put your setup code here, to run once:
  lcd.fillRect(0, TOP_MARGIN, LCD_WIDTH,
               LCD_HEIGHT - TOP_MARGIN - BOTTOM_MARGIN, ST7735_BLACK);
  lcd.setCursor(LEFT_MARGIN, TOP_MARGIN + 1 * ROW_HEIGHT);
  lcd.print("Mean Speed: ");
  lcd.setCursor(LEFT_MARGIN + 100, TOP_MARGIN + 2 * ROW_HEIGHT);
  lcd.print(meanspeed);
  lcd.setCursor(LEFT_MARGIN, TOP_MARGIN + 3 * ROW_HEIGHT);
  lcd.print("Proportional Constant: ");
  lcd.setCursor(LEFT_MARGIN + 100, TOP_MARGIN + 4 * ROW_HEIGHT);
  lcd.print(factor);

  Serial.begin(9600);
  delay(500);
}
// the loop function runs continuously when you select the user defined function
void loop_user_def_fun_3() {
  // put your user defined (custom) code here, to run repeatedly:
  factor = analogRead(A10)/ 20;
  meanspeed = analogRead(A9)/4;
  lcd.setTextColor(ST7735_RED, ST7735_BLACK);
  lcd.setCursor(LEFT_MARGIN + 100, TOP_MARGIN + 2 * ROW_HEIGHT);
  lcd.print(meanspeed);
  lcd.print("   ");
  lcd.setCursor(LEFT_MARGIN + 100, TOP_MARGIN + 4 * ROW_HEIGHT);
  lcd.print(factor);
  lcd.print("   ");
}

// the setup function runs once when you select the user defined function
void setup_user_def_fun_4() {
  // put your setup code here, to run once:
  lcd.fillRect(0, TOP_MARGIN, LCD_WIDTH,
               LCD_HEIGHT - TOP_MARGIN - BOTTOM_MARGIN, ST7735_BLACK);
  lcd.setCursor(LEFT_MARGIN, TOP_MARGIN + 1 * ROW_HEIGHT);
  lcd.print("Mean Speed: ");
  lcd.print(meanspeed);
  lcd.setCursor(LEFT_MARGIN, TOP_MARGIN + 2 * ROW_HEIGHT);
  lcd.print("Proportional Constant: ");
  lcd.print(factor);

  Serial.begin(9600);
  for (i = 0; i < 7; i++)
    pinMode(i + 2, INPUT);
  left.stopMotor();
  right.stopMotor();
  //left.startSmoothly(speedleft);
  //right.startSmoothly(speedright);
  //servo.attach(9);
  //servo.write(90);
  delay(500);
}
// the loop function runs continuously when you select the user defined function
void loop_user_def_fun_4() {
  // put your user defined (custom) code here, to run repeatedly:
  
    left.moveMotor(speedleft);
    right.moveMotor(speedright);
  for(i=0;i<6;i++)
  {
    sense[i]=digitalRead(i+2);
    //Serial.print(sense[i]);
   // Serial.print("  ");
  }
  //Serial.println(servoAngle);
  //Serial.println(detect(sense,7));
  x = detect(sense,7);
  Serial.println(x);
  if (x != 0)
  {
  speedleft=meanspeed+x*factor;
  speedright=meanspeed-x*factor;
  //speedright=0;
  }
  delay(10);
}

// the setup function runs once when you select the user defined function
void setup_user_def_fun_5() {
  // put your setup code here, to run once:
}
// the loop function runs continuously when you select the user defined function
void loop_user_def_fun_5() {
  // put your user defined (custom) code here, to run repeatedly:
}

//Function to add the selected user defined function in loop
void add_user_def_fun(uint8_t funNum) {
  if (funNum == 1) {
    actionRemove(loop_user_def_fun_2);
    actionRemove(loop_user_def_fun_3);
    actionRemove(loop_user_def_fun_4);
    actionRemove(loop_user_def_fun_5);
    setup_user_def_fun_1();
    actionAdd(loop_user_def_fun_1, 1);
  }
  else if (funNum == 2) {
    actionRemove(loop_user_def_fun_1);
    actionRemove(loop_user_def_fun_3);
    actionRemove(loop_user_def_fun_4);
    actionRemove(loop_user_def_fun_5);
    setup_user_def_fun_2();
    actionAdd(loop_user_def_fun_2, 1);
  }
  else if (funNum == 3) {
    actionRemove(loop_user_def_fun_1);
    actionRemove(loop_user_def_fun_2);
    actionRemove(loop_user_def_fun_4);
    actionRemove(loop_user_def_fun_5);
    setup_user_def_fun_3();
    actionAdd(loop_user_def_fun_3, 1);
  }
  else if (funNum == 4) {
    actionRemove(loop_user_def_fun_1);
    actionRemove(loop_user_def_fun_2);
    actionRemove(loop_user_def_fun_3);
    actionRemove(loop_user_def_fun_5);
    left.stopMotor();
    right.stopMotor();
    setup_user_def_fun_4();
    actionAdd(loop_user_def_fun_4, 1);
  }
  else if (funNum == 5) {
    actionRemove(loop_user_def_fun_1);
    actionRemove(loop_user_def_fun_2);
    actionRemove(loop_user_def_fun_3);
    actionRemove(loop_user_def_fun_4);
    setup_user_def_fun_5();
    actionAdd(loop_user_def_fun_5, 1);
  }
}

///////////////////// Write other sub functions below this ////////////////////

int sign(int n)
{
  if(n>0)
    return 1;
  else if(n<0)
    return -1;
  else 
    return 0;      
}

void scan()
{
  servo.write(60);
  delay(100);
  servo.write(120);
  delay(100);
}


float detect(int ar[],int size){
  int count=0;
  float pin=0;
  for(i=0;i<size-1;i++){
    if(ar[i]==0)
      { pin=i;
        count++;
      }
  } 
  //Serial.println(pin);
  //Serial.println(pin);  
  if(count==2)
    return (pin-0.5-3);   
  
  else if(count==1)
  {
    if (pin==0) 
    return -5;
    
    else if (pin == 6)
    return 5;
    else
    return (pin-3);
  }
  else if (count==0)
  return 0;
  else
  return 0;  
    
}

