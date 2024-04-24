#include "Screen.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int curPos[2] = {120, 10};

void screenSetup(){
    // Screen Begin
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){ // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever, if this breaks move semicolon down a line
  }
}

void welcome()
{
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);

  #ifdef EASTEREGGS
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
#endif

  display.setCursor(35, 0);
  display.clearDisplay();
  display.setTextSize(2);
  display.println(F("AM-MT"));
  display.setTextSize(1);
  display.print(F(" Additive Manufctrng\n      Multi-Tool")); // Add a glitching text animation for EASTEREGGS
  display.display();
  delay(2000);
}

/*
The following functions are responsible for drawing the menus and setting their state
*/


// Show the options menu
void menuMain()
{
  subMenuState = 0;
  //Serial.println(subMenuState);
  display.clearDisplay();
  display.setCursor(43, 0);
  display.setTextSize(1);
  display.println(F("OPTIONS"));
  display.setCursor(0, 10);
  display.print(F("Tension Meter"));
  display.setCursor(0, 20);
  display.print(F("Acceleration"));
  display.setCursor(curPos[0], curPos[1]);
  display.print("<");
  display.display();
}