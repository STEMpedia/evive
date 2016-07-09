/*
  ADC_Test
  Author: Art of Circuits
  Contact: support@artofcircuits.com
	Edited by evive http://evive.cc
	or Dhrupal R Shah, Agilo Technologies on 20160518
	Contact: support@evive.cc
	Target CPU: ATMEGA32U4
  Targer Board: Arduino MEGA
  
  Description: 
    Test code that writes sends SPI data
  
  External Libraries:  
    None
 
  Test Setup:
  1. Power the Board
  2. Program code into the Arduino
    
  Observations:

 */
#define __DEBUG__    /* comment this line to disable debugging messages over serial console*/

// include the SPI library:
#include <SPI.h>

int SPI_ADC_SS = 35;    // SPI ADC SS
int ADC_RDY = 32;      // ADC Ready pin
#define ADC_SPIMaxSpeed 5600000
#define ADC_SPIMode SPI_MODE3
#define ADC_SPIDataOrder MSBFIRST

// Command Definitions
#define ADE791X_READ    0x04
#define ADE791X_WRITE   0x00

// Register Definitions
#define ADE791X_REG_IWV            0x00    /* Instantaneous value of Current I. */
#define ADE791X_REG_V1WV           0x01    /* Instantaneous value of Voltage V1 */
#define ADE791X_REG_V2WV           0x02    /* Instantaneous value of Voltage V2 */
#define ADE791X_MUL_V1WV           0.006485
#define ADE791X_OFFSET_V1WV        362760   
#define ADE791X_MUL_V2WV           0.0011901
#define ADE791X_MUL_IWV            0.0005921

#define ADE791X_REG_ADC_CRC        0x04    /* CRC value of IWV, V1WV, and V2WV registers. See the ADC Output Values CRC section for details */
#define ADE791X_REG_CTRL_CRC       0x05    /* CRC value of configuration registers. See the CRC of Configuration Registers  for details. */

#define ADE791X_REG_CNT_SNAPSHOT   0x07    /* Snapshot value of the counter used in synchronization operation. */
#define ADE791X_REG_CONFIG         0x08    /* Configuration register. See Table 15 for details */
#define ADE791X_REG_STATUS0        0x09    /* Status register */
#define ADE791X_REG_LOCK           0x0A    /* Memory protection register */
#define ADE791X_REG_SYNC_SNAP      0x0B    /* Synchronization register */
#define ADE791X_REG_COUNTER0       0x0C    /* Contains the least significant eight bits of the internal synchronization counter */
#define ADE791X_REG_COUNTER1       0x0D    /* COUNTER1[3:0] bits contain the most significant four bits of the internal synchronization counter */
#define ADE791X_REG_EMI_CTRL       0x0E    /* EMI control register. */
#define ADE791X_REG_STATUS1        0x0F    /* Status register */

#define ADE791X_REG_TEMPOS         0x18    /* Temperature sensor offset */

/* configuration register constants */
#define CLKOUT_EN                  0x01
#define PWRDWN_EN                  0x04    /* Shuts down the dc-to-dc converter. When PWRDWN_EN = 0, the default value, the */
#define TEMP_EN                    0x08    /* This bit selects the second voltage channel measurement. */
#define ADC_FREQ_8KHZ              0x00    /* These bits select the ADC output frequency to 8khz. */
#define ADC_FREQ_4KHZ              0x10    /* These bits select the ADC output frequency.4khz */
#define ADC_FREQ_2KHZ              0x20    /* These bits select the ADC output frequency.2khz */
#define ADC_FREQ_1KHZ              0x30    /* These bits select the ADC output frequency.1khz */
#define SWRST                      0x40    /* When this bit is set to 1, a software reset is initiated. This bit clears itself to 0 after */
#define BW                         0x80    /* Selects the bandwidth of the digital low-pass filter of the ADC. When BW = 0, the */

/*Status0 registers (address 0x9*/
#define RESET_ON                  0x00
#define CRC_STAT                  0x01
#define IC_PROT                   0x02

/* lock register constants(address 0xA */
#define LOCKED                    0xCA    /*locks configuration register writing */
#define UNLOCKED                  0x9C    /*unlocks configuration register writing */

SPISettings ADCSetting(ADC_SPIMaxSpeed,ADC_SPIDataOrder,ADC_SPIMode);

// the setup routine runs once when you press reset:
void setup() {
  
  Serial.begin (250000);
  ade791x_init();
    delay (100); 
}

