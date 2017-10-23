
#include "sara-n2.h"

#if defined(ARDUINO_AVR_LEONARDO)
#define DebugSerial Serial 
#define SaraSerial Serial1

#elif defined(ARDUINO_ARCH_SAMD)
#define DebugSerial SerialUSB
#define SaraSerial Serial5

#else
#error "Current board is not supported."
#endif

//#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT DebugSerial.println
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

  SaraSerial.begin(9600);

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
  SaraSerial.println(command);
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
  if (SaraSerial.available()) {
    String response = "";
    do {
      response = SaraSerial.readStringUntil('\n');
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
  while (!SaraSerial.available()) {
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

  SaraSerial.print("AT+NSOST=0,");
  SaraSerial.print(server);
  SaraSerial.print(",");
  SaraSerial.print(port);
  SaraSerial.print(",");
  SaraSerial.print(message.length());
  SaraSerial.print(",");
  for (uint16_t i = 0; i < message.length(); i++) {
    SaraSerial.print(message[i], HEX);
  }
  SaraSerial.println();
  waitForResponse("OK");
}

// Local helper functions

bool stringContains(String text, String searchTerm) {
  return text.indexOf(searchTerm) != -1;
}
