# Additive Manufacturing - Multi-Tool

Current sensor loadout:
- GY-521 (for acceleration checking)
- ADA1713 (microphone and op-amp)

Hardware:
- ESP32S3 XIAO (Testing with c3)
- 0.96" inch OLED I2C Display

Under the Hood:
- Frequency detection using arduinoFFT
- Tesnion calcuated with linear density and fundamental frequency eq.

Potential Addons:
- Gcode communication
- Chamber temperature sensor
- VOC meter
- Fan tester
- Thermistor tester
- Limit switch tester
- Bubble level 

Current predicted peak current draw: 90.11mA
Predicted battery life: 15hrs (minimum)

### ToDo:
1. Seperate functions into seperate files
2. Switch to I2S mic
3. Improve FFT sampling and low dB response
4. Data logging
5. Serial interface with printer

