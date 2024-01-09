#ifndef _KELSIERWIFI_H_
#define _KELSIERWIFI_H_

#include "Arduino.h"
#include "display.h"
#include "WiFi.h"
// #include "esp_wifi_types.h"

class WiFiScan
{

public:
  WiFiScan();
  WiFiScan(Display* display);
  WiFiScan(const char* bssid, const char* password, Display* display);
  ~WiFiScan();

  void attachDisplay(Display* display);
  void init();
  
  bool connect();
  bool connect(const char* bssid, const char* password);
  void disconnect();

  void scan(bool showStrength = false, bool showChannel = false);
  void startServer(const char* bssid, const char* password);

  void setMode(wifi_mode_t type);
  void setAutoConnect(bool autoConnect);
  void setBSSID(const char* bssid);
  void setPassword(const char* password);

protected:
  bool autoConnect;
  char *bssid;
  char *password;
  Display* display;

};

#endif