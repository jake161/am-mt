/*

Menus.h - Library for abstracting the drawing process (This doesn't work yet lol)

*/

#include "Arduino.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "SPI.h"
#include "Wire.h"
#include "Menus.h"

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 32    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Menus::Menus(int bu, int bm, int bd, bool egs, long debounce)
{
    curPos[0] = 120;
    curPos[1] = 10;
    interval = debounce;
    _but_u = bu;
    _but_m = bm;
    _but_d = bd;
    pinMode(_but_u, INPUT_PULLUP);
    pinMode(_but_m, INPUT_PULLUP);
    pinMode(_but_d, INPUT_PULLUP);
    EASTEREGGS = egs;

    // // Screen Begin
    // // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    // Serial.begin(9600);

    // if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    // {
    //     Serial.println(F("SSD1306 allocation failed"));
    //     for (;;)
    //         ; // Don't proceed, loop forever
    // }
}

void Menus::welcome(void)
{

    display.clearDisplay();

    display.setTextSize(2); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);

    if (EASTEREGGS == true)
    {
        display.setCursor(20, 0);
        display.println(F("Howdy :)"));
        display.display();
        delay(2000);

        display.setCursor(0, 0);
        display.clearDisplay();
        display.setTextSize(1);
        display.print(F("Damming Torpedoes"));
        display.display();
        delay(500);
        display.print(F("."));
        display.display();
        delay(500);
        display.print(F("."));
        display.display();
        delay(500);
        display.print(F("."));
        display.display();
        delay(500);

        display.setCursor(0, 0);
        display.clearDisplay();
        display.setTextSize(1);
        display.println(F("Opening Podbay Doors"));
        display.display();
        delay(500);
        display.print(F("."));
        display.display();
        delay(500);
        display.print(F("."));
        display.display();
        delay(500);
        display.print(F("."));
        display.display();
        delay(500);

        display.setCursor(0, 0);
        display.clearDisplay();
        display.setTextSize(1);
        display.println(F("Shall we play"));
        display.print(F("a game"));
        display.display();
        delay(700);
        display.print(F("?"));
        display.display();
        delay(500);
    }

    display.setCursor(35, 0);
    display.clearDisplay();
    display.setTextSize(2);
    display.println(F("AM-MT"));
    display.setTextSize(1);
    display.print(F(" Additive Manufctrng\n      Multi-Tool")); // Add a glitching text animation for EASTEREGGS
    display.display();
    delay(2000);
}

// Show the options menu
void Menus::menuMain(void)
{
    subMenuState = 0;
    Serial.println(subMenuState);
    display.clearDisplay();
    display.setCursor(43, 0);
    display.setTextSize(1);
    display.println(F("OPTIONS"));
    display.setCursor(0, 10);
    display.print(F("Tension Meter"));
    display.setCursor(0, 20);
    display.print(F("Ambient Temp"));
    display.setCursor(curPos[0], curPos[1]);
    display.print("<");
    display.display();
}

// Draw the Tension Meter Sub menu
void Menus::menuTension()
{
    subMenuState = 1;
    Serial.println(subMenuState);
    display.clearDisplay();
    display.setCursor(13, 0);
    display.print("Measured Tension:");
    display.setCursor(46, 20);
    display.print(String(tension(frequency, linDen, beltLen)) + "N"); // Place holder for analog input, add menu options to add lin_dens and belt length
    display.display();
}

// Draw the Ambient Temp Sub menu
void Menus::menuAmbient()
{
    subMenuState = 2;
    Serial.println(subMenuState);
    display.clearDisplay();
    display.setCursor(25, 0);
    display.print("Ambient Temp");
    display.setCursor(52, 20);
    display.print("nullC"); // Place holder for temp reading
    display.display();
}

void Menus::menuCon()
{

    switch (subMenuState)
    {
    case 0:
        // So here's the thing... this logic works well. It will need to be implemented for the other submenus... but I'm not sure how to effectively do that yet lol
        // Also... I don't think this method is extensible to overflow options. ie... don't base your choice off cursor position exactly?

        if ((tNow - tLast) >= interval)
        {
            // If sitting for too long, add goofy animation to EASTEREGGS
            tLast = tNow;
            if (digitalRead(_but_d) == LOW)
            {
                if (curPos[1] + 10 <= 20 && curPos[1] != 20)
                {
                    // Serial.println("UPDATING CURSOR POS @ X:" + String(curPos[0]) + " Y:" + String(curPos[1]));
                    curPos[1] = curPos[1] + 10;
                    // Serial.println("NEW CURSOR POS @ X:" + String(curPos[0]) + " Y:" + String(curPos[1]));
                    // Serial.println();
                    menuMain();
                }
            }

            if (digitalRead(_but_u) == LOW)
            {
                if (curPos[1] - 10 >= 10 && curPos[1] != 10)
                {
                    // Serial.println("UPDATING CURSOR POS @ X:" + String(curPos[0]) + " Y:" + String(curPos[1]));
                    curPos[1] = curPos[1] - 10;
                    // Serial.println("NEW CURSOR POS @ X:" + String(curPos[0]) + " Y:" + String(curPos[1]));
                    // Serial.println();
                    menuMain();
                }
            }

            if (digitalRead(_but_m) == LOW)
            {
                if (curPos[1] == 10)
                {
                    subMenuState = 1;
                }

                if (curPos[1] == 20)
                {
                    subMenuState = 2;
                }
            }
        }
        break;

    case 1: // I think I can steal the control logic from above and dump it into the other submenu cases. If thats the case, functions for each menu make sense.

        menuTension();

        if ((tNow - tLast) >= interval)
        {
            tLast = tNow;
            if (digitalRead(_but_m) == LOW) // Debounce this
            {
                menuMain(); // sends back to main menu
            }
        }
        break;

    case 2:

        menuAmbient();

        if ((tNow - tLast) >= interval)
        {
            tLast = tNow;
            if (digitalRead(_but_m) == LOW) // Debounce this
            {
                menuMain(); // sends back to main menu
            }
        }
        break;
    }
}

/*
The following functions perform arithmatic on sensor data
*/

// Calculates belt tension from frequency and linear density
float Menus::tension(float freq, float mu, float len)
{
    float tension = mu * pow(2.0 * len * freq, 2);

    return tension;
}