#include "telia-att.h"

const String deviceId = "<AllThingsTalk device ID>";
const String token = "<AllThingsTalk token>";
const String server = "<Telia NB-IoT server IP>";
const String port = "<Telia NB-IoT server port>";

TeliaATT Telia(deviceId, token, server, port);
int counterValue = 0;

void setup() {
  SerialUSB.begin(9600);
  delay(2000);
  Telia.begin();
}

void loop() {
  Telia.send("counter", counterValue);
  SerialUSB.println(counterValue);
  counterValue++;
  delay(2000);
}
