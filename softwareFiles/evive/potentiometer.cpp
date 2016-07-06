/*
|| @changelog
|| | 1.0 2009-04-13 - Alexander Brevig : Initial Release
|| | 2.0 2016-05-22 - http://evive.cc Dhrupal R Shah support@evive.cc
|| #

|| @file Potentiometer.cpp
|| @version 1.2
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Provide an easy way of making/using potentiometers
|| #
||
|| @license
|| | This library is free software; you can redistribute it and/or
|| | modify it under the terms of the GNU Lesser General Public
|| | License as published by the Free Software Foundation; version
|| | 2.1 of the License.
|| |
|| | This library is distributed in the hope that it will be useful,
|| | but WITHOUT ANY WARRANTY; without even the implied warranty of
|| | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
|| | Lesser General Public License for more details.
|| |
|| | You should have received a copy of the GNU Lesser General Public
|| | License along with this library; if not, write to the Free Software
|| | Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
|| #
||
*/

#include "potentiometer.h"

Potentiometer::Potentiometer(byte potPin){
	_pin=potPin;
	setSectors(6);
	_value = analogRead(_pin);
}

Potentiometer::Potentiometer(byte potPin, uint16_t sectors){
	_pin=potPin;
	setSectors(sectors);
}

uint16_t Potentiometer::getValue(){
	return (_value = analogRead(_pin));
}

uint16_t Potentiometer::hadValue(){
	return _value;
}

uint16_t Potentiometer::getSector(){
	return analogRead(_pin)/(1024/_sectors);
}

void Potentiometer::setSectors(uint16_t newSectors){
	if (newSectors<1024 && newSectors>0){
		_sectors=newSectors;
	}else if (newSectors<0){
		_sectors=0;
	}else{
		_sectors=1023;
	}
}

Potentiometer pot1(9,6), pot2(10,6);
