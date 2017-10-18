
#include "sara-n2.h"

#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT Serial.println
#else
#define DEBUG_PRINT
#endif

bool stringContains(String text, String searchTerm);

SaraN2::SaraN2(String udpServer, String udpPort) {
  server = udpServer;
  port = udpPort;
}

void SaraN2::begin() {
  enableModulePower();

  Serial1.begin(9600);

  int timeout = 5000;
  while (timeout--) {
      if (readResponse() == "OK") {
        break;
      }
      delay(1);
  }

  verifyModuleConnection();
  verifyAutoconnect();
  waitForNetworkConnection();
  openSocket();
}

void SaraN2::enableModulePower() {
  pinMode(powerEnablePin, OUTPUT);
  digitalWrite(powerEnablePin, HIGH);
}

void SaraN2::verifyModuleConnection() {
  do {
    sendCommand("AT");
  } while(getNextResponse() != "OK");
}

void SaraN2::sendCommand(String command) {
  DEBUG_PRINT("> " + command);
  Serial1.println(command);
}

void SaraN2::verifyAutoconnect() {
  sendCommand("AT+NCONFIG?");
  String response = "";
  bool autoconnect = false;
  do {
    response = getNextResponse();
    if (stringContains(response, "AUTOCONNECT,TRUE")) {
      autoconnect = true;
    }
  } while (response != "OK");

  if (autoconnect == false) {
    sendCommand("AT+NCONFIG=AUTOCONNECT,TRUE");
    waitForResponse("OK");
    resetModule();
  }
}

void SaraN2::resetModule() {
  sendCommand("AT+NRB");
  waitForResponse("OK");
}

void SaraN2::waitForResponse(String expectedResponse) {
  while(readResponse().indexOf(expectedResponse) == -1){
    delay(0);
  }
}

String SaraN2::readResponse() {
  if (Serial1.available()) {
    String response = "";
    do {
      response = Serial1.readStringUntil('\n');
      response.trim();
    } while (response == "");
    DEBUG_PRINT("> " + response);
    return response;
  }
  else {
    return "";
  }
}

String SaraN2::getNextResponse() {
  while (!Serial1.available()) {
    delay(0);
  }
  return readResponse();
}

void SaraN2::waitForNetworkConnection() {
  sendCommand("AT+CEREG=1");
  waitForResponse("OK");

  sendCommand("AT+CEREG?");
  String cereg = getNextResponse();
  waitForResponse("OK");
  if (stringContains(cereg, "+CEREG:1,1")) {
    return;
  }
  waitForResponse("+CEREG:1");
}

void SaraN2::openSocket() {
  sendCommand("AT+NSOCL=0");
  getNextResponse();
  sendCommand("AT+NSOCR=DGRAM,17,12345,1");
  waitForResponse("OK");
}

void SaraN2::send(String message) {

  Serial1.print("AT+NSOST=0,");
  Serial1.print(server);
  Serial1.print(",");
  Serial1.print(port);
  Serial1.print(",");
  Serial1.print(message.length());
  Serial1.print(",");
  for (uint16_t i = 0; i < message.length(); i++) {
    Serial1.print(message[i], HEX);
  }
  Serial1.println();
  waitForResponse("OK");
}

// Local helper functions

bool stringContains(String text, String searchTerm) {
  return text.indexOf(searchTerm) != -1;
}
