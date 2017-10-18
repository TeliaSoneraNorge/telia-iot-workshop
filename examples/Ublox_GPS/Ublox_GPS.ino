#include <Arduino.h>
#include "Sodaq_UBlox_GPS.h"
#include "Sodaq_nbIOT.h"

#define MySerial        SERIAL_PORT_MONITOR
#define MODEM_STREAM Serial1

#define ARRAY_DIM(arr)  (sizeof(arr) / sizeof(arr[0]))

Sodaq_nbIOT nbiot;

// List of interval values to be used in loop()
// to measure how long it takes to get a fix.
uint32_t intervals[] = {

        // Do a few tests with 1 minute delay
        1UL * 60 * 1000,
        1UL * 60 * 1000,
        1UL * 60 * 1000,

        // Try a few longer delays
        2UL * 60 * 1000,
        2UL * 60 * 1000,
        5UL * 60 * 1000,
        5UL * 60 * 1000,

        // Slowly increase the delays
        15UL * 60 * 1000,
        30UL * 60 * 1000,
        1UL * 60 * 60 * 1000,
        3UL * 60 * 60 * 1000,
        4UL * 60 * 60 * 1000,
        8UL * 60 * 60 * 1000,
};
size_t interval_ix = 0;

void find_fix(uint32_t delay_until);
void do_flash_led(int pin);

void setup()
{
    delay(3000);
    while (!SerialUSB) {
        // Wait for USB to connect
    }

    MySerial.begin(57600);
    MODEM_STREAM.begin(nbiot.getDefaultBaudrate());

    nbiot.init(MODEM_STREAM, 7);
    nbiot.setDiag(MySerial);

    if (nbiot.connect("oceanconnect.t-mobile.nl", "172.16.14.20", "20416")) {
        MySerial.println("Connected succesfully!");
    }
    else {
        MySerial.println("Failed to connect!");
        return;
    }

    digitalWrite(13, HIGH);
    pinMode(13, OUTPUT);
    //digitalWrite(LED_GREEN, HIGH);
    //pinMode(LED_GREEN, OUTPUT);
    //digitalWrite(LED_BLUE, HIGH);
    //pinMode(LED_BLUE, OUTPUT);

    do_flash_led(13);
    //do_flash_led(LED_GREEN);
    //do_flash_led(LED_BLUE);

    MySerial.println("SODAQ NB-IoT SAM-M8Q test is starting ...");

    sodaq_gps.init(6);

    // This is for debugging to see more details, more messages
    // Use this in combination with setDiag()
    //sodaq_gps.setMinNumOfLines(10);

    // Uncomment the next line if you want to see the incoming $GPxxx messages
    sodaq_gps.setDiag(MySerial);

    // First time finding a fix
    find_fix(0);
}

void loop()
{
    uint32_t wait_ms = intervals[interval_ix];
    if (++interval_ix > ARRAY_DIM(intervals)) {
        interval_ix = 0;
    }
    find_fix(wait_ms);
}

/*!
 * Find a GPS fix, but first wait a while
 */
void find_fix(uint32_t delay_until)
{
    MySerial.println(String("delay ... ") + delay_until + String("ms"));
    delay(delay_until);

    uint32_t start = millis();
    uint32_t timeout = 900L * 1000;
    MySerial.println(String("waiting for fix ..., timeout=") + timeout + String("ms"));
    if (sodaq_gps.scan(false, timeout)) {
      String message = "";
        message +=(String(" time to find fix: ") + (millis() - start) + String("ms"));
        message +=(String(" datetime = ") + sodaq_gps.getDateTimeString());
        message +=(String(" lat = ") + String(sodaq_gps.getLat(), 7));
        message +=(String(" lon = ") + String(sodaq_gps.getLon(), 7));
        message +=(String(" num sats = ") + String(sodaq_gps.getNumberOfSatellites()));

        if (!nbiot.sendMessage(message)) {
          MySerial.println("Could not queue message!");
        }
    } else {
        MySerial.println("No Fix");
        if (!nbiot.sendMessage("No Fix")) {
          MySerial.println("Could not queue message!");
        }
    }
}

void do_flash_led(int pin)
{
    for (size_t i = 0; i < 2; ++i) {
        delay(100);
        digitalWrite(pin, LOW);
        delay(100);
        digitalWrite(pin, HIGH);
    }
}
