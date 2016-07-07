/*

Gamepad Shield Example

This example shows an application on 1Sheeld's gamepad shield.

By using this example, you can control a 2-wheel car (like the
one in our warrior kit) using the gamepad in our app along with
Seeedstudio's motor shield.

PS: Arduino's motor shield has different configuration.

OPTIONAL:
To reduce the library compiled size and limit its memory usage, you
can specify which shields you want to include in your sketch by
defining CUSTOM_SETTINGS and the shields respective INCLUDE_ define. 

*/

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_SHIELD

/* Include 1Sheeld library. */
#include <OneSheeld.h>
// This sketch code is based on the RPLIDAR driver library provided by RoboPeak
//#include <RPLidar.h>
#include <Wire.h>

// You need to create an driver instance 
//RPLidar lidar;

// The PWM pin for control the speed of RPLIDAR's motor.
// This pin should connected with the RPLIDAR's MOTOCTRL signal 

//#define RPLIDAR_MOTOR 11 

// Register names according to the datasheet.
// According to the InvenSense document
// "MPU-9150 Register Map and Descriptions Revision 4.0",

#define MPU9150_SELF_TEST_X        0x0D   // R/W
#define MPU9150_SELF_TEST_Y        0x0E   // R/W
#define MPU9150_SELF_TEST_X        0x0F   // R/W
#define MPU9150_SELF_TEST_A        0x10   // R/W
#define MPU9150_SMPLRT_DIV         0x19   // R/W
#define MPU9150_CONFIG             0x1A   // R/W
#define MPU9150_GYRO_CONFIG        0x1B   // R/W
#define MPU9150_ACCEL_CONFIG       0x1C   // R/W
#define MPU9150_FF_THR             0x1D   // R/W
#define MPU9150_FF_DUR             0x1E   // R/W
#define MPU9150_MOT_THR            0x1F   // R/W
#define MPU9150_MOT_DUR            0x20   // R/W
#define MPU9150_ZRMOT_THR          0x21   // R/W
#define MPU9150_ZRMOT_DUR          0x22   // R/W
#define MPU9150_FIFO_EN            0x23   // R/W
#define MPU9150_I2C_MST_CTRL       0x24   // R/W
#define MPU9150_I2C_SLV0_ADDR      0x25   // R/W
#define MPU9150_I2C_SLV0_REG       0x26   // R/W
#define MPU9150_I2C_SLV0_CTRL      0x27   // R/W
#define MPU9150_I2C_SLV1_ADDR      0x28   // R/W
#define MPU9150_I2C_SLV1_REG       0x29   // R/W
#define MPU9150_I2C_SLV1_CTRL      0x2A   // R/W
#define MPU9150_I2C_SLV2_ADDR      0x2B   // R/W
#define MPU9150_I2C_SLV2_REG       0x2C   // R/W
#define MPU9150_I2C_SLV2_CTRL      0x2D   // R/W
#define MPU9150_I2C_SLV3_ADDR      0x2E   // R/W
#define MPU9150_I2C_SLV3_REG       0x2F   // R/W
#define MPU9150_I2C_SLV3_CTRL      0x30   // R/W
#define MPU9150_I2C_SLV4_ADDR      0x31   // R/W
#define MPU9150_I2C_SLV4_REG       0x32   // R/W
#define MPU9150_I2C_SLV4_DO        0x33   // R/W
#define MPU9150_I2C_SLV4_CTRL      0x34   // R/W
#define MPU9150_I2C_SLV4_DI        0x35   // R  
#define MPU9150_I2C_MST_STATUS     0x36   // R
#define MPU9150_INT_PIN_CFG        0x37   // R/W
#define MPU9150_INT_ENABLE         0x38   // R/W
#define MPU9150_INT_STATUS         0x3A   // R  
#define MPU9150_ACCEL_XOUT_H       0x3B   // R  
#define MPU9150_ACCEL_XOUT_L       0x3C   // R  
#define MPU9150_ACCEL_YOUT_H       0x3D   // R  
#define MPU9150_ACCEL_YOUT_L       0x3E   // R  
#define MPU9150_ACCEL_ZOUT_H       0x3F   // R  
#define MPU9150_ACCEL_ZOUT_L       0x40   // R  
#define MPU9150_TEMP_OUT_H         0x41   // R  
#define MPU9150_TEMP_OUT_L         0x42   // R  
#define MPU9150_GYRO_XOUT_H        0x43   // R  
#define MPU9150_GYRO_XOUT_L        0x44   // R  
#define MPU9150_GYRO_YOUT_H        0x45   // R  
#define MPU9150_GYRO_YOUT_L        0x46   // R  
#define MPU9150_GYRO_ZOUT_H        0x47   // R  
#define MPU9150_GYRO_ZOUT_L        0x48   // R  
#define MPU9150_EXT_SENS_DATA_00   0x49   // R  
#define MPU9150_EXT_SENS_DATA_01   0x4A   // R  
#define MPU9150_EXT_SENS_DATA_02   0x4B   // R  
#define MPU9150_EXT_SENS_DATA_03   0x4C   // R  
#define MPU9150_EXT_SENS_DATA_04   0x4D   // R  
#define MPU9150_EXT_SENS_DATA_05   0x4E   // R  
#define MPU9150_EXT_SENS_DATA_06   0x4F   // R  
#define MPU9150_EXT_SENS_DATA_07   0x50   // R  
#define MPU9150_EXT_SENS_DATA_08   0x51   // R  
#define MPU9150_EXT_SENS_DATA_09   0x52   // R  
#define MPU9150_EXT_SENS_DATA_10   0x53   // R  
#define MPU9150_EXT_SENS_DATA_11   0x54   // R  
#define MPU9150_EXT_SENS_DATA_12   0x55   // R  
#define MPU9150_EXT_SENS_DATA_13   0x56   // R  
#define MPU9150_EXT_SENS_DATA_14   0x57   // R  
#define MPU9150_EXT_SENS_DATA_15   0x58   // R  
#define MPU9150_EXT_SENS_DATA_16   0x59   // R  
#define MPU9150_EXT_SENS_DATA_17   0x5A   // R  
#define MPU9150_EXT_SENS_DATA_18   0x5B   // R  
#define MPU9150_EXT_SENS_DATA_19   0x5C   // R  
#define MPU9150_EXT_SENS_DATA_20   0x5D   // R  
#define MPU9150_EXT_SENS_DATA_21   0x5E   // R  
#define MPU9150_EXT_SENS_DATA_22   0x5F   // R  
#define MPU9150_EXT_SENS_DATA_23   0x60   // R  
#define MPU9150_MOT_DETECT_STATUS  0x61   // R  
#define MPU9150_I2C_SLV0_DO        0x63   // R/W
#define MPU9150_I2C_SLV1_DO        0x64   // R/W
#define MPU9150_I2C_SLV2_DO        0x65   // R/W
#define MPU9150_I2C_SLV3_DO        0x66   // R/W
#define MPU9150_I2C_MST_DELAY_CTRL 0x67   // R/W
#define MPU9150_SIGNAL_PATH_RESET  0x68   // R/W
#define MPU9150_MOT_DETECT_CTRL    0x69   // R/W
#define MPU9150_USER_CTRL          0x6A   // R/W
#define MPU9150_PWR_MGMT_1         0x6B   // R/W
#define MPU9150_PWR_MGMT_2         0x6C   // R/W
#define MPU9150_FIFO_COUNTH        0x72   // R/W
#define MPU9150_FIFO_COUNTL        0x73   // R/W
#define MPU9150_FIFO_R_W           0x74   // R/W
#define MPU9150_WHO_AM_I           0x75   // R

