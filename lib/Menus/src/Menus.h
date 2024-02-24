/*

Menus.h - Library for simplifying local servo commands

*/
#ifndef Menus_h
#define Menus_h

#include "Arduino.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

class Menus
{
public:
    Menus(int SCREEN_WIDTH, int SCREEN_HEIGHT, int OLED_RESET, int SCREEN_ADDRESS, int bu, int bm, int bd);

public:
    void welcome(void);
    void menuMain(void);
    void menuTension(void);
    void menuAmbient(void);
    void menuCon(void);

private:
    int curPos[2];
    int _but_u;
    int _but_m;
    int _but_d;

};

#endif