/*

Menus.h - Library for abstracting the drawing process (This doesn't work yet lol)

*/

#include "Arduino.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Menus.h"

Menus::Menus(int SCREEN_WIDTH, int SCREEN_HEIGHT, int OLED_RESET, int SCREEN_ADDRESS, int bu, int bm, int bd)
{
    Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    curPos[0]=120;
    curPos[1]=10;
    _but_u=bu;
    _but_m=bm;
    _but_d=bd;
}