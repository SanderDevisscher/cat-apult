#include <Servo.h>
#include <LiquidCrystal.h>

Servo feederServo;  // servo voor het voeren van snoepjes
Servo shooterServo; // servo voor het schieten van snoepjes
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // LCD pinnen

const int startButtonPin = 2;  // pin voor start knop
const int resetButtonPin = 3;  // pin voor reset knop
const int buzzerPin = 1;       // pin voor buzzer

int shootings = 0;             // aantal shootings
unsigned long cooldownTime = 60000; // cooldown tijd in milliseconden (1 minuut)
unsigned long lastShootTime = 0;    // tijd van laatste shooting

void setup() {
  feederServo.attach(11);
  shooterServo.attach(12);
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("aantal shootings:");
  lcd.setCursor(0, 1);
  lcd.print("cooldowntime:");
}

void loop() {
  if (digitalRead(startButtonPin) == LOW) {
    lcd.clear();
    lcd.print("Nee niet nu!");
    delay(60000); // wacht 1 minuut
    lcd.clear();
    lcd.print("aantal shootings:");
    lcd.setCursor(0, 1);
    lcd.print("cooldowntime:");
  }

  if (digitalRead(resetButtonPin) == LOW) {
    shootings = 0;
    lastShootTime = 0;
  }

  unsigned long currentTime = millis();
  if (currentTime - lastShootTime >= cooldownTime) {
    if (shootings > 0) {
      shootings--;
    }
    lastShootTime = currentTime;
  }

  lcd.setCursor(16, 0);
  lcd.print(shootings);
  lcd.setCursor(14, 1);
  lcd.print(cooldownTime / 1000); // toon cooldown tijd in seconden

  // Voer hier de code in voor het schieten van snoepjes wanneer nodig
}

void buzz() {
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
  delay(100);
}