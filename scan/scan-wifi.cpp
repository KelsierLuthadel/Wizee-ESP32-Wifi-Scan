#include "scan-wifi.h"
#include "Arduino.h"
#include "WiFi.h"

WiFiScan::WiFiScan()
{
  this->bssid = NULL;
  this->password = NULL;

  this->autoConnect = false;
  this->display = NULL;
}

WiFiScan::WiFiScan(Display* display)
{
  this->bssid = NULL;
  this->password = NULL;

  this->autoConnect = false;
  this->display = display;
}

WiFiScan::WiFiScan(const char* bssid, const char* password, Display* display)
{
  this->setBSSID(bssid);
  this->setPassword(password);

  this->autoConnect = false;
  this->display = display;
}

WiFiScan::~WiFiScan()
{
  if (NULL != this->bssid)
  {
    delete []this->bssid; 
  }
  
  if (NULL != this->password)
  {
    delete []this->password; 
  }
}

void WiFiScan::attachDisplay(Display* display)
{
  this->display = display;
}

void WiFiScan::init()
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
}

bool WiFiScan::connect()
{
  WiFi.setAutoConnect(this->autoConnect);
	WiFi.begin(this->bssid,this->password);
	delay(100);

  byte count = 0;
	while(WiFi.status() != WL_CONNECTED && count < 10)
	{ 
		count ++;
		delay(500);
    display->output(0, 0, "Connecting...");
	}

	if(WiFi.status() == WL_CONNECTED)
	{
		display->output(0, 0, "Connecting...OK.");
	}
	else
	{
    display->clear();
    display->output(0, 0, "Connecting...Failed");
    return false;
	}

	display->output(0, 10, "WIFI Setup done");
	delay(500);
  display->clear();
  return true;
}

bool WiFiScan::connect(const char* bssid, const char* password)
{
  this->setBSSID(bssid);
  this->setPassword(password);

  return this->connect();
}

void WiFiScan::disconnect()
{
  WiFi.disconnect(true);
  delay(100);
}

void WiFiScan::scan(bool showStrength, bool showChannel)
{
  int networksFound = WiFi.scanNetworks();
  display->clear(WHITE);

  if (networksFound == 0)
  {
    display->println("no network found");
  }
  else
  {
    display->scr("Networks: " + (String)networksFound);

    int y = 1;

    for (int i = 0; i < networksFound; ++i) 
    {
      if (y > 16) 
      {
        delay(3000);
        display->clear();
        display->scr("Networks: " + (String)networksFound);
        y=0;
      }

      unsigned int position = i+1;
      
      String ssid = (String)WiFi.SSID(i).substring(0,15);
      String open = (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "  ": " *";
      String network = (String)position + ":" + ssid ;

      if (showChannel)
      {
        network += " CH: " + (String)(WiFi.channel(i));
      }

      if (showStrength)
      {
        network += " (" + (String)(WiFi.RSSI(i)) + ")";
      }

      network += open;

      display->scr(network);

      y++;
    }

		delay(3000);
	}
}

void handler(WiFiEvent_t event, WiFiEventInfo_t info)
{
  // Serial.printf("[WiFi-event] event: %d\n", event);
    switch (event) {
        case ARDUINO_EVENT_WIFI_READY: 
            Serial.println("WiFi interface ready");
            break;
        case ARDUINO_EVENT_WIFI_SCAN_DONE:
            // Serial.println("Completed scan for access points");
            break;
        case ARDUINO_EVENT_WIFI_STA_START:
            Serial.println("WiFi client started");
            break;
        case ARDUINO_EVENT_WIFI_STA_STOP:
            Serial.println("WiFi clients stopped");
            break;
        case ARDUINO_EVENT_WIFI_STA_CONNECTED:
            Serial.println("Connected to access point");
            break;
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            Serial.println("Disconnected from WiFi access point");
            break;
        case ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE:
            Serial.println("Authentication mode of access point has changed");
            break;
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            Serial.print("Obtained IP address: ");
            Serial.println(WiFi.localIP());
            break;
        case ARDUINO_EVENT_WIFI_STA_LOST_IP:
            Serial.println("Lost IP address and IP address is reset to 0");
            break;
        case ARDUINO_EVENT_WPS_ER_SUCCESS:
            Serial.println("WiFi Protected Setup (WPS): succeeded in enrollee mode");
            break;
        case ARDUINO_EVENT_WPS_ER_FAILED:
            Serial.println("WiFi Protected Setup (WPS): failed in enrollee mode");
            break;
        case ARDUINO_EVENT_WPS_ER_TIMEOUT:
            Serial.println("WiFi Protected Setup (WPS): timeout in enrollee mode");
            break;
        case ARDUINO_EVENT_WPS_ER_PIN:
            Serial.println("WiFi Protected Setup (WPS): pin code in enrollee mode");
            break;
        case ARDUINO_EVENT_WIFI_AP_START:
            Serial.println("WiFi access point started");
            break;
        case ARDUINO_EVENT_WIFI_AP_STOP:
            Serial.println("WiFi access point  stopped");
            break;
        case ARDUINO_EVENT_WIFI_AP_STACONNECTED:
            Serial.println("Client connected");
            break;
        case ARDUINO_EVENT_WIFI_AP_STADISCONNECTED:
            Serial.println("Client disconnected");
            break;
        case ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED:
            Serial.println("Assigned IP address to client");
            break;
        case ARDUINO_EVENT_WIFI_AP_PROBEREQRECVED:
            Serial.println("Received probe request");
            break;
        case ARDUINO_EVENT_WIFI_AP_GOT_IP6:
            Serial.println("AP IPv6 is preferred");
            break;
        case ARDUINO_EVENT_WIFI_STA_GOT_IP6:
            Serial.println("STA IPv6 is preferred");
            break;
        case ARDUINO_EVENT_ETH_GOT_IP6:
            Serial.println("Ethernet IPv6 is preferred");
            break;
        case ARDUINO_EVENT_ETH_START:
            Serial.println("Ethernet started");
            break;
        case ARDUINO_EVENT_ETH_STOP:
            Serial.println("Ethernet stopped");
            break;
        case ARDUINO_EVENT_ETH_CONNECTED:
            Serial.println("Ethernet connected");
            break;
        case ARDUINO_EVENT_ETH_DISCONNECTED:
            Serial.println("Ethernet disconnected");
            break;
        case ARDUINO_EVENT_ETH_GOT_IP:
            Serial.println("Obtained IP address");
            break;
        default: break;
    }
}


void WiFiScan::setMode(wifi_mode_t type)
{
  WiFi.mode(type);
}

void WiFiScan::setAutoConnect(bool autoConnect)
{
  this->autoConnect = autoConnect;
}

void WiFiScan::setBSSID(const char* bssid)
{
  if(bssid && *bssid != 0x00 && strlen(bssid) <= 32) {
    if (NULL != this->bssid)
    {
      delete []this->bssid;
    }

    this->bssid = new char[strlen(bssid) + 1];
    strncpy(this->bssid, bssid, 32);
  }
}

void WiFiScan::setPassword(const char* password)
{
  if(password && strlen(password) <= 64) {
    if (NULL != this->password)
    {
        delete []this->password;
    }

    this->password = new char[strlen(password) + 1];
    strncpy(this->password, password, 64);
  }
}

void WiFiScan::WiFiScan::startServer(const char* bssid, const char* password)
{
  
  display->println("Starting server");
  
  WiFi.softAP(bssid, password);
  IPAddress myIP = WiFi.softAPIP();
  
  display->println(AP IP address: " + myIP.toString());
  WiFi.onEvent(handler);
}
