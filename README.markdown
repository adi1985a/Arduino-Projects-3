# 🔴🟡🟢 Arduino LED Toggle with I2C LCD and Polish Characters

This Arduino project toggles three LEDs (Red, Yellow, Green) using a push button. It displays the active LED and its status (ON/OFF) on a 16x2 I2C LCD, including custom characters to correctly display Polish letters like **Ż**, **ó**, and **ł**.

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![Platform: Arduino](https://img.shields.io/badge/Platform-Arduino-00979D.svg)](https://www.arduino.cc/)
[![Language: C++](https://img.shields.io/badge/Language-C++-lightgrey.svg)](https://isocpp.org/)

---

## 🧠 Overview

This project demonstrates:

- Button-controlled toggling of three LEDs in sequence.
- Displaying LED status (ON/OFF) on a 16x2 I2C LCD.
- Custom LCD characters for Polish letters: **Ż**, **ó**, **ł**.
- Basic debounce handling for reliable button input.

---

## 🛠️ Components Required

| Component            | Quantity |
|----------------------|----------|
| Arduino Uno/Nano     | 1        |
| I2C 16x2 LCD Display | 1        |
| Red LED              | 1        |
| Yellow LED           | 1        |
| Green LED            | 1        |
| 220Ω Resistors       | 3        |
| Push Button          | 1        |
| Breadboard & Wires   | As needed |

---

## 🔌 Wiring Guide

### LEDs and Button

| Arduino Pin | Connected To              |
|-------------|---------------------------|
| D5          | Green LED (via resistor)  |
| D6          | Red LED (via resistor)    |
| D9          | Yellow LED (via resistor) |
| D7          | Push Button (with pull-up)|

### I2C LCD (Default Address: `0x27`)

| LCD Pin | Arduino Pin |
|---------|-------------|
| GND     | GND         |
| VCC     | 5V          |
| SDA     | A4 (Uno)    |
| SCL     | A5 (Uno)    |

💡 Use an [I2C scanner](https://playground.arduino.cc/Main/I2cScanner/) to detect your LCD address if unsure.

---

## 📄 Features

- 🔘 Press button to toggle active LED ON/OFF.
- 🔁 If turned OFF, next LED in cycle becomes active.
- 📺 LCD and Serial Monitor display LED name and state.
- 🇵🇱 Custom LCD characters support Polish diacritics (Ż, ó, ł).

---

## 📸 Screenshots

Screenshots of the working project should be placed in the `screenshots/` folder.

| LCD Display Example | Serial Monitor Output |
|---------------------|------------------------|
| ![LCD Screenshot](screenshots/lcd.png) | ![Serial Screenshot](screenshots/serial.png) |

> 📝 Replace with your actual screenshots.

---

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

🟡 When the yellow LED is active, the LCD uses three custom characters to display `"Żółta"` properly.

---

## ▶️ How to Run

1. Open the **Arduino IDE**.
2. Go to `Tools > Manage Libraries` and install **LiquidCrystal_I2C**.
3. Upload the sketch to your Arduino board.
4. Open the **Serial Monitor** (9600 baud).
5. Press the button to cycle through LED states and observe the LCD updates.

---

## ✅ Project Highlights

- ✅ Button-controlled LED toggling logic.
- ✅ Polish diacritic support on I2C LCD.
- ✅ LCD + Serial synchronization.
- ✅ Clean hardware-software interaction.

---

## 📃 License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT).  
See the `LICENSE` file for details.

---

## 👤 Author

**Adrian Lesniak**  
Embedded Systems & Arduino Developer

---

> 💡 A simple but elegant project showcasing multilingual display, state control, and interactive hardware behavior using Arduino.
