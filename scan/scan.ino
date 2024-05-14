#include "scan-wifi.h"
#include "WiFi.h"
#include "display.h"

Display display(true);
WiFiScan *scanner;

int io1 = 25;
int io2 = 23;

void setup() {
  pinMode(io1, INPUT);
  pinMode(io2, INPUT);
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
  int  x = analogRead(io1);
  int  y = analogRead(io2);
  int xMap = map(x, 0,1023, 0, 7);
  int yMap = map(y,0,1023,7,0);

    Serial.println(xMap);
  Serial.println(yMap);
 // scanner->scan(true, true);
}

