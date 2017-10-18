/***************************************************************************
	This is a library for the LPS22HB Absolute Digital Barometer
	-	Originally written by Adrien Chapelet for Iotech
	-	Adjusted by Gregory Knauff of SODAQ for the NB-IoT shield

	Standard I2C-address is 0x5D (pullup/Vcc). If two LPS22HB 
	sensors are being used, please take note of changing 
	one of the addresses to 0x5C (pulldown/GND)

 ***************************************************************************/

#include <Wire.h>

#include "Sodaq_LPS22HB.h"

Sodaq_LPS22HB::Sodaq_LPS22HB()
{
}

void Sodaq_LPS22HB::begin(uint8_t address) {
	_address = address;
	Wire.begin();
	write(LPS22HB_RES_CONF, 0x0); // resolution: temp=32, pressure=128
	write(LPS22HB_CTRL_REG1, 0x00); // one-shot mode
}

byte Sodaq_LPS22HB::whoAmI() {
	uint8_t data;

	Wire.beginTransmission(_address);
	Wire.write(LPS22HB_WHO_AM_I);
	Wire.endTransmission();
	Wire.requestFrom(_address, 1);
	
	if(Wire.read() == LPS22HB_WHO_AM_I_RETURN)
	{
		return true;
	}

	return false;
}

float Sodaq_LPS22HB::readPressure() {
	write(LPS22HB_CTRL_REG2, 0x1);

	if (status(0x1) < 0)
		return 1.23;
	//delay(50);
	uint8_t pressOutH = read(LPS22HB_PRES_OUT_H);
	uint8_t pressOutL = read(LPS22HB_PRES_OUT_L);
	uint8_t pressOutXL = read(LPS22HB_PRES_OUT_XL);

	long val = ( ((long)pressOutH << 24) | ((long)pressOutL << 16) | ((long)pressOutXL << 8)) >> 8;
	//if (val == 1.00) readPressure();
	return val/4096.0f;
}

uint32_t Sodaq_LPS22HB::readPressureRAW() {
	write(LPS22HB_CTRL_REG2, 0x1);

	if (status(0x1) < 0)
		return 123;
	//delay(50);
	uint8_t pressOutH = read(LPS22HB_PRES_OUT_H);
	uint8_t pressOutL = read(LPS22HB_PRES_OUT_L);
	uint8_t pressOutXL = read(LPS22HB_PRES_OUT_XL);

	int32_t val = ((pressOutH << 24) | (pressOutL << 16) | (pressOutXL << 8));
	val >> 8;
	val=val+0x400000;
	//if (val == 1.00) readPressure();
	return (uint32_t)val;
}

uint32_t Sodaq_LPS22HB::readPressureUI() {
	write(LPS22HB_CTRL_REG2, 0x1);

	if (status(0x1) < 0)
		return 1.23;
	//delay(50);
	uint8_t pressOutH = read(LPS22HB_PRES_OUT_H);
	uint8_t pressOutL = read(LPS22HB_PRES_OUT_L);
	uint8_t pressOutXL = read(LPS22HB_PRES_OUT_XL);

	uint32_t val = ((pressOutH << 24) | (pressOutL << 16) | (pressOutXL << 8)) >> 8;
	//if (val == 1.00) readPressure();
	return val/4096;
}

float Sodaq_LPS22HB::readTemperature() {
	write(LPS22HB_CTRL_REG2, 0x1);
	if (status(0x2) < 0)
		return 4.56;

	uint8_t tempOutH = read(LPS22HB_TEMP_OUT_H);
	uint8_t tempOutL = read(LPS22HB_TEMP_OUT_L);

	int16_t val = tempOutH << 8 | tempOutL & 0xff;
	return 42.5f+val/480.0f;
}


uint8_t Sodaq_LPS22HB::status(uint8_t status) {
	int count = 1000;
	uint8_t data = 0xff;
	do {
		data = read(LPS22HB_STATUS_REG);
		--count;
		if (count < 0)
			break;
	} while ((data & status) == 0);

	if (count < 0)
		return -1;
	else
		return 0;
}

uint8_t Sodaq_LPS22HB::read(uint8_t reg) {
	Wire.beginTransmission(_address);
	Wire.write(reg);
	Wire.endTransmission();
	Wire.requestFrom(_address, 1);
	return Wire.read();
}

void Sodaq_LPS22HB::write(uint8_t reg, uint8_t data) {
	Wire.beginTransmission(_address);
	Wire.write(reg);
	Wire.write(data);
	Wire.endTransmission();
}
