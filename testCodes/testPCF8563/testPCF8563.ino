/* Demonstration of Rtc_Pcf8563 Date Time individual functions. 
 * Set the clock to a time then loop over reading time and 
 * output the time and date to the serial console.
 *
 * I used a RBBB with Arduino IDE, the pins are mapped a 
 * bit differently. Change for your hw
 * SCK - A5, SDA - A4, INT - D3/INT1
 *
 * After loading and starting the sketch, use the serial monitor
 * to see the clock output.
 * 
 * setup:  see Pcf8563 data sheet.
 *         1x 10Kohm pullup on Pin3 INT
 *         No pullups on Pin5 or Pin6 (I2C internals used)
 *         1x 0.1pf on power
 *         1x 32khz chrystal
 *
 * Joe Robertson, jmr
 * orbitalair@bellsouth.net
 */ 
#include <Wire.h>
#include <Rtc_Pcf8563.h>

//init the real time clock
Rtc_Pcf8563 rtc;

void setup()
{
  Serial.begin(9600);
  Serial.println("Date and Time function test.");
  //clear out the registers
//  rtc.initClock();
  //set a time to start with.
  //day, weekday, month, century(1=1900, 0=2000), year(0-99)
  rtc.setDate(01, 6, 5, 0, 16);
  //hr, min, sec
  rtc.setTime(15, 20, 0);
  
//  Serial.println("Date set to: Sunday(6) March(3) 14, 2010.  Time set to:  1:15:00 am.");
  
  Serial.println("Now reading back from chip.");
  
    //both format functions call the internal getTime() so that the 
  //formatted strings are at the current time/date.
  Serial.print("Hour:");
  Serial.println(rtc.getHour());
  Serial.print("Minute:");
  Serial.println(rtc.getMinute());
  Serial.print("Second:");
  Serial.println(rtc.getSecond());
  Serial.print("Weekday:");
  Serial.println(rtc.getWeekday());
  Serial.print("Day:");
  Serial.println(rtc.getDay());
  Serial.print("Month:");
  Serial.println(rtc.getMonth());
  Serial.print("Year:");
  Serial.println(rtc.getYear());

}

void loop()
{
  //both format functions call the internal getTime() so that the 
  //formatted strings are at the current time/date.
  Serial.print(rtc.formatTime());
  Serial.print("\r\n");
  Serial.print(rtc.formatDate());
  Serial.print("\r\n");
  delay(1000);
}



