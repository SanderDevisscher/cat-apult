int ledPin = 3;
int knop;

void setup() {
  // put your setup code here, to run once:
 pinMode(ledPin, OUTPUT);
 pinMode(2, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:

  knop = digitalRead(2);
  if(knop == 0){
   digitalWrite(ledPin, HIGH);
   delay(500);
   digitalWrite(ledPin, LOW);
   delay(500);
  }
}
