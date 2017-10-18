#ifndef _telia_att_h_
#define _telia_att_h_

#include "Arduino.h"
#include "sara-n2.h"


class TeliaATT {
  private:
    String deviceId;
    String token;
    SaraN2 sara;
    void sendAssetPayload(String asset, String Payload);

  public:
    TeliaATT(String deviceId, String token, String server, String port);
    void begin();
    void send(String asset, int value);
    void send(String asset, float value);
    void send(String asset, double value);
    void send(String asset, bool value);
    void send(String asset, String value);
};

#endif
