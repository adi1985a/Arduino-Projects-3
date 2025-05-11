#include <Wire.h>  // Dołącz bibliotekę Wire, używaną do komunikacji I2C
#include <LiquidCrystal_I2C.h> // Dołącz bibliotekę dla wyświetlacza LCD z interfejsem I2C

// Ustawienie adresu I2C dla LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Definicja własnych znaków dla polskich liter
byte customCharZ[8] = {B00100, B11111, B00001, B00010, B00100, B01000, B10000, B11111}; // 'Ż'
byte customCharO[8] = {B00100, B00000, B01110, B10001, B10001, B10001, B01110, B00000}; // 'ó'
byte customCharL[8] = {B01100, B00100, B00110, B00100, B01100, B00100, B01110, B00000}; // 'ł'

const int redPin = 6; // Pin dla czerwonej diody LED
const int yellowPin = 9; // Pin dla żółtej diody LED
const int greenPin = 5; // Pin dla zielonej diody LED
const int buttonPin = 7; // Pin cyfrowy dla przycisku
bool lastButtonState = HIGH; // Zakładamy, że przycisk jest aktywowany do LOW
bool currentButtonState = HIGH; // Aktualny stan przycisku
unsigned long lastDebounceTime = 0; // Ostatni czas dla debouncingu
unsigned long debounceDelay = 50; // Opóźnienie dla debouncingu

int ledPins[] = {redPin, yellowPin, greenPin}; // Tablica pinów dla diod LED
String ledNames[] = {"Czerwona", "Żółta", "Zielona"}; // Nazwy diod LED
int currentLED = 0; // Aktualnie kontrolowana dioda LED
bool ledState = LOW; // Stan diody LED, LOW oznacza wyłączoną
bool buttonPressed = false; // Dodana flaga do śledzenia, czy przycisk został już obsłużony

void setup() {
  lcd.init(); // Inicjalizacja LCD
  lcd.backlight(); // Włączenie podświetlenia

  // Utworzenie własnych znaków
  lcd.createChar(0, customCharL); // 'ł'
  lcd.createChar(1, customCharO); // 'ó'
  lcd.createChar(2, customCharZ); // 'Ż'

  pinMode(buttonPin, INPUT_PULLUP); // Ustawienie pinu przycisku jako wejście z wewnętrznym rezystorem podciągającym
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT); // Ustawienie pinów LED jako wyjścia
  }
  Serial.begin(9600); // Rozpoczęcie komunikacji szeregowej
}

void loop() {
  int reading = digitalRead(buttonPin); // Odczyt stanu przycisku

  if (reading != lastButtonState) { // Jeśli stan przycisku się zmienił
    lastDebounceTime = millis(); // Zaktualizuj czas debouncingu
  }

  if ((millis() - lastDebounceTime) > debounceDelay) { // Jeśli minęło wystarczająco dużo czasu od debouncingu
    if (reading != currentButtonState) { // I stan przycisku się zmienił
      currentButtonState = reading; // Zaktualizuj aktualny stan przycisku

      if (currentButtonState == LOW && !buttonPressed) { // Jeśli przycisk jest wciśnięty i nie był wcześniej obsłużony
        updateLEDs(); // Zaktualizuj stany diod LED
        buttonPressed = true; // Ustaw flagę, że przycisk został obsłużony
      } 
      else if (currentButtonState == HIGH) {
        buttonPressed = false; // Reset flagi, gdy przycisk jest zwolniony
      }
    }
  }

  lastButtonState = reading; // Zaktualizuj ostatni odczytany stan przycisku
}

void updateLEDs() {
  ledState = !ledState; // Zmiana stanu diody LED na przeciwny

  // Wyłączenie wszystkich diod LED
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPins[i], LOW);
  }

  // Włączenie bieżącej diody LED
  digitalWrite(ledPins[currentLED], ledState ? HIGH : LOW);

  // Wysyłanie informacji do Serial i LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  
  // Sprawdź czy bieżąca dioda LED to żółta i wyświetl "Żółta"
  if (currentLED == 1) { // Zakładając, że żółta ma indeks 1
    lcd.write(byte(2)); // 'Ż'
    lcd.write(byte(1)); // 'ó'
    lcd.write(byte(0)); // 'ł'
    lcd.print("ta");
    Serial.println("Żółta " + String(ledState ? "ON" : "OFF"));
  } else {
    lcd.print(ledNames[currentLED]); // Wypisz nazwę diody na LCD
    Serial.print(ledNames[currentLED]); // Wyślij nazwę diody na port szeregowy
    Serial.println(ledState ? " ON" : " OFF");
  }

  lcd.print(ledState ? " - ON" : " - OFF"); // Dodaj informację o stanie diody na LCD

  if (!ledState) {
    currentLED = (currentLED + 1) % 3; // Przejdź do następnej diody tylko podczas wyłączania
  }
}
