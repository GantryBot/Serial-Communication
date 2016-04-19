#include <PrintCascade.h>
#include <SerialDebug.h>
#include<SPI.h>
const int ledPin = 13; // the pin that the LED is attached to
#define debug true;
void setup() {  
  //initialize serial commm. Serial is global
  Serial.begin(9600);

if(debug){
  SerialDebugger.begin(9600);
  SerialDebugger.enable(Error);
  SerialDebugger.enable(NOTIFICATION);
  }

  // initialize the ledPin as an output:
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin, 0);
}

void loop() {  
//   check if data has been sent from the computer:
  if(Serial.available() > 0){
    // read the most recent byte (which will be from 0 to 255):
    digitalWrite(ledPin,1); 
    String request=Serial.readString();
    Serial.println(request);
    delay(20000);
    digitalWrite(ledPin,0); 
      
  } 
}

