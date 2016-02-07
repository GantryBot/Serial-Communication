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
    // read the most recent byte (which will be from 0 to 255):
    int brightness = Serial.parseInt();
    Serial.print(brightness);
    digitalWrite(ledPin,1);
    
  }  
}
