# include <Servo.h>
Servo s1;
#define Motor1Pin 3
int power = 75;

int value = 0;
int encoder_to_output_gear_ratio = 9;

volatile unsigned long timevar = 0;
volatile unsigned int RPM = 0;
volatile unsigned int looptime = 0;
#define encoder0Pin  2


volatile unsigned long encoder0Pos = 0;

void setup() {
  
  // put your setup code here, to run once:
  pinMode(Motor1Pin, OUTPUT);
  pinMode(encoder0Pin, INPUT); 
  digitalWrite(encoder0Pin, HIGH);       // turn on pullup resistor
  attachInterrupt(0, doEncoder, RISING);  // encoder pin on interrupt 0 - pin 2
  Serial.begin (9600);
  Serial.println("Encoder initialised -> interrupt attached"); 
  
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
//power = 63;
delay(200);
if(encoder0Pos >0)
     {
      looptime = millis()-timevar;
      RPM = encoder0Pos*5000/(encoder_to_output_gear_ratio*looptime);
      timevar = millis();
      Serial.print("RPM - ");
      Serial.print(RPM); 
      Serial.print("      loop time - ");
      Serial.print(looptime);
      Serial.print("      encoder0Pos - ");
      Serial.println(encoder0Pos); 
      encoder0Pos = 0;
     }
     

power = power+1;
if(power==80)
{power = 60;}
}

void doEncoder() {
  encoder0Pos++;  
}
