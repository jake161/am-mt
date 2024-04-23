#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU6050.h>

// Screen Setup
#define SCREEN_WIDTH 128                        // OLED display width, in pixels
#define SCREEN_HEIGHT 32                        // OLED display height, in pixels
#define OLED_RESET -1                           // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C                     ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Mic Setup
#define MIC_PIN             A2                  // Analog pin connected to the microphone
#define SAMPLE_RATE         44100               // Audio sample rate in Hz
#define NUM_SAMPLES         2048                // Number of samples to process for frequency estimation
#define SAMPLE_DELAY_US     (1000000 / SAMPLE_RATE) // Delay between samples in microseconds
#define DC_OFFSET           1650                // Analog voltage offset to center at 0, NEEDS TUNING
#define NUM_VALUES_TO_AVERAGE 5                 // Number of previous frequency values to average

// Acceleration Sensor Setup
MPU6050 accel;
float accelXg, accelYg, accelZg;

float alpha = 1; // This is the smoothing factor, adjust it to your needs
float lastOutput = 0.0; // This will hold the last output value

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
float processAudio();
void getAccelCorrected();
float lowPassFilter(float);

void setup()
{

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
    display.setCursor(46, 20);
    float ten=lowPassFilter(tension(processAudio(),0.0083,0.350));
    if (ten>1000){
      display.setCursor(10, 20);
      display.print("Freq out of Range");
    }
    else {
      //Calculate tension from analog audio input
      display.print(String(ten)+"N");
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

float processAudio() {
    unsigned long last_crossing_time = 0;
    unsigned long crossings = 0;

    // Array to store previous frequency values for averaging
    float previous_values[NUM_VALUES_TO_AVERAGE] = {0};
    int index = 0;

    // Collect audio samples
    for (int i = 0; i < NUM_SAMPLES; i++) {
        int sample = analogRead(MIC_PIN) - DC_OFFSET; // Read analog input and center around 0

        // Check for zero-crossings
        if (i > 0 && sample * (analogRead(MIC_PIN) - DC_OFFSET) < 0) {
            if (last_crossing_time != 0) {
                unsigned long current_time = micros();
                unsigned long period = current_time - last_crossing_time;
                crossings++;

                last_crossing_time = current_time;
            } else {
                last_crossing_time = micros();
            }
        }

        delayMicroseconds(SAMPLE_DELAY_US); // Adjusted delay between samples
    }

    // Calculate frequency based on zero-crossings
    float frequency;
    if (crossings > 0) {
        // Convert crossings to Hz
        frequency = (float)crossings * 1000000 / (NUM_SAMPLES * SAMPLE_DELAY_US);
    } else {
        frequency = 0; // Default to 0 if no crossings
    }

    // Store current frequency values
    previous_values[index] = frequency;
    index = (index + 1) % NUM_VALUES_TO_AVERAGE;

    // Calculate average frequency value
    float average_frequency = 0;
    for (int i = 0; i < NUM_VALUES_TO_AVERAGE; i++) {
        average_frequency += previous_values[i];
    }
    average_frequency /= NUM_VALUES_TO_AVERAGE;

    // Output the dominant frequency
    return average_frequency;
}

void getAccelCorrected() { // Provide this portion of the code to the students.
  int16_t ax, ay, az; // Initialize acceleration variables in the different axes. "int16_t" means 16-bit integer.
  accel.getAcceleration(&ax, &ay, &az); // Get axis acceleration values.
  accelXg = float(ax) / 8192 /2 ; // Conversion to g's.
  accelYg = float(ay) / 8192 /2; // Conversion to g's.
  accelZg = float(az) / 8192 /2 ; // Conversion to g's.
}

float lowPassFilter(float input) {
  float output = alpha * input + (1.0 - alpha) * lastOutput;
  lastOutput = output;
  return output;
}