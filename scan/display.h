#ifndef _KELSIER_DISPLAY_H_
#define _KELSIER_DISPLAY_H_

#include "gfxfont.h"

#define BLACK       0x0000      /*   0,   0,   0 */
#define NAVY        0x000F      /*   0,   0, 128 */
#define DARKGREEN   0x03E0      /*   0, 128,   0 */
#define DARKCYAN    0x03EF      /*   0, 128, 128 */
#define MAROON      0x7800      /* 128,   0,   0 */
#define PURPLE      0x780F      /* 128,   0, 128 */
#define OLIVE       0x7BE0      /* 128, 128,   0 */
#define LIGHTGREY   0xD69A      /* 211, 211, 211 */
#define DARKGREY    0x7BEF      /* 128, 128, 128 */
#define BLUE        0x001F      /*   0,   0, 255 */
#define GREEN       0x07E0      /*   0, 255,   0 */
#define CYAN        0x07FF      /*   0, 255, 255 */
#define RED         0xF800      /* 255,   0,   0 */
#define MAGENTA     0xF81F      /* 255,   0, 255 */
#define YELLOW      0xFFE0      /* 255, 255,   0 */
#define WHITE       0xFFFF      /* 255, 255, 255 */
#define ORANGE      0xFDA0      /* 255, 180,   0 */
#define GREENYELLOW 0xB7E0      /* 180, 255,   0 */
#define PINK        0xFE19      /* 255, 192, 203 */ //Lighter pink, was 0xFC9F
#define BROWN       0x9A60      /* 150,  75,   0 */
#define GOLD        0xFEA0      /* 255, 215,   0 */
#define SILVER      0xC618      /* 192, 192, 192 */
#define SKYBLUE     0x867D      /* 135, 206, 235 */
#define VIOLET      0x915C      /* 180,  46, 226 */

class Display {

public:
  Display(bool serial = false);
  void init();
  void rotate(uint8_t r); // Set the display image orientation to 0, 1, 2 or 3
  void clear();
  void clear(uint32_t color);

  void setScreenColor(uint16_t color);
  void setCursor(int16_t x, int16_t y); 
  void setFont(const GFXfont *f = NULL);
  void setTextSize(uint8_t size);
  void setTextColor(uint16_t fg_color);
  void setTextColor(uint16_t fg_color, uint16_t bg_color, bool bgfill = false);

  void output(int32_t x, int32_t y, const String& value);

private:
  bool serialOutput;
  uint16_t color;
  int16_t xPos;
  int16_t yPos;
};

#endif
