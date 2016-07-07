void setup() {
  // put your setup code here, to run once:
pinMode(13, OUTPUT);
}
unsigned long currTime, prevTime;
bool state=1;
void loop() {
  if(millis()%10 == 1 )
  {state = !state;
  digitalWrite(13,state);
  }
}
