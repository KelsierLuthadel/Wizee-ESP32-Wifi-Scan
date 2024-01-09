#include "scan-wifi.h"
#include "WiFi.h"
#include "display.h"

Display display(true);
WiFiScan *scanner;

void setup() {
  
  scanner = new WiFiScan(&display);
  
  scanner->init();
  scanner->startServer("Starfucks Coffee", "");
  
  delay(100);
  Serial.begin(115200);
  display.init(8, 8);

  Serial.println("Setup done");
  display.output(8, 8, "Scanning");
  
}

void loop() {
  scanner->scan(true, true);
}

