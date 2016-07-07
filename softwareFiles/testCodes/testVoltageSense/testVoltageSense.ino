void setup() {
  pinMode(45,OUTPUT);
  pinMode(48,OUTPUT);
  pinMode(49,OUTPUT);
  pinMode(A10,INPUT);
  pinMode(A6,INPUT);
  pinMode(A7,INPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(A7));
  delay(400);
}
