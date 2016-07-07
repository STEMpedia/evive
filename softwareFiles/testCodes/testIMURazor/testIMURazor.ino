#define BUFF_SIZE 40
char buffer[BUFF_SIZE];

void setup(){
Serial.begin(57600);
Serial3.begin(57600);
Serial.println("Starting Communication with Razor IMU");
}

void loop() {

int i = 0;
while(Serial3.available()) {
buffer[i++] = Serial3.read();
if(i == BUFF_SIZE) break;
}

for(int j = 0; j < i; j++) {
Serial.print(buffer[j]);
}

}
