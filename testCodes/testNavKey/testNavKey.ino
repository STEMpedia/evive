void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(A11,INPUT);
pinMode(19,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int x=analogRead(11);
if (digitalRead(19) ==HIGH)
{
  Serial.println("Pressed");
}

Serial.println(x);
delay(5);
}
