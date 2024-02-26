#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <Menus.h>

// Debug and such
#define EASTEREGGS true // Want a fun little suprise?
#define BMP_DEBUG false

// Button Inputs
static const uint8_t but_u = D8;
static const uint8_t but_m = D9;
static const uint8_t but_d = D10;


// Screen Setup
Menus myMenu(but_u,but_m,but_d,EASTEREGGS,150);

// Temp BMP280 Setup
Adafruit_BMP280 bmp; // I2C

// Mic Setup
static const uint8_t micPin = A2;

void setup()
{
  if (BMP_DEBUG == true)
  {
    while (!Serial)
      delay(100); // wait for native usb, not sure if I'll keep this in final implementation
    Serial.println(F("BMP280 test"));
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

  myMenu.welcome();
  myMenu.menuMain();
}

void loop()
{
  myMenu.tNow = millis();

  myMenu.menuCon();
  Serial.println(analogRead(micPin));
}