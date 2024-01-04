#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

#include "Free_Fonts.h" // Include the header file attached to this sketch
#include "WiFi.h"

TFT_eSPI tft = TFT_eSPI();                   // Invoke custom library with default width and height
int xpos =  0;
int ypos = 40;

void setup() {
  
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.begin(115200);
  tft.begin();
  tft.setRotation(1);

  Serial.println("Setup done");
  
  // tft.setTextFont(GLCD);     // Select the orginal small GLCD font by using NULL or GLCD
  tft.setFreeFont(FS9); 
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
 
  tft.setCursor(xpos, ypos);    // Set cursor near top left corner of screen
  outputln("scan start");
}

void loop() {
  tft.setCursor(xpos, ypos);    // Set cursor near top left corner of screen
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  tft.fillScreen(TFT_BLACK);

  if (n == 0) {
    outputln("no networks found");
  } else {
    output(n);
    outputln(" networks found");
    outputln("");

    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      output(i + 1);
      output(": ");
      output(WiFi.SSID(i));
      output(" (");
      output(WiFi.RSSI(i));
      output(")");
      outputln((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      delay(10);
    }
  }

  // Wait a bit before scanning again
  delay(5000);
}

void output(String string)
{
  Serial.print(string);
  tft.print(string);
}

void outputln(String string)
{
  Serial.println(string);
  tft.println(string);
}

void output(int n)
{
  Serial.print(n);
  tft.print(n); 
}

void outputln(int n)
{
  Serial.print(n);
  tft.print(n); 
}




