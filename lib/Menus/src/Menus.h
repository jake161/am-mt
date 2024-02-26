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
    Menus(int bu, int bm, int bd, bool egs,long debounce);

public:
    void welcome(void);
    void menuMain(void);
    void menuTension(void);
    void menuAmbient(void);
    void menuCon(void);
    float tension(float, float, float);
    int subMenuState;
    int curPos[2];
    unsigned long tNow;
    float frequency,linDen,beltLen;

private:
    int _but_u;
    int _but_m;
    int _but_d;
    bool EASTEREGGS;
    unsigned long tLast;
    unsigned long interval;

};

// class test
// {
// public:
//     int hello;
// };

#endif