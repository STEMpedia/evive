void setup()
{
    Serial.begin(9600);
    Serial3.begin(9600);
}
void loop()
{
    if (Serial3.available()){
      while (Serial3.available()) {
        Serial.write(Serial3.read());
      }
    }
    if (Serial.available()){
      delay(1000);
      String command="";
      while (Serial.available()) {
        command+=(char)Serial.read();
      }
      Serial3.println(command);
  }
}

