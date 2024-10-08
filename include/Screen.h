#ifndef SCREEN_H
#define SCREEN_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

extern Adafruit_SSD1306 display;
extern int subMenuState;
extern int curPos[2];


void welcome(void);
void menuMain(void);
void screenSetup(void);

#endif