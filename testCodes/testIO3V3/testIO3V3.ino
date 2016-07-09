void setup() {
  // put your setup code here, to run once:
pinMode(36, OUTPUT);
pinMode(37, INPUT);
pinMode(33, OUTPUT);    //DIR
Serial.begin(9600);
Serial.println("start");
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(33, HIGH);
digitalWrite(36,LOW);
delay(2000);
digitalWrite(33, LOW);
Serial.println(digitalRead(37));
Serial.println(digitalRead(36));
digitalWrite(33, HIGH);
digitalWrite(36,LOW);
Serial.println(digitalRead(37));
Serial.println(digitalRead(36));
delay(2000);
}