//MPU9150 Compass
#define MPU9150_CMPS_XOUT_L        0x4A   // R
#define MPU9150_CMPS_XOUT_H        0x4B   // R
#define MPU9150_CMPS_YOUT_L        0x4C   // R
#define MPU9150_CMPS_YOUT_H        0x4D   // R
#define MPU9150_CMPS_ZOUT_L        0x4E   // R
#define MPU9150_CMPS_ZOUT_H        0x4F   // R

// I2C address 0x69 could be 0x68 depends on your wiring. 
// Put 0x68 if MPU9150 ADO pin is grounded. Change to 0x69 if ADO pin is tied to Vcc.
int MPU9150_I2C_ADDRESS = 0x69;


//Variables where our values can be stored
int cmps[3];
int accl[3];
int gyro[3];
int temp;

/* A name for the LED on pin 13. */
int ledPin = 13 ;

void setup() 
{
  /* Start communication. */
  OneSheeld.begin();     // OneSheeld at COM0, Can't change this setting 
  
  /* Set the LED pin as output. */
  pinMode(ledPin,OUTPUT);
  
  // bind the RPLIDAR driver to the arduino hardware serial
//  lidar.begin(Serial2);  // Lidar at COM2
  Serial2.begin(115200);   // Motor Controller at COM3
  Serial1.begin(115200);   // X-Bee End device at COM1
  
  /* To include more serial devices use Soft Serial */
//  pinMode(RPLIDAR_MOTOR, OUTPUT);
  
  // Initialize the 'Wire' class for the I2C-bus.
  Wire.begin();

  // Clear the 'sleep' bit to start the sensor.
  MPU9150_writeSensor(MPU9150_PWR_MGMT_1, 0);

  MPU9150_setupCompass();
}

