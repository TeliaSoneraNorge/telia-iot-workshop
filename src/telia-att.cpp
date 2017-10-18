
#include "telia-att.h"

TeliaATT::TeliaATT(
  String deviceId,
  String token,
  String server,
  String port)
  :sara(server, port) {
  this->deviceId = deviceId;
  this->token = token;
}

void TeliaATT::begin() {
  sara.begin();
}

void TeliaATT::send(String asset, int value){
  sendAssetPayload(asset, String(value));
}

void TeliaATT::send(String asset, float value){
  sendAssetPayload(asset, String(value));
}

void TeliaATT::send(String asset, double value){
  sendAssetPayload(asset, String(value));
}

void TeliaATT::send(String asset, bool value){
  if (value == true) {
    sendAssetPayload(asset, String("true"));
  }
  else {
    sendAssetPayload(asset, String("false"));
  }
}

void TeliaATT::send(String asset, String value) {
  sendAssetPayload(asset, String("\"" + value + "\""));
}

void TeliaATT::sendAssetPayload(String asset, String value) {
  String payload;
  payload += "{\"deviceId\":\"" + deviceId + "\",";
  payload += "\"token\":\"" + token + "\",";
  payload += "\"asset\":\"" + asset + "\",";
  payload += "\"payload\":{\"value\":" + value + "}}";
  sara.send(payload);
}
