#include <Arduino.h>
#include <Accel.h>
#include <Mic.h>
#include <Screen.h>
#include <Tension.h>

// Flags
// #define EASTEREGGS
// #define DEBUG

// Button Inputs
static const uint8_t but_u = D8;
static const uint8_t but_m = D9;
static const uint8_t but_d = D10;

// Debouncing
unsigned long tNow, tLast;
unsigned long interval = 150;

// Sub-Menu Logic
int subMenuState = 0;
int lastButtonState_d = HIGH;
int lastButtonState_u = HIGH;
int lastButtonState_m = HIGH;

// Prototypes
void menuTension();
void menuAmbient();
void menuCon();

void setup()
{
  // Serial Begin
  #ifdef DEBUG
    Serial.begin(9600);
  #endif

  // Mic Setup
  setupMic();

  // Button Inputs
  pinMode(but_u, INPUT_PULLUP);
  pinMode(but_m, INPUT_PULLUP);
  pinMode(but_d, INPUT_PULLUP);

  // Accelerometer Begin
  setupAccel();

  // Screen Begin
  screenSetup();

  // Call menu welcom screen
  welcome();
  menuMain();
}

void loop(){

  tNow = millis();
  menuCon();
}

/*
The following functions are responsible for drawing the menus and setting their state
*/

// Draw the Tension Meter Sub menu
void menuTension(){
    subMenuState = 1;
    //Serial.println(subMenuState);
    display.clearDisplay();
    display.setCursor(13, 0);
    display.print("Measured Tension");
    display.setCursor(46, 12);
    float freq=getDominantFrequency();
    float ten=tension(freq,0.0083,0.350);
    if (ten>1000){
      display.setCursor(10, 12);
      display.print("Freq out of Range");
    }
    else {
      //Calculate tension from analog audio input
      #ifdef DEBUG
        Serial.println(ten);
      #endif

      display.print(String(ten)+"N");
      display.setCursor(46, 20);
      display.print(String(freq)+"Hz");

    }
     
    display.display();
}

// Draw the Ambient Temp Sub menu
void menuAccel(){
    subMenuState = 2;
    //Serial.println(subMenuState);
    display.clearDisplay();
    display.setCursor(25, 0);
    display.print("Acceleration");
    if ((tNow - tLast) >= interval){
      getAccelCorrected();
    }

    #ifdef DEBUG
      Serial.print(accelXg);
      Serial.print(" ");
      Serial.print(accelYg);
      Serial.print(" ");
      Serial.println(accelZg);
    #endif

    display.setCursor(0, 12);
    display.print("X:"+String(abs(accelXg))+"Gs"); // Get acceleration values from MPU6050 in mm/s^2
    display.setCursor(60, 12);
    display.print("Y:"+String(abs(accelYg))+"Gs");
    display.setCursor(0, 25);
    display.print("Z:"+String(abs(accelZg))+"Gs");
    display.display();
}

// Sub Menu Control Logic, handles navigating and re-drawing the menus
void menuCon(){

  switch (subMenuState){
  case 0:
    if ((tNow - tLast) >= interval){
      int buttonState_d = digitalRead(but_d);
      int buttonState_u = digitalRead(but_u);
      int buttonState_m = digitalRead(but_m);

      if (buttonState_d == lastButtonState_d && buttonState_u == lastButtonState_u && buttonState_m == lastButtonState_m){
        // The button state hasn't changed, so don't proceed
        return;
      }

      tLast = tNow;

      if (buttonState_d == LOW){
        if (curPos[1] + 10 <= 20 && curPos[1] != 20){
          curPos[1] = curPos[1] + 10;
          menuMain();
        }
      }

      if (buttonState_u == LOW){
        if (curPos[1] - 10 >= 10 && curPos[1] != 10){
          curPos[1] = curPos[1] - 10;
          menuMain();
        }
      }

      if (buttonState_m == LOW){
        if (curPos[1] == 10){
          subMenuState = 1;
        }

        if (curPos[1] == 20){
          subMenuState = 2;
        }
      }

      lastButtonState_d = buttonState_d;
      lastButtonState_u = buttonState_u;
      lastButtonState_m = buttonState_m;
    }
    break;

  case 1: // I think I can steal the control logic from above and dump it into the other submenu cases. If thats the case, functions for each menu make sense.
    
    menuTension();

    if ((tNow - tLast) >= interval){
      int buttonState = digitalRead(but_m);
      if (buttonState == lastButtonState_m){
        return;
      }

      tLast = tNow;
      lastButtonState_m = buttonState;
      if (digitalRead(but_m) == LOW){
        menuMain(); // sends back to main menu
      }
    }
    break;

  case 2:

    menuAccel();

    if ((tNow - tLast) >= interval){
      int buttonState = digitalRead(but_m);
      if (buttonState == lastButtonState_m){
        return;
      }

      tLast = tNow;
      lastButtonState_m = buttonState;
      if (digitalRead(but_m) == LOW){
        menuMain(); // sends back to main menu
      }
    }
    break;
  }
}