void loop() 
{
  
  /* Turn on the LED when the red button is pressed. */
  if(GamePad.isRedPressed())
  {
    /* Turn on the LED. */
    digitalWrite(ledPin,LOW);
    Serial2.print("6");
    Serial1.println("Speed set to 10%");
  }
  else if(GamePad.isOrangePressed())
  {
    /* Turn off the LED. */
    digitalWrite(ledPin,HIGH);
    Serial2.print("5");
    Serial1.println("Speed set to 80%");
  }
  else if(GamePad.isGreenPressed())
  {
    /* Turn off the LED. */
    digitalWrite(ledPin,HIGH);
    Serial2.print("7");
    Serial1.println("Speed set to 35%");  
  }
  else if(GamePad.isBluePressed())
  {
    /* Turn off the LED. */
    digitalWrite(ledPin,HIGH);
    Serial2.print("8");
    Serial1.println("Speed set to 40%");
  }
  else if(GamePad.isUpPressed())
  {
    Serial2.print("3");
    digitalWrite(ledPin,HIGH);
    Serial1.println("Moving Forward");
  }
  /* If down is pressed, move the car backwards. */
  else if (GamePad.isDownPressed())
  {
    Serial2.print("4");
    digitalWrite(ledPin,HIGH);
    Serial1.println("Reverse");
  }
  /* If right is pressed, turn the car to the right. */
  else if (GamePad.isRightPressed())
  {
    Serial2.print("1");
    digitalWrite(ledPin,HIGH);
    Serial1.println("Turning Right");
  }
    /* If left is pressed, turn the car to the left. */
  else if(GamePad.isLeftPressed())
  {
    Serial2.print("2");
    digitalWrite(ledPin,HIGH);
    Serial1.println("Turning Left");
  }
  /* If nothing is pressed stop all motors. */
  else 
  {
    digitalWrite(ledPin,LOW);
  }
  delay(10);
//  sendRPlidarData();
//  sendIMUData();
}

//void sendRPlidarData() {
//  if (IS_OK(lidar.waitPoint())) {
//    float distance = lidar.getCurrentPoint().distance; //distance value in mm unit
//    float angle    = lidar.getCurrentPoint().angle; //anglue value in degree
//    bool  startBit = lidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
//    byte  quality  = lidar.getCurrentPoint().quality; //quality of the current measurement
//    
//    //perform data processing here... 
//    Serial1.println();
//    Serial1.print("Lidar Data          |   ");
//    Serial1.print("Angle = ");
//    Serial1.print(angle);
//    Serial1.print(" ; Distance = ");
//    Serial1.print(distance);
//    Serial1.print(" ; StartBit = ");
//    Serial1.print(startBit);
//    Serial1.print(" ; Quality = ");
//    Serial1.println(quality);
//    
//  } else {
//    analogWrite(RPLIDAR_MOTOR, 0); //stop the rplidar motor
//    Serial1.println("Wait ! Detecting Lidar...");
//    // try to detect RPLIDAR... 
//    rplidar_response_device_info_t info;
//    if (IS_OK(lidar.getDeviceInfo(info, 100))) {
//       // detected...
//       lidar.startScan();
//       
//       // start motor rotating at max allowed speed
//       analogWrite(RPLIDAR_MOTOR, 255);
//       delay(1000);
//    }
//  }
//}

