#define red_led 11
#define green_led 9
#define blue_led 10

void setup()
{
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(blue_led, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available()){
    char led_specifier = Serial.read();
    int led_brightness = Serial.parseInt();
    write_leds(led_specifier, led_brightness);
  }
}

void write_leds(char led, int brightness)
{
  if (led == 'r'){
    analogWrite(red_led, brightness);
    return;
  }
  if (led == 'g'){
    analogWrite(green_led, brightness);
    return;
  }
  if (led == 'b'){
    analogWrite(blue_led, brightness);
    return;
  }
  
  return;
}
