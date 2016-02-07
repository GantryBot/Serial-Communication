#include<SPI.h>
const int ledPin = 13; // the pin that the LED is attached to
void setup() {  
  //initialize serial commm. Serial is global
  Serial.begin(9600);

  // initialize the ledPin as an output:
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin, 0);
}

void loop() {  
//   check if data has been sent from the computer:
  if(Serial.available()){
    digitalWrite(ledPin,1);
    delay(2000);
    digitalWrite(ledPin,0);
    delay(2000);
  }  
}

