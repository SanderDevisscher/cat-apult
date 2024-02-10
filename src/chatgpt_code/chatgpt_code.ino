#include <Servo.h>
#include <LiquidCrystal.h>

#define SERVO_PIN_1 2 // Pin voor servo 1 (snoepjes verplaatsen)
#define SERVO_PIN_2 3 // Pin voor servo 2 (schietmechanisme)
#define BUTTON_PIN 4 // Pin voor het knopje
#define RESET_PIN 5 // Pin voor het resetknopje
#define BUZZER_PIN 6 // Pin voor de buzzer

Servo servo1;
Servo servo2;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const unsigned long cooldownTime = 3000; // 5 minuten cooldown tijd
unsigned long lastPressTime = 0;
bool firstSweetsDeparted = false;
int shootings = 0;

void setup() {
  servo1.attach(SERVO_PIN_1);
  servo2.attach(SERVO_PIN_2);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(RESET_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Shootings: ");
}

void loop() {
  unsigned long currentTime = millis();

  if (digitalRead(BUTTON_PIN) == LOW && currentTime - lastPressTime >= cooldownTime) {
    lastPressTime = currentTime;
    moveSweets();
    firstSweetsDeparted = true;
    shootSweets();
    updateLCD();
  }

  if (digitalRead(RESET_PIN) == LOW) {
    shootings = 0;
    lcd.setCursor(0, 1);
    lcd.print("             "); // Om het oude aantal te overschrijven
    lcd.setCursor(0, 1);
    lcd.print(shootings);
    firstSweetsDeparted = false; // Reset de flag
  }

  if (firstSweetsDeparted && currentTime - lastPressTime >= cooldownTime) {
    if (digitalRead(BUTTON_PIN) == LOW) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(100);
      digitalWrite(BUZZER_PIN, LOW);
      delay(100);
    }
  }

  // Cooldown tijd weergeven op LCD scherm
  unsigned long remainingTime = cooldownTime - (currentTime - lastPressTime);
  lcd.setCursor(0, 0);
  lcd.print("Cooldown: ");
  lcd.print(remainingTime / 60000); // Minuten
  lcd.print("m ");
  lcd.print((remainingTime % 60000) / 1000); // Seconden
  lcd.print("s ");
}

void moveSweets() {
  servo1.write(90);
  delay(1000);
  servo1.write(0);
  delay(1000);
}

void shootSweets() {
  servo2.write(180);
  delay(1000);
  servo2.write(0);
  delay(1000);
  shootings++;
}

void updateLCD() {
  lcd.setCursor(0, 1);
  lcd.print("             ");
  lcd.setCursor(0, 1);
  lcd.print(shootings);
}