// the loop routine runs over and over again forever
void loop() { 
  ade791x_read_v1 ();
//  ade791x_read_v2();
//  ade791x_read_vim (); 
//  ade791x_read_i ();
// ade791x_read_temperature ();
//Serial.println(millis());
//  Serial.println();
    
//  delay (100);  

}


void ade791x_init(void)
{
  pinMode(SPI_ADC_SS, OUTPUT);
  pinMode(ADC_RDY, INPUT);
  // take the SS pin high to de-select the chip:
  digitalWrite(SPI_ADC_SS, HIGH);
  // initialize SPI:
  SPI.begin();
//  delay(1);
//  delayMicroseconds(16);
  //SPI.setClockDivider(SPI_ADC_SS, 64);  // default is 4MHz clock
//  SPI.setBitOrder(MSBFIRST);        // default is MSBFIRST
//  SPI.setDataMode(SPI_MODE3);       // ADE791x chip uses SPI_MODE3

//DS: MAKE  THIS WORKING
  //  ade791x_write(ADE791X_REG_LOCK,UNLOCKED); 
//  ade791x_write(ADE791X_REG_CONFIG, ADC_FREQ_4KHZ | TEMP_EN);  // configures adc sampling frequency and enables temperature on V2WV register
 
}

///////////////////////////////////////////////////////////////////////////////
// function name: ade791x_read()
// inputs: none
// outputs: unsigned char value read from ADC
// Description: function that reads from ADC over SPI bus
//
///////////////////////////////////////////////////////////////////////////////

unsigned char ade791x_read(unsigned char addr)
{
  unsigned char value;  // stores value to return
  unsigned char opcode; // stores opcode
  
  addr = addr << 3;  // left shift address by 3 bits
  opcode = (addr | ADE791X_READ); // forms opcode byte
  Serial.print ("opcode: ");    // for debug only
  Serial.println(opcode, BIN);  // for debug only

  // take the SS pin low to select the chip:
  SPI.beginTransaction(ADCSetting);  
  digitalWrite(SPI_ADC_SS, LOW);  // bring SS2 pin low
  SPI.transfer(opcode);           // send out opcode
  value = SPI.transfer(0xFF);     // send out dummy byte to read register
  // take the SS pin high to de-select the chip:
  digitalWrite(SPI_ADC_SS, HIGH);
  SPI.endTransaction();  
  return value;
}


///////////////////////////////////////////////////////////////////////////////
// function name: ade791x_write()
// inputs: unsigned char addr (address)
//         unsigned char value
// outputs: 
// Description: function that writes ADE791x ADC over SPI interface. 
///////////////////////////////////////////////////////////////////////////////

unsigned char ade791x_write(unsigned char addr, unsigned char value)
{
  unsigned char opcode; // stores opcode
  unsigned char v;
  
  addr = addr << 3;  // left shift address by 3 bits
  opcode = (addr | ADE791X_WRITE);// forms opcode byte
  Serial.print ("opcode: ");    // for debug only
  Serial.println(opcode, BIN);  // for debug only
  Serial.print ("Value: ");    // for debug only
  Serial.println(value, BIN);  // for debug only
  
  // take the SS pin low to select the chip:
  digitalWrite(SPI_ADC_SS, LOW); // bring SS2 pin low
  SPI.transfer(opcode);          // send out opcode
  v = SPI.transfer(value);       // send out dummy byte to read register

  // take the SS pin high to de-select the chip:
  digitalWrite(SPI_ADC_SS, HIGH);
  return v;
}


///////////////////////////////////////////////////////////////////////////////
// function name: ade791x_read_v1()
// inputs: none
// outputs: 4 byte / signed long value read from ADC V1WV register
// Description: function that reads ADE791x ADC V1WV register over SPI
// interface. 
///////////////////////////////////////////////////////////////////////////////

