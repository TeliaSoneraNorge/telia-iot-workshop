/***************************************************************************
	This is a library for the HTS221 Humidity Temperature Sensor
		Originally written by speirano for SmartEverything
		Adjusted by Gregory Knauff of SODAQ for the NB-IoT shield
    Adjusted by Jan van Loenen to work on Sodaq Explorer and Arduino Leonardo
    
	Standard I2C-address is 0x5F.

***************************************************************************/

#include <Wire.h>
#include <Arduino.h>
#include "Sodaq_HTS221.h"

#if defined(ARDUINO_AVR_LEONARDO)
#define SerialOut Serial 
#define UBLOX Serial1

#elif defined(ARDUINO_SODAQ_EXPLORER)
#define SerialOut SerialUSB
#define UBLOX Serial

#elif defined(ARDUINO_ARCH_SAMD)
#define SerialOut SerialUSB
#define UBLOX Serial5

#else
#error "Please select a Sodaq ExpLoRer, Arduino Leonardo or add your board."
#endif

void setup() 
{
	delay(500);
	SerialOut.begin(9600);
  while (!SerialOut);             // Wait for serial monitor
	SerialOut.println("\r\nSODAQ HTS221 Arduino Example\r\n");

  delay(2000);

	if (hts221.begin() == false) 
	{
		SerialOut.println("Error while retrieving WHO_AM_I byte...");
			while (1);
	}
}


void loop() 
{
	SerialOut.print("Humidity   : ");
	SerialOut.print(hts221.readHumidity());
	SerialOut.println(" %");

	SerialOut.print("Temperature: ");
	SerialOut.print(hts221.readTemperature());
	SerialOut.println(" celsius");

	delay(1000);
}
