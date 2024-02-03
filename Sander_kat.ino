#include <LCD_I2C.h>
LCD_I2C lcd(0x27, 16, 2); // Default address 
int candy = 20;
int knop;
int shootings = 0;
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
void setup()
{
    pinMode(2, INPUT_PULLUP);    //knop kat
    
    lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
    lcd.backlight();
    Serial.begin(9600);

    lcd.createChar(0, CAT1);  //karaters
    lcd.createChar(1, CAT2);  //karaters
    lcd.createChar(2, CAT3);  //karaters
    lcd.createChar(3, CAT4);  //karaters
    lcd.createChar(4, CAT5);  //karaters
    lcd.createChar(5, CAT6);  //karaters
    lcd.createChar(6, SNOR1);  //karaters
    lcd.createChar(7, SNOR2);  //karaters    
    lcd.createChar(8, OP);  //karaters    
        
    lcd.setCursor(0,0);               //start scherm
    lcd.print("Cat Candy       "); 
    lcd.setCursor(0,1);
    lcd.print("Shooter         ");
    lcd.setCursor(12,0);
    lcd.write(0);
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
    delay(500);  

    lcd.backlight();
    lcd.clear();                   // start scherm
     lcd.print("Created by     "); 
    lcd.setCursor(0,1); 
    lcd.print("Timo Aerts and  ");
    delay(3000);
    
    lcd.backlight();
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
    lcd.setCursor(0,1);
    lcd.print("Candies:        ");
    lcd.setCursor(11,1);
    lcd.print(candy);
}
void loop(){
  
    knop = digitalRead(2);
    Serial.println(knop);
    if(knop == 0) {
      shot();
    }

    if(candy <5) {
      lcd.setCursor(15,1);           
      lcd.write(8);    
    }
}
void shot() {
  shootings ++; 
  //motor...
  candy --;
   lcd.setCursor(11,0);
   lcd.print(shootings);
   lcd.setCursor(11,1);
   lcd.print(candy);
   delay(1000);
}
