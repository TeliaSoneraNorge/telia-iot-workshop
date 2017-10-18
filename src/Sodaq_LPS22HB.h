/***************************************************************************
	This is a library for the LPS22HB Absolute Digital Barometer
	-	Originally written by Adrien Chapelet for Iotech
	-	Adjusted by Gregory Knauff of SODAQ for the NB-IoT shield

	Standard I2C-address is 0x5D (pullup/Vcc). If two LPS22HB 
	sensors are being used, please take note of changing 
	one of the addresses to 0x5C (pulldown/GND)

 ***************************************************************************/

#ifndef _Sodaq_LPS22HB_h

#define _Sodaq_LPS22HB_h
#include <Arduino.h>

#define LPS22HB_WHO_AM_I			0X0F // Who am I
#define LPS22HB_WHO_AM_I_RETURN		0xB1 // Return value of WHO_AM_I register
#define LPS22HB_RES_CONF			0X1A // Resolution
#define LPS22HB_CTRL_REG1			0X10
#define LPS22HB_CTRL_REG2			0X11
#define LPS22HB_STATUS_REG			0X27
#define LPS22HB_PRES_OUT_XL			0X28 // LSB
#define LPS22HB_PRES_OUT_L			0X29
#define LPS22HB_PRES_OUT_H			0X2A // MSB
#define LPS22HB_TEMP_OUT_L			0X2B // LSB
#define LPS22HB_TEMP_OUT_H			0X2C // MSB



class Sodaq_LPS22HB {
public:
	Sodaq_LPS22HB();

	void begin(uint8_t address);

	uint8_t whoAmI();
	float readTemperature();

	float readPressure();
	uint32_t readPressureUI();
	uint32_t readPressureRAW();

private:
	uint8_t _address;
	uint8_t read(uint8_t reg);
	void write(uint8_t reg, uint8_t data);
	uint8_t status(uint8_t data);
};

#endif
