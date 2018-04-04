// From: http://support.sodaq.com/sodaq-one/at/
// Ublox manuals: https://www.u-blox.com/en/product/sara-n2-series

#include "Arduino.h"

#if defined(ARDUINO_AVR_LEONARDO)
#define USB Serial 
#define UBLOX Serial1

#elif defined(ARDUINO_SODAQ_EXPLORER)
#define USB SerialUSB
#define UBLOX Serial

#elif defined(ARDUINO_SAM_ZERO)
#define USB SerialUSB
#define UBLOX Serial1

#else
#error "Please select a Sodaq ExpLoRer, Arduino Leonardo or add your board."
#endif

// Pin to turn on/off the nb-iot module
#define powerPin 7 
unsigned long baud = 9600;  //start at 9600 allow the USB port to change the Baudrate


void setup() 
{
  // Turn the nb-iot module on
  pinMode(powerPin, OUTPUT); 
  digitalWrite(powerPin, HIGH);

  // Start communication
  USB.begin(baud);
  UBLOX.begin(baud);
}

// Forward every message to the other serial
void loop() 
{
  while (USB.available())
  {
    uint8_t c = USB.read();
    UBLOX.write(c);
  }

  while (UBLOX.available())
  {     
    USB.write(UBLOX.read());
  }

  // check if the USB virtual serial wants a new baud rate
  if (USB.baud() != baud) {
    baud = USB.baud();
       UBLOX.begin(baud);
  }
}
