#include "telia-att.h"

const String deviceId = "<AllThingsTalk device ID>";
const String token = "<AllThingsTalk token>";
const String server = "<Telia NB-IoT server IP>";
const String port = "<Telia NB-IoT server port>";

TeliaATT telia(deviceId, token, server, port);
int counterValue = 0;

void setup() {
  Serial.begin(9600);
  delay(2000);
  telia.begin();
}

void loop() {
  telia.send("counter", counterValue);
  Serial.println(counterValue);
  counterValue++;
  delay(2000);
}
