#include <LiquidCrystal.h>
#include <Servo.h>
int ledPin = 3;
int knop = 4;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 
int shootings = 0;
unsigned long startTime;
int servo1_pin = 2;
Servo servo1;

// cat parts:
uint8_t CAT1[8] =  //karaters voor ventilator.
{
    0b00000,
    0b00000,
    0b00100,
    0b01110,
    0b01110,
    0b01111,
    0b11111,
    0b11100
};
uint8_t CAT2[8] =  //karaters voor ventilator.
{
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b01110,
    0b11111,
};
uint8_t CAT3[8] =  //karaters voor ventilator.
{
    0b00000,
    0b00000,
    0b00100,
    0b01110,
    0b01110,
    0b11110,
    0b11111,
    0b00111
};
uint8_t CAT4[8] =  //karaters voor ventilator.
{
    0b11100,
    0b11111,
    0b11111,
    0b01111,
    0b11110,
    0b00111,
    0b00011,
    0b00000
};
uint8_t CAT5[8] =  //karaters voor ventilator.
{
    0b11111,
    0b11011,
    0b10001,
    0b11111,
    0b11111,
    0b00000,
    0b10001,
    0b11111
};
uint8_t CAT6[8] =  //karaters voor ventilator.
{
    0b00111,
    0b11111,
    0b11111,
    0b11110,
    0b01111,
    0b11100,
    0b11000,
    0b00000
};

uint8_t SNOR1[8] =  //karaters voor ventilator.
{
    0b00111,
    0b00000,
    0b01111,
    0b00000,
    0b00111,
    0b00000,
    0b00000,
    0b00000
};
uint8_t SNOR2[8] =  //karaters voor ventilator.
{
    0b11100,
    0b00000,
    0b11110,
    0b00000,
    0b11100,
    0b00000,
    0b00000,
    0b00000
};
uint8_t OP[8] =  //karaters voor ventilator.
{
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00000,
    0b10101,
    0b10001,
    0b11111
};

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
 pinMode(ledPin, OUTPUT);
 pinMode(2, INPUT_PULLUP);
 lcd.begin(16, 2); 
 lcd.setCursor(0,0); 
 servo1.attach(servo1_pin);

 lcd.createChar(9, CAT1);  //karaters
    lcd.createChar(1, CAT2);  //karaters
    lcd.createChar(2, CAT3);  //karaters
    lcd.createChar(3, CAT4);  //karaters
    lcd.createChar(4, CAT5);  //karaters
    lcd.createChar(5, CAT6);  //karaters
    lcd.createChar(6, SNOR1);  //karaters
    lcd.createChar(7, SNOR2);  //karaters      
        
    lcd.setCursor(0,0);               //start scherm
    lcd.print("Cat Candy       "); 
    lcd.setCursor(0,1);
    lcd.print("Shooter         ");
    lcd.setCursor(12,0);
    lcd.write(9);
    lcd.setCursor(13,0);
    lcd.write(1);
    lcd.setCursor(14,0);
    lcd.write(2);
    lcd.setCursor(12,1);           
    lcd.write(3);                 // start scherm
    lcd.setCursor(13,1);           
    lcd.write(4);   
    lcd.setCursor(14,1);           
    lcd.write(5); 
    lcd.setCursor(11,1);           
    lcd.write(6); 
    lcd.setCursor(15,1);           
    lcd.write(7);         
    delay(5000);  

    lcd.clear();                   // start scherm
    lcd.print("Created by     "); 
    lcd.setCursor(0,1); 
    lcd.print("Timo Aerts and  ");
    delay(3000);
    
    lcd.clear();
    lcd.print("Sander          "); 
    lcd.setCursor(0,1); 
    lcd.print("Devisscher      ");
    delay(3000);                   // einde start scherm
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Shootings:      ");
    lcd.setCursor(11,0);
    lcd.print(shootings);
    startTime = millis();
}

void loop() {
  // put your main code here, to run repeatedly:

   knop = digitalRead(2);
    
    Serial.println(knop);
    if(knop == 0) {
      shot();
    }
}

void shot() {
  
  //motor...
  Serial.println(knop);
   if(shootings >= 1){
     unsigned long currentTime = millis();
    // bereken cooldown
   

    // knop werd te snel ingedrukt
     if (currentTime - startTime < 120000) {
      lcd.setCursor(0,1);
      lcd.print("neeje niet nu!!");  // Reset the count if 2 seconds have passed
      delay(500);
      lcd.setCursor(0,1);
      lcd.print("               ");
      startTime = currentTime;
     }
    // er werd lang genoeg gewacht
     else{
      servo1.write(0);
      delay(500);
      servo1.write(180);
      shootings ++; 
      lcd.setCursor(11,0);
      lcd.print(shootings);
      delay(500);
      startTime = currentTime;
     }
   }
   else{
     servo1.write(0);
     delay(500);
     servo1.write(180);
     shootings ++; 
     lcd.setCursor(11,0);
     lcd.print(shootings);
    delay(500);
   }
}

void cooldown(){

}