long ade791x_read_v1(void)
{
	//unsigned long st = micros();
  unsigned char addr = ADE791X_REG_V1WV;
  long value = 0;  // stores value to return
  long tempValue1 = 0, tempValue2 = 0 , tempValue3 = 0;  
  unsigned char opcode; // stores opcode
  
  addr = addr << 3;  // left shift address by 3 bits
  opcode = (addr | ADE791X_READ);     // forms opcode byte
//  Serial.print ("opcode: ");    // for debug only
//  Serial.println(opcode, BIN);  // for debug only

  SPI.beginTransaction(ADCSetting);
  // take the SS pin low to select the chip:
//  digitalWrite(SPI_ADC_SS, LOW);  // bring SS2 pin low
	PORTC &= ~_BV(PC2);
  SPI.transfer(opcode);        // send out opcode
//  value  = SPI.transfer(0xFF) * 0x10000;  // read MS Byte
////  tempValue1=value;  
//  value |= SPI.transfer(0xFF) * 0x100;  // read mid Byte
////  tempValue2=value;  
//  value |= SPI.transfer(0xFF);  // LS Byte

  tempValue1 = SPI.transfer(0xFF);  // read MS Byte
//  tempValue1=value;  
  tempValue2 = SPI.transfer(0xFF);  // read mid Byte
//  tempValue2=value;  
  tempValue3 = SPI.transfer(0xFF);  // LS Byte

  // take the SS pin high to de-select the chip:
  //digitalWrite(SPI_ADC_SS, HIGH);  
	PORTC |= _BV(PC2);
	
  SPI.endTransaction();  

  tempValue1  = tempValue1 * 0x10000;
  tempValue2 = tempValue1 | tempValue2 * 0x100;
  value = tempValue2 | tempValue3;
    
  value = value <<8;        // sign extends value to 32 bit
  value = value / 0x100;    // converts back value to 24 bit but now sign extended


  #ifdef __DEBUG__
//  Serial.print ("val1 :");
//  Serial.println (tempValue1,BIN);
//  Serial.print ("val2:");
//  Serial.println (tempValue2,BIN);
//  Serial.print ("val3 :");
//  Serial.println (tempValue3,BIN);  
////  #endif  

  value = (value - 362760.0)*0.006485; //ADE791X_MUL_V1WV;
	
//  Serial.print ("V1: ");
//  Serial.println (value);
//    Serial.print ("V1: ");
//  Serial.println (value,BIN);
  #endif  
	//Serial.println(micros()-st);
  return value;  

}

///////////////////////////////////////////////////////////////////////////////
// function name: ade791x_read_v2()
// inputs: none
// outputs: 4 byte / long value read from ADC V2WV register
// valid bits are 23-0 upper bits are all 0
// Description: function that reads ADE791x ADC V2WV register over SPI
// interface. 
///////////////////////////////////////////////////////////////////////////////

long ade791x_read_v2(void)
{
  unsigned char addr = ADE791X_REG_V2WV;
  long value = 0;  // stores value to return
  long tempValue1, tempValue2, tempValue3;
  unsigned char opcode; // stores opcode
  
  addr = addr << 3;  // left shift address by 3 bits
  opcode = (addr | ADE791X_READ);     // forms opcode byte
//  Serial.print ("opcode: ");    // for debug only
//  Serial.println(opcode, BIN);  // for debug only
  SPI.beginTransaction(ADCSetting);
  // take the SS pin low to select the chip:
  digitalWrite(SPI_ADC_SS, LOW);  // bring SS2 pin low
  SPI.transfer(opcode);        // send out opcode
  tempValue1 = SPI.transfer(0xff);  // read MS Byte
//  tempValue1=value;  
  tempValue2 = SPI.transfer(0xff);  // read mid Byte
//  tempValue2=value;  
  tempValue3 = SPI.transfer(0xff);  // LS Byte

  // take the SS pin high to de-select the chip:
  digitalWrite(SPI_ADC_SS, HIGH);  
  SPI.endTransaction();  

  tempValue1  = tempValue1 * 0x10000;
  tempValue2 = tempValue1 | tempValue2 * 0x100;
  value = tempValue2 | tempValue3;
//  tempValue3=value;
    
  value = value <<8;        // sign extends value to 32 bit
  value = value / 0x100;    // converts back value to 24 bit but now sign extended


  #ifdef __DEBUG__
//  Serial.print ("val1 :");
//  Serial.println (tempValue1,BIN);
//  Serial.print ("val2:");
//  Serial.println (tempValue2,BIN);
//  Serial.print ("val3 :");
//  Serial.println (tempValue3,BIN);  
////  #endif  
  //value = (value);// - 362760.0)*0.006485; //ADE791X_MUL_V1WV;
  Serial.print ("V2: ");
  Serial.println (value);
//    Serial.print ("V2: ");
//  Serial.println (value,BIN);
  #endif  
  return value; 
}

///////////////////////////////////////////////////////////////////////////////
// function name: ade791x_read_vim()
// inputs: none
// outputs: 4 byte / long value read from ADC IWV register
// valid bits are 23-0. upper bits are all 0
// Description: function that reads ADE791x ADC IWV register over SPI
// interface. 
///////////////////////////////////////////////////////////////////////////////

