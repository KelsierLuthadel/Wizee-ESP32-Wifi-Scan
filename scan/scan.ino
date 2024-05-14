/**
Board: ESP32 Dev Module
Flash Mode: QIO
Flash Size: 4MB
Parition Scheme: Huge App 
PSRAM: Enabled

*/


#include "display.h"
#include "scan-wifi.h"
#include "WiFi.h"

WiFiScan wifi;
Display display(true);


void setup() {
  delay(100);
  Serial.begin(115200);
  display.init();
  delay(100);
  
  wifi.attachDisplay(&display);
  wifi.startServer("Stressco free WiFi", "");
}

void loop() {
  wifi.scan(true, true);
}
