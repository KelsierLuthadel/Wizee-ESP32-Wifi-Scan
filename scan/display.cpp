
#include <TFT_eSPI.h>
#include <SPI.h>
#include "display.h"
#include "gfxfont.h"
#include "Free_Fonts.h"


TFT_eSPI tft = TFT_eSPI();

Display::Display(bool serial)
{
  serialOutput = serial;
  xPos = 0;
  yPos = 0;
  startXPos = 0;
  startYPos = 0;
}

void Display::init(uint16_t xPos, uint16_t yPos)
{
  startXPos = xPos;
  startYPos = yPos;
  
  tft.begin();
  rotate(1);
  setFont(FF0);
  setScreenColor(WHITE);
  clear();
  setTextColor(BLACK);
  setCursor(xPos, xPos);
}

void Display::init()
{
  init(0, 0);
}

void Display::setCursor(uint16_t x, uint16_t y)
{
  this->xPos = x;
  this->yPos = y;
  tft.setCursor(x, y); 
}

void Display::rotate(uint8_t r)
{
  tft.setRotation(r);
}

void Display::clear()
{
  tft.fillScreen(this->color);
  setCursor(startXPos, startYPos);
}


void Display::clear(uint32_t color)
{
  tft.fillScreen(color);
  setCursor(startXPos, startYPos);
}

void Display::setScreenColor(uint16_t color)
{
  this->color = color;
}

void Display::setFont(const GFXfont *font)
{
   tft.setFreeFont(font); 
}

void Display::setTextSize(uint8_t size)
{
   tft.setTextSize(size);
}

void Display::setTextColor(uint16_t fg_color)
{
  tft.setTextColor(fg_color);
}

void Display::setTextColor(uint16_t fg_color, uint16_t bg_color, bool bgfill)
{
  tft.setTextColor(fg_color, bg_color, bgfill);
}

void Display::output(int32_t x, int32_t y, const String& value)
{
  tft.drawString(value, x, y);
  
  if (serialOutput) {
    Serial.println(value);
  }
}

void Display::print(const String& value)
{
  tft.print(value);
  
  if (serialOutput) {
    Serial.print(value);
  }
}

void Display::scr(const String& value)
{
  tft.println(value);

}

void Display::println(const String& value)
{
  tft.println(value);

  if (serialOutput) {
    Serial.println(value);
  }
}

void Display::print(int32_t value)
{
  tft.print(value);
  
  if (serialOutput) {
    Serial.print(value);
  }
}

void Display::println(int32_t value)
{
  tft.println(value);

  if (serialOutput) {
    Serial.println(value);
  }
}