long ade791x_read_vim(void)
{
  unsigned char addr = ADE791X_REG_IWV;
  long value = 0;  // stores value to return
  long tempValue1 = 0, tempValue2 = 0 , tempValue3 = 0;  
  unsigned char opcode; // stores opcode
  
  addr = addr << 3;  // left shift address by 3 bits
  opcode = (addr | ADE791X_READ);     // forms opcode byte
//  Serial.print ("opcode: ");    // for debug only
//  Serial.println(opcode, BIN);  // for debug only

  SPI.beginTransaction(ADCSetting);
  // take the SS pin low to select the chip:
  digitalWrite(SPI_ADC_SS, LOW);  // bring SS2 pin low
  SPI.transfer(opcode);        // send out opcode
//  value  = SPI.transfer(0xFF) * 0x10000;  // read MS Byte
////  tempValue1=value;  
//  value |= SPI.transfer(0xFF) * 0x100;  // read mid Byte
////  tempValue2=value;  
//  value |= SPI.transfer(0xFF);  // LS Byte

  tempValue1 = SPI.transfer(0xFF);  // read MS Byte
//  tempValue1=value;  
  tempValue2 = SPI.transfer(0xFF);  // read mid Byte
//  tempValue2=value;  
  tempValue3 = SPI.transfer(0xFF);  // LS Byte

  // take the SS pin high to de-select the chip:
  digitalWrite(SPI_ADC_SS, HIGH);  
  SPI.endTransaction();  

  tempValue1  = tempValue1 * 0x10000;
  tempValue2 = tempValue1 | tempValue2 * 0x100;
  value = tempValue2 | tempValue3;
//  tempValue3=value;
    
  value = value <<8;        // sign extends value to 32 bit
  value = value / 0x100;    // converts back value to 24 bit but now sign extended


  #ifdef __DEBUG__
//  Serial.print ("val1 :");
//  Serial.println (tempValue1,BIN);
//  Serial.print ("val2:");
//  Serial.println (tempValue2,BIN);
//  Serial.print ("val3 :");
//  Serial.println (tempValue3,BIN);  
////  #endif  
  value = (value - 349319.0)*0.0011901; //ADE791X_MUL_V1WV;
  // Serial.print ("V1M: ");
  // Serial.println (value);
//    Serial.print ("V1: ");
//  Serial.println (value,BIN);
  #endif  
  return value;  
}


///////////////////////////////////////////////////////////////////////////////
// function name: ade791x_read_i()
// inputs: none
// outputs: 4 byte / long value read from ADC IWV register
// valid bits are 23-0. upper bits are all 0
// Description: function that reads ADE791x ADC IWV register over SPI
// interface. 
///////////////////////////////////////////////////////////////////////////////

long ade791x_read_i(void)
{
  unsigned char addr = ADE791X_REG_IWV;
  long value = 0;  // stores value to return
  unsigned char opcode; // stores opcode
  
  addr = addr << 3;  // left shift address by 3 bits
  opcode = (addr | ADE791X_READ);     // forms opcode byte
//  Serial.print ("opcode: ");    // for debug only
//  Serial.println(opcode, BIN);  // for debug only

  // take the SS pin low to select the chip:
  digitalWrite(SPI_ADC_SS, LOW);  // bring SS2 pin low
  SPI.transfer(opcode);        // send out opcode
  value  = SPI.transfer(0xff) * 0x10000;  // read MS Byte
  value |= SPI.transfer(0xff) * 0x100;  // read mid Byte
  value |= SPI.transfer(0xff);  // LS Byte

  // take the SS pin high to de-select the chip:
  digitalWrite(SPI_ADC_SS, HIGH);
  #ifdef __DEBUG__
  Serial.print ("I: ");
  Serial.println (value);
  #endif
  return value;
}


///////////////////////////////////////////////////////////////////////////////
// function name: ade791x_read_temperature()
// inputs: none
// outputs: temperature 
// valid bits are 23-0 upper bits are all 0
// Description: reads chip temperature and ignores Temperature offset 
// in TEMPOS tegister.
///////////////////////////////////////////////////////////////////////////////

double ade791x_read_temperature (void)
{
  long value;
  double temp;
  long tempos;
  
  tempos = ade791x_read (ADE791X_REG_TEMPOS);
  Serial.println (tempos, BIN);
  tempos = tempos * 2048;     //TEMPOS*2^11

  
  value = ade791x_read_v2 ();
//  temp = ((value) / 11466.56) -306.47;
  temp = ((value+tempos) / 11466.56) -306.47;

  #ifdef __DEBUG__
  Serial.print ("Temp: ");
  Serial.print (temp);
  Serial.println (" C");
  #endif
  return temp;  // returns temperature in celcius  
}

