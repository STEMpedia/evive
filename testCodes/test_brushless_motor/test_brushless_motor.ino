#include <Servo.h>
Servo s1;
#define Motor1Pin 3
int power = 95;
int count = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(Motor1Pin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Get ready");
  
  delay(3000);
s1.attach(3);
delay(1);
//s1.write(0);
Serial.println("Start ESC");
delay(3000);
 s1.write(1023);
  Serial.println("Full throttle");
  Serial.println("Waiting 2.5  seconds...");
  delay(2500);
  s1.write(0);
//  Serial.println("Zero throttle");
//  delay(5000);
  
}

void loop() {

s1.write(power);
Serial.println(power);
delay(20);
count = count +1;
if(count%200 == 0)
  power = power+1;
if(power==110)
{power = 95;}
}
