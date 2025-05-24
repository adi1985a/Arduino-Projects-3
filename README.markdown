# 🔴🟡🟢 Arduino LED Toggle with I2C LCD and Polish Characters

This Arduino project toggles three LEDs (Red, Yellow, Green) using a push button. It displays the active LED and its status (ON/OFF) on a 16x2 I2C LCD, including custom characters to correctly display Polish letters like **Ż**, **ó**, and **ł**.

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![Platform: Arduino](https://img.shields.io/badge/Platform-Arduino-00979D.svg)](https://www.arduino.cc/)
[![Language: C++](https://img.shields.io/badge/Language-C++-lightgrey.svg)](https://isocpp.org/)

## 🧠 Overview

This project demonstrates:

- Button-controlled toggling of three LEDs in sequence.
- Displaying the current LED and its status (ON/OFF) on a 16x2 I2C LCD.
- Use of custom characters for Polish language support on the LCD.
- Basic debounce handling to ensure reliable button presses.

## 🛠 Components Required

| Component             | Quantity |
|-----------------------|----------|
| Arduino (Uno/Nano)    | 1        |
| I2C 16x2 LCD display  | 1        |
| LEDs (Red, Yellow, Green) | 3    |
| Resistors (220Ω)      | 3        |
| Push Button           | 1        |
| Breadboard + Wires    | as needed |

## 🔌 Wiring Guide

### LEDs and Button

| Arduino Pin | Connected To               |
|-------------|----------------------------|
| D5          | Green LED (via resistor)   |
| D6          | Red LED (via resistor)     |
| D9          | Yellow LED (via resistor)  |
| D7          | Push Button (with pull-up) |

### I2C LCD (Default I2C address: `0x27`)

| LCD Pin | Arduino Pin |
|---------|-------------|
| GND     | GND         |
| VCC     | 5V          |
| SDA     | A4 (Uno)    |
| SCL     | A5 (Uno)    |

💡 *Use an I2C scanner if unsure of your LCD address.*

## 📸 Screenshots

Coming soon!

## 📄 Features

- Press the button to toggle the current LED ON/OFF.
- If the LED is turned OFF, the program advances to the next LED in the cycle.
- LCD and Serial Monitor display the current LED name and its status.
- Custom Polish characters for `'Ż'`, `'ó'`, and `'ł'` are rendered correctly on the LCD.

## 🧾 Code Summary

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Polish character definitions
byte customCharZ[8] = {B00100, B11111, B00001, B00010, B00100, B01000, B10000, B11111}; // 'Ż'
byte customCharO[8] = {B00100, B00000, B01110, B10001, B10001, B10001, B01110, B00000}; // 'ó'
byte customCharL[8] = {B01100, B00100, B00110, B00100, B01100, B00100, B01110, B00000}; // 'ł'

const int redPin = 6;
const int yellowPin = 9;
const int greenPin = 5;
const int buttonPin = 7;

bool ledState = LOW;
int currentLED = 0;
bool buttonPressed = false;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, customCharL);
  lcd.createChar(1, customCharO);
  lcd.createChar(2, customCharZ);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Debounced button logic...
}

void updateLEDs() {
  // Logic to toggle LED and update LCD and Serial...
}
```

🟡 *When the yellow LED is active, the LCD uses three custom characters to display `"Żółta"` properly.*

## ▶️ How to Run

1. Open the **Arduino IDE**.
2. Install the `LiquidCrystal_I2C` library via **Library Manager**.
3. Upload the sketch to your Arduino board.
4. Open **Serial Monitor** (`9600 baud`) and observe the LCD.
5. Press the button to cycle through the LEDs.

## ✅ Project Highlights

✅ Button-controlled LED cycling  
✅ Custom LCD character creation  
✅ LCD and Serial synchronization  
✅ Polish diacritic support (`Ż`, `ó`, `ł`)

## 📃 License

This project is open-source and available under the **MIT License**. See the `LICENSE` file for details.

## 👨‍💻 Author

**Adrian Lesniak**

> 💡 Designed for projects where internationalization, hardware control, and user interaction matter most.