void sendIMUData() {
  double dT = ( (double) MPU9150_readSensor(MPU9150_TEMP_OUT_L,MPU9150_TEMP_OUT_H) + 12412.0) / 340.0;
  Serial1.print("IMU Sensor Value    |   ");
//    Serial1.println(sensorValue);
//    digitalWrite(ledPin,LOW);
  Serial1.print(dT);
  Serial1.print("  M: ");
  Serial1.print(MPU9150_readSensor(MPU9150_CMPS_XOUT_L,MPU9150_CMPS_XOUT_H));
  Serial1.print("  ");
  Serial1.print(MPU9150_readSensor(MPU9150_CMPS_YOUT_L,MPU9150_CMPS_YOUT_H));
  Serial1.print("  ");
  Serial1.print(MPU9150_readSensor(MPU9150_CMPS_ZOUT_L,MPU9150_CMPS_ZOUT_H));
  Serial1.print("  G: ");
  Serial1.print((double)MPU9150_readSensor(MPU9150_GYRO_XOUT_L,MPU9150_GYRO_XOUT_H)/131);
  Serial1.print("  ");
  Serial1.print((double)MPU9150_readSensor(MPU9150_GYRO_YOUT_L,MPU9150_GYRO_YOUT_H)/131);
  Serial1.print("  ");
  Serial1.print((double)MPU9150_readSensor(MPU9150_GYRO_ZOUT_L,MPU9150_GYRO_ZOUT_H)/131);
  Serial1.print("  A: ");
  Serial1.print((double)MPU9150_readSensor(MPU9150_ACCEL_XOUT_L,MPU9150_ACCEL_XOUT_H)/1638.4);
  Serial1.print("  ");
  Serial1.print((double)MPU9150_readSensor(MPU9150_ACCEL_YOUT_L,MPU9150_ACCEL_YOUT_H)/1638.4);
  Serial1.print("  ");
  Serial1.print((double)MPU9150_readSensor(MPU9150_ACCEL_ZOUT_L,MPU9150_ACCEL_ZOUT_H)/1638.4);
  Serial1.println(); 
}

//http://pansenti.wordpress.com/2013/03/26/pansentis-invensense-mpu-9150-software-for-arduino-is-now-on-github/
//Thank you to pansenti for setup code.
//I will documented this one later.
void MPU9150_setupCompass(){
  MPU9150_I2C_ADDRESS = 0x0C;      //change Address to Compass

  MPU9150_writeSensor(0x0A, 0x00); //PowerDownMode
  MPU9150_writeSensor(0x0A, 0x0F); //SelfTest
  MPU9150_writeSensor(0x0A, 0x00); //PowerDownMode

  MPU9150_I2C_ADDRESS = 0x69;      //change Address to MPU

  MPU9150_writeSensor(0x24, 0x40); //Wait for Data at Slave0
  MPU9150_writeSensor(0x25, 0x8C); //Set i2c address at slave0 at 0x0C
  MPU9150_writeSensor(0x26, 0x02); //Set where reading at slave 0 starts
  MPU9150_writeSensor(0x27, 0x88); //set offset at start reading and enable
  MPU9150_writeSensor(0x28, 0x0C); //set i2c address at slv1 at 0x0C
  MPU9150_writeSensor(0x29, 0x0A); //Set where reading at slave 1 starts
  MPU9150_writeSensor(0x2A, 0x81); //Enable at set length to 1
  MPU9150_writeSensor(0x64, 0x01); //overvride register
  MPU9150_writeSensor(0x67, 0x03); //set delay rate
  MPU9150_writeSensor(0x01, 0x80);

  MPU9150_writeSensor(0x34, 0x04); //set i2c slv4 delay
  MPU9150_writeSensor(0x64, 0x00); //override register
  MPU9150_writeSensor(0x6A, 0x00); //clear usr setting
  MPU9150_writeSensor(0x64, 0x01); //override register
  MPU9150_writeSensor(0x6A, 0x20); //enable master i2c mode
  MPU9150_writeSensor(0x34, 0x13); //disable slv4
}

////////////////////////////////////////////////////////////
///////// I2C functions to get easier all values ///////////
////////////////////////////////////////////////////////////

int MPU9150_readSensor(int addrL, int addrH){
  Wire.beginTransmission(MPU9150_I2C_ADDRESS);
  Wire.write(addrL);
  Wire.endTransmission(false);

  Wire.requestFrom(MPU9150_I2C_ADDRESS, 1, true);
  byte L = Wire.read();

  Wire.beginTransmission(MPU9150_I2C_ADDRESS);
  Wire.write(addrH);
  Wire.endTransmission(false);

  Wire.requestFrom(MPU9150_I2C_ADDRESS, 1, true);
  byte H = Wire.read();

  return (int16_t)((H<<8)+L);
}

int MPU9150_readSensor(int addr){
  Wire.beginTransmission(MPU9150_I2C_ADDRESS);
  Wire.write(addr);
  Wire.endTransmission(false);

  Wire.requestFrom(MPU9150_I2C_ADDRESS, 1, true);
  return Wire.read();
}

int MPU9150_writeSensor(int addr,int data){
  Wire.beginTransmission(MPU9150_I2C_ADDRESS);
  Wire.write(addr);
  Wire.write(data);
  Wire.endTransmission(true);

  return 1;
}

