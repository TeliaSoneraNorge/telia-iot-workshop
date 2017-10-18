/***************************************************************************
	This is a library for the LPS22HB Absolute Digital Barometer
		Originally written by Adrien Chapelet for Iotech
		Adjusted by Gregory Knauff of SODAQ for the NB-IoT shield

	Standard I2C-address is 0x5D (pullup/Vcc). If two LPS22HB 
	sensors are being used, please take note of changing 
	one of the addresses to 0x5C (pulldown/GND)

 ***************************************************************************/

#include <Wire.h>
#include "Sodaq_LPS22HB.h"

#if defined(ARDUINO_AVR_LEONARDO)
#define DEBUG_STREAM Serial 

#elif defined(ARDUINO_SODAQ_EXPLORER)
#define DEBUG_STREAM SerialUSB

#else
#error "Please select a Sodaq ExpLoRer, Arduino Leonardo or add your board."
#endif 

Sodaq_LPS22HB lps22hb;

void setup()
{
	delay(500);
	DEBUG_STREAM.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
	DEBUG_STREAM.println("\r\nSODAQ LPS22HB Arduino Example\r\n");
	
	lps22hb.begin(0x5D);	// 

	if (lps22hb.whoAmI() == false)
	{
		DEBUG_STREAM.println("Error while retrieving WHO_AM_I byte...");
		while (1);
	}
}

void loop()
{
	DEBUG_STREAM.print("P=");
	DEBUG_STREAM.print(lps22hb.readPressure());
	DEBUG_STREAM.println(" mbar");

	delay(1000);
}

