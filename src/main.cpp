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




#define EASTEREGGS true // Want a fun little suprise?

void welcome(void); // welcome message prototype

void setup()
{
  Serial.begin(9600);
  while ( !Serial ) delay(100);   // wait for native usb, not sure if I'll keep this in final implementation
  Serial.println(F("BMP280 test"));

  // Screen Begin
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }



  // BMP280 Begin
  unsigned status;
  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin();
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  welcome();
}

void loop()
{
}

void welcome() // Welcome Message
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
  display.setTextSize(0);
  display.print(F(" Additive Manufctrng\n      Multi-Tool"));
  display.display();
  delay(2000);
}