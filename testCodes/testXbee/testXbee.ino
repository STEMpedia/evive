void setup() {
  // put your setup code here, to run once:
Serial3.begin(9600);
Serial.begin(9600);
    Serial3.println("poke me");
    Serial.println("poke me");
}

void loop() {
  // put your main code here, to run repeatedly:
  if( Serial3.available())
  {
    Serial3.println("udo responded!!!");
    delay(5);
  }

}
