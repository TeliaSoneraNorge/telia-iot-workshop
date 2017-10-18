#ifndef __sara_n2_h__
#define __sara_n2_h

#include "Arduino.h"

class SaraN2 {
  private:
    String server;
    String port;

    const int powerEnablePin = 7;

    void enableModulePower();
    void verifyModuleConnection();
    void sendCommand(String command);
    void verifyAutoconnect();
    void resetModule();
    void waitForNetworkConnection();
    void openSocket();
    void waitForResponse(String expectedResponse);
    String readResponse();
    String getNextResponse();

  public:
    SaraN2(String udpServer, String udpPort);
    void begin();
    void send(String message);

};

#endif
