// I2C interface by default
//
#include "Wire.h"
#include "SparkFunIMU.h"
#include "SparkFunLSM303C.h"
#include "LSM303CTypes.h"

// #define DEBUG 1 in SparkFunLSM303C.h turns on debugging statements.
// Redefine to 0 to turn them off.

LSM303C myIMU;

void setup()
{
  SerialUSB.begin(9600);
  if (myIMU.begin() != IMU_SUCCESS)
  {
    SerialUSB.println("Failed setup.");
    while(1);
  }
}

void loop()
{
  //Get all parameters
  SerialUSB.print("\nAccelerometer:\n");
  SerialUSB.print(" X = ");
  SerialUSB.println(myIMU.readAccelX(), 4);
  SerialUSB.print(" Y = ");
  SerialUSB.println(myIMU.readAccelY(), 4);
  SerialUSB.print(" Z = ");
  SerialUSB.println(myIMU.readAccelZ(), 4);

  // Not supported by hardware, so will return NAN
  SerialUSB.print("\nGyroscope:\n");
  SerialUSB.print(" X = ");
  SerialUSB.println(myIMU.readGyroX(), 4);
  SerialUSB.print(" Y = ");
  SerialUSB.println(myIMU.readGyroY(), 4);
  SerialUSB.print(" Z = ");
  SerialUSB.println(myIMU.readGyroZ(), 4);

  SerialUSB.print("\nMagnetometer:\n");
  SerialUSB.print(" X = ");
  SerialUSB.println(myIMU.readMagX(), 4);
  SerialUSB.print(" Y = ");
  SerialUSB.println(myIMU.readMagY(), 4);
  SerialUSB.print(" Z = ");
  SerialUSB.println(myIMU.readMagZ(), 4);

  SerialUSB.print("\nThermometer:\n");
  SerialUSB.print(" Degrees C = ");
  SerialUSB.println(myIMU.readTempC(), 4);
  SerialUSB.print(" Degrees F = ");
  SerialUSB.println(myIMU.readTempF(), 4);
  
  delay(1000);
}
