
#include <TFT_eSPI.h>
#include <SPI.h>
#include "display.h"
#include "gfxfont.h"


TFT_eSPI tft = TFT_eSPI();

Display::Display(bool serial)
{
  serialOutput = serial;
}

void Display::init()
{
  tft.begin();
  rotate(1);
  clear(WHITE);
  
  setFont(&FreeMonoBold9pt7b);
  setTextColor(BLACK);
  setCursor(0, 0);
}

void Display::setCursor(int16_t x, int16_t y)
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
}


void Display::clear(uint32_t color)
{
  tft.fillScreen(color);
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
}
