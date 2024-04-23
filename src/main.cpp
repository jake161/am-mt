#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU6050.h>
#include <arduinoFFT.h>

// Screen Setup
#define SCREEN_WIDTH 128                        // OLED display width, in pixels
#define SCREEN_HEIGHT 32                        // OLED display height, in pixels
#define OLED_RESET -1                           // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C                     ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Mic Setup
#define SAMPLES 128
#define SAMPLING_FREQUENCY 2048
#define VOLT_OFFSET 250
#define MIC_PIN A2

unsigned int samplingPeriod;
unsigned long microSeconds;

double vReal[SAMPLES];
double vImag[SAMPLES];

ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);

unsigned long prevTime = 0;
float timeDiff = 0;
float timeConst = 10;
float timeConst2 = 100;
float alpha = 0;
float data = 0;
float filtered = 0;

// Acceleration Sensor Setup
MPU6050 accel;
float accelXg, accelYg, accelZg;

// Button Inputs
static const uint8_t but_u = D8;
static const uint8_t but_m = D9;
static const uint8_t but_d = D10;

int curPos[2] = {120, 10};

unsigned long tNow, tLast;
unsigned long interval = 150;

// Sub-Menu Logic
int subMenuState = 0;
int lastButtonState_d = HIGH;
int lastButtonState_u = HIGH;
int lastButtonState_m = HIGH;

// Flags
#define EASTEREGGS false                         // Want a fun little suprise?


// Prototypes
void welcome(void);
void menuMain(void);
void menuTension(void);
void menuAmbient(void);
void menuCon(void);
float tension(float, float, float);
void getAccelCorrected();
double getDominantFrequency();

void setup()
{

  // Mic Setup
  samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY));

  // Button Inputs
  pinMode(but_u, INPUT_PULLUP);
  pinMode(but_m, INPUT_PULLUP);
  pinMode(but_d, INPUT_PULLUP);

  // Accelerometer Begin
  Wire.begin(); // Start the wire libary (used by the accelerometer)
  accel.initialize();      // Initialize the accelerometer
  accel.CalibrateAccel(6); // Calibrate the accelerometer with 6 loops

  // Screen Begin
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){ // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever, if this breaks move semicolon down a line
  }

  // Call menu welcom screen
  welcome();
  menuMain();
}

void loop()
{
  tNow = millis();
  menuCon();
}

////////////////////////////////////////
//                                    //
//        ADDITIONAL FUNCTIONS        //
//                                    //
////////////////////////////////////////

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
      display.print(String(ten)+"N");
      display.setCursor(46, 20);
      display.print(String(freq)+"Hz");

    }
     
    display.display();
}

// Draw the Ambient Temp Sub menu
void menuAmbient(){
    subMenuState = 2;
    //Serial.println(subMenuState);
    display.clearDisplay();
    display.setCursor(25, 0);
    display.print("Acceleration");
    if ((tNow - tLast) >= interval){
      getAccelCorrected();
    }
    display.setCursor(0, 12);
    display.print("X:"+String(abs(accelXg))+"Gs"); // Get acceleration values from MPU6050 in mm/s^2
    display.setCursor(60, 12);
    display.print("Y:"+String(abs(accelYg))+"Gs");
    display.setCursor(0, 25);
    display.print("Z:"+String(abs(accelZg))+"Gs");
    display.display();
}

// Sub Menu Control Logic, handles navigating and re-drawing the menus
void menuCon()
{

  switch (subMenuState)
  {
  case 0:
    if ((tNow - tLast) >= interval)
    {
      int buttonState_d = digitalRead(but_d);
      int buttonState_u = digitalRead(but_u);
      int buttonState_m = digitalRead(but_m);

      if (buttonState_d == lastButtonState_d && buttonState_u == lastButtonState_u && buttonState_m == lastButtonState_m)
      {
        // The button state hasn't changed, so don't proceed
        return;
      }

      tLast = tNow;

      if (buttonState_d == LOW)
      {
        if (curPos[1] + 10 <= 20 && curPos[1] != 20)
        {
          curPos[1] = curPos[1] + 10;
          menuMain();
        }
      }

      if (buttonState_u == LOW)
      {
        if (curPos[1] - 10 >= 10 && curPos[1] != 10)
        {
          curPos[1] = curPos[1] - 10;
          menuMain();
        }
      }

      if (buttonState_m == LOW)
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

      lastButtonState_d = buttonState_d;
      lastButtonState_u = buttonState_u;
      lastButtonState_m = buttonState_m;
    }
    break;

  case 1: // I think I can steal the control logic from above and dump it into the other submenu cases. If thats the case, functions for each menu make sense.
    
    menuTension();

    if ((tNow - tLast) >= interval)
    {
      int buttonState = digitalRead(but_m);
      if (buttonState == lastButtonState_m){
        return;
      }

      tLast = tNow;
      lastButtonState_m = buttonState;
      if (digitalRead(but_m) == LOW) // Debounce this
      {
        menuMain(); // sends back to main menu
      }
    }
    break;

  case 2:

    menuAmbient();

    if ((tNow - tLast) >= interval)
    {
      int buttonState = digitalRead(but_m);
      if (buttonState == lastButtonState_m)
      {
        return;
      }

      tLast = tNow;
      lastButtonState_m = buttonState;
      if (digitalRead(but_m) == LOW) // Debounce this
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
float tension(float freq, float mu, float len)
{
  float tension = mu * pow(2.0 * len * freq, 2);

  return tension;
}

void getAccelCorrected() {
    int16_t ax, ay, az;
    accel.getAcceleration(&ax, &ay, &az);

    timeDiff = micros() - prevTime;
    prevTime = micros();
    alpha = timeDiff / (timeConst2 + timeDiff);

    float rawAccelXg = float(ax) / 8192 /2 ;
    float rawAccelYg = float(ay) / 8192 /2;
    float rawAccelZg = float(az) / 8192 /2 ;

    accelXg = accelXg + alpha * (rawAccelXg - accelXg);
    accelYg = accelYg + alpha * (rawAccelYg - accelYg);
    accelZg = accelZg + alpha * (rawAccelZg - accelZg);
}

double getDominantFrequency() {
    for(int i=0; i<SAMPLES; i++) {
        microSeconds = micros();

        timeDiff = micros() - prevTime;
        prevTime = micros();
        alpha = timeDiff / (timeConst + timeDiff);
        data = analogRead(MIC_PIN) - VOLT_OFFSET;
        filtered = filtered + alpha * (data - filtered);

        vReal[i] = filtered;
        vImag[i] = 0;

        while(micros() < (microSeconds + samplingPeriod)) {
            //do nothing
        }
    }

    FFT.windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.complexToMagnitude(vReal, vImag, SAMPLES);

    double peak = FFT.majorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
    return peak;
}