#include <Servo.h>
#include <LiquidCrystal.h>

#define SERVO_PIN_1 9 // Pin voor servo 1 (snoepjes verplaatsen)
#define SERVO_PIN_2 10 // Pin voor servo 2 (schietmechanisme)
#define BUTTON_PIN 2 // Pin voor het knopje
#define RESET_PIN 3 // Pin voor het resetknopje
#define BUZZER_PIN 4 // Pin voor de buzzer
#define LCD_RS 12
#define LCD_EN 11
#define LCD_D4 5
#define LCD_D5 4
#define LCD_D6 3
#define LCD_D7 6
#define LCD_COLUMNS 16
#define LCD_ROWS 2

Servo servo1;
Servo servo2;
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

const unsigned long cooldownTime = 300000; // 5 minuten cooldown tijd
unsigned long lastPressTime = 0;
int shootings = 0;

void setup() {
  servo1.attach(SERVO_PIN_1);
  servo2.attach(SERVO_PIN_2);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(RESET_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  lcd.begin(LCD_COLUMNS, LCD_ROWS);
  lcd.print("Shootings: ");
}

void loop() {
  unsigned long currentTime = millis();
  
  if (digitalRead(BUTTON_PIN) == LOW && currentTime - lastPressTime >= cooldownTime) {
    lastPressTime = currentTime;
    moveSweets();
    shootSweets();
    updateLCD();
  }

  if (digitalRead(RESET_PIN) == LOW) {
    shootings = 0;
    lcd.setCursor(0, 1);
    lcd.print("             "); // Om het oude aantal te overschrijven
    lcd.setCursor(0, 1);
    lcd.print(shootings);
  }
  
  if (currentTime - lastPressTime < cooldownTime && digitalRead(BUTTON_PIN) == LOW) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
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