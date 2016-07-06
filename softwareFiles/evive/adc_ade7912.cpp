/*
 * adc_ade7912.cpp
 *
 *  Created on: May 27, 2016
 *      Author: dhrups
 */
/*
 * Sensing with ADE7912
 * Based on codes of Art of Circuits
 * Contact: support@artofcircuits.com
 * Edited by evive team http://evive.cc
 * or Dhrupal R Shah, Agilo Technologies
 * Edited on 20160518
 * Contact: support@evive.cc
 * Target CPU: ATMEGA 2560
 * Target Board: Arduino MEGA
*/

#include "adc_ade7912.h"

/*---------ADE MACROS/VAR//start----------*/
#define __DEBUG__    /* comment this line to disable debugging messages over serial console*/

// inslude the SPI library:
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
#define ADE791X_MUL_VIMWV          0.0011901
#define ADE791X_OFFSET_VIMWV			 349319
#define ADE791X_MUL_IWV            0.0005921
#define ADE791X_OFFSET_IWV				 349319

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
/*---------ADE MACROS/VAR//end----------*/

/*---------ADE functions//start-------*/

void ade791x_init(void)
{
  pinMode(SPI_ADC_SS, OUTPUT);
  pinMode(ADC_RDY, INPUT);
  // take the SS pin high to de-select the chip:
//  digitalWrite(SPI_ADC_SS, HIGH);
  // initialize SPI:
//  SPI.begin();
  //delay(1);
//  delayMicroseconds(16);
  //SPI.setClockDivider(SPI_ADC_SS, 64);  // default is 4MHz clock
//  SPI.setBitOrder(MSBFIRST);        // default is MSBFIRST
//  SPI.setDataMode(SPI_MODE3);       // ADE791x chip uses SPI_MODE3
//  ade791x_write(ADE791X_REG_LOCK,UNLOCKED);
//  ade791x_write(ADE791X_REG_CONFIG, ADC_FREQ_4KHZ | TEMP_EN);  // configures adc sampling frequency and enables temperature on V2WV register
}

long ade791x_read_v1(void)
{
	//unsigned long st = micros();
  unsigned char addr = ADE791X_REG_V1WV;
  long value = 0;  // stores value to return
  long tempValue1 = 0, tempValue2 = 0 , tempValue3 = 0;
  unsigned char opcode; // stores opcode

  addr = addr << 3;  // left shift address by 3 bits
  opcode = (addr | ADE791X_READ);     // forms opcode byte
  // Serial.print ("opcode: ");    // for debug only
  // Serial.println(opcode, BIN);  // for debug only

  SPI.beginTransaction(ADCSetting);
  // take the SS pin low to select the chip:
//  digitalWrite(SPI_ADC_SS, LOW);  // bring SS2 pin low
//	PORTC &= ~_BV(PC2);
	PORTC &= 0b11111011;
  SPI.transfer(opcode);        // send out opcode
//  value  = SPI.transfer(0xFF) * 0x10000;  // read MS Byte
////  tempValue1=value;
//  value |= SPI.transfer(0xFF) * 0x100;  // read mid Byte
////  tempValue2=value;
//  value |= SPI.transfer(0xFF);  // LS Byte

  tempValue1 = SPI.transfer(0xFF);  // read MS Byte
  tempValue2 = SPI.transfer(0xFF);  // read mid Byte
  tempValue3 = SPI.transfer(0xFF);  // LS Byte

  // take the SS pin high to de-select the chip:
  //digitalWrite(SPI_ADC_SS, HIGH);
	//PORTC |= _BV(PC2);
	PORTC |= 0b00000100;
  SPI.endTransaction();

  tempValue1  = tempValue1 * 0x10000;
  tempValue2 = tempValue1 | tempValue2 * 0x100;
  value = tempValue2 | tempValue3;

  value = value <<8;        // sign extends value to 32 bit
  value = value / 0x100;    // converts back value to 24 bit but now sign extended

  value = (value - ADE791X_OFFSET_V1WV)*ADE791X_MUL_V1WV; //ADE791X_MUL_V1WV;

  #ifdef __DEBUG__
 // Serial.print ("V1: ");
 // Serial.println (value);
  #endif
  return value;
}

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
  // digitalWrite(SPI_ADC_SS, LOW);  // bring SS2 pin low
  //	PORTC &= ~_BV(PC2);
  	PORTC &= 0b11111011;
  SPI.transfer(opcode);        // send out opcode
//  value  = SPI.transfer(0xFF) * 0x10000;  // read MS Byte
////  tempValue1=value;
//  value |= SPI.transfer(0xFF) * 0x100;  // read mid Byte
////  tempValue2=value;
//  value |= SPI.transfer(0xFF);  // LS Byte

  tempValue1 = SPI.transfer(0xFF);  // read MS Byte
  tempValue2 = SPI.transfer(0xFF);  // read mid Byte
  tempValue3 = SPI.transfer(0xFF);  // LS Byte

  // take the SS pin high to de-select the chip:
  // digitalWrite(SPI_ADC_SS, HIGH);
	//PORTC |= _BV(PC2);
	PORTC |= 0b00000100;
  SPI.endTransaction();

  tempValue1  = tempValue1 * 0x10000;
  tempValue2 = tempValue1 | tempValue2 * 0x100;
  value = tempValue2 | tempValue3;

	// Serial.print("RAW: ");
	// Serial.println (value);
	value = value <<8;        // sign extends value to 32 bit
  value = value / 0x100;    // converts back value to 24 bit but now sign extended
	value = (value - ADE791X_OFFSET_VIMWV)*ADE791X_MUL_VIMWV; //ADE791X_MUL_V1WV;
		// Serial.print ("VIM: ");
		// Serial.println (value);
  return value;
}

long ade791x_read_im(void)
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
  // digitalWrite(SPI_ADC_SS, LOW);  // bring SS2 pin low
  //	PORTC &= ~_BV(PC2);
  	PORTC &= 0b11111011;
  SPI.transfer(opcode);        // send out opcode
//  value  = SPI.transfer(0xFF) * 0x10000;  // read MS Byte
////  tempValue1=value;
//  value |= SPI.transfer(0xFF) * 0x100;  // read mid Byte
////  tempValue2=value;
//  value |= SPI.transfer(0xFF);  // LS Byte

  tempValue1 = SPI.transfer(0xFF);  // read MS Byte
  tempValue2 = SPI.transfer(0xFF);  // read mid Byte
  tempValue3 = SPI.transfer(0xFF);  // LS Byte

  // take the SS pin high to de-select the chip:
  // digitalWrite(SPI_ADC_SS, HIGH);
	//PORTC |= _BV(PC2);
	PORTC |= 0b00000100;
  SPI.endTransaction();

  tempValue1  = tempValue1 * 0x10000;
  tempValue2 = tempValue1 | tempValue2 * 0x100;
  value = tempValue2 | tempValue3;
//  tempValue3=value;
	// Serial.print("RAW: ");
	// Serial.println (value);
	value = value <<8;        // sign extends value to 32 bit
  value = value / 0x100;    // converts back value to 24 bit but now sign extended

		value = (value - ADE791X_OFFSET_IWV)*ADE791X_MUL_IWV; //ADE791X_MUL_IWV;
		// Serial.print ("IM: ");
		// Serial.println (value);
  return value;
}
/*--------ADE functions//end------------*/
