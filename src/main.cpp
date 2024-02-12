#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP280.h>

// Screen Setup

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 32    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Temp BMP280 Setup

Adafruit_BMP280 bmp; // I2C

// Mic Setup

static const uint8_t micPin = A2;

// Button Inputs

static const uint8_t but_u = D8;
static const uint8_t but_m = D9;
static const uint8_t but_d = D10;

int curPos[2] = {120, 10};

unsigned long tNow, tLast;
unsigned long interval = 75;

// Flags
#define EASTEREGGS false // Want a fun little suprise?
#define BMP_DEBUG false

// Prototypes

void welcome(void);
void menu(void);
void updateCur(void);
float tension(float, float, float);

void setup()
{
  Serial.begin(9600);

  pinMode(but_u, INPUT_PULLUP);
  pinMode(but_m, INPUT_PULLUP);
  pinMode(but_d, INPUT_PULLUP);

  if (BMP_DEBUG == true)
  {
    while (!Serial)
      delay(100); // wait for native usb, not sure if I'll keep this in final implementation
    Serial.println(F("BMP280 test"));
  }

  // Screen Begin
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  if (BMP_DEBUG == true)
  {
    // BMP280 Begin
    unsigned status;
    // status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
    status = bmp.begin();
    if (!status)
    {
      Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                       "try a different address!"));
      Serial.print("SensorID was: 0x");
      Serial.println(bmp.sensorID(), 16);
      Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
      Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
      Serial.print("        ID of 0x60 represents a BME 280.\n");
      Serial.print("        ID of 0x61 represents a BME 680.\n");
      while (1)
        delay(10);
    }

    /* Default settings from datasheet. */
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  }

  welcome();
  menu();
}

void loop()
{
  tNow = millis();
  updateCur();
}

// Welcome Message
void welcome()
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
void menu()
{
  display.setCursor(43, 0);
  display.clearDisplay();
  display.setTextSize(1);
  display.println(F("OPTIONS"));
  display.display();
  display.setCursor(0, 10);
  display.print(F("Tension Meter"));
  display.setCursor(0, 20);
  display.print(F("Ambient Temp"));
  display.setCursor(curPos[0], curPos[1]);
  display.print("<");
  display.display();
}

void updateCur()
{

  if ((tNow - tLast) >= interval)
  {
    //If sitting for too long, add goofy animation to EASTEREGGS
    tLast = tNow;
    if (digitalRead(but_d) == LOW)
    {
      if (curPos[1] + 10 <= 20 && curPos[1] != 20)
      {
        Serial.println("UPDATING CURSOR POS @ X:" + String(curPos[0]) + " Y:" + String(curPos[1]));
        curPos[1] = curPos[1] + 10;
        Serial.println("NEW CURSOR POS @ X:" + String(curPos[0]) + " Y:" + String(curPos[1]));
        Serial.println();
        menu();
      }
    }

    if (digitalRead(but_u) == LOW)
    {
      if (curPos[1] - 10 >= 10 && curPos[1] != 10)
      {
        Serial.println("UPDATING CURSOR POS @ X:" + String(curPos[0]) + " Y:" + String(curPos[1]));
        curPos[1] = curPos[1] - 10;
        Serial.println("NEW CURSOR POS @ X:" + String(curPos[0]) + " Y:" + String(curPos[1]));
        Serial.println();
        menu();
      }
    }
  }
}

// Calculates belt tension from frequency and linear density
float tension(float freq, float mu, float len)
{
  float tension = mu * pow(2.0 * len * freq, 2);

  return tension;
}