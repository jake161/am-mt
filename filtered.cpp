#include <Arduino.h>
unsigned long prevTime = 0;
float timeDiff = 0;
int timeConst = 10;
float alpha = 0;
float data = 0;
float filtered = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    timeDiff = millis() - prevTime;
    prevTime = millis();
    alpha = timeDiff / (timeConst + timeDiff);
    data=analogRead(A0)-250;
    filtered = filtered + alpha * (data - filtered);
    Serial.println(filtered,3);
}