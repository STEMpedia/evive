void setup(){
  pinMode(A9,INPUT);
  pinMode(A10,INPUT);
  pinMode(13,OUTPUT);
  pinMode(47,OUTPUT);
}
void loop(){
  int x=analogRead(A9)/4;
  int y=analogRead(A10)/4;
  //analogWrite(13,x);
  analogWrite(13,y);
}
