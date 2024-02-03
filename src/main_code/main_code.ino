#include <LiquidCrystal.h>
int ledPin = 3;
int knop;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

void setup() {
  // put your setup code here, to run once:
 pinMode(ledPin, OUTPUT);
 pinMode(2, INPUT_PULLUP);
 lcd.begin(16, 2); 
 lcd.setCursor(0,0); 
}

void loop() {
  // put your main code here, to run repeatedly:

  knop = digitalRead(2);
  if(knop == 0){
   lcd.print("hello, world!"); 
   digitalWrite(ledPin, HIGH);
   delay(500);
   digitalWrite(ledPin, LOW);
   delay(500);
   lcd.clear();
  }
}
