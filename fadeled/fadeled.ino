int ledPin = 13;      // LED connected to digital pin 9
int val = 0;         // variable to store the read value

void setup()
{
  pinMode(ledPin, OUTPUT);   // sets the pin as output
}

void loop()
{
  int i;
  for (i = 0; i < 256; i++) {
    analogWrite(ledPin, i);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
    delay(10);
  }
  for (i = 0; i < 256; i++) {
    analogWrite(ledPin, 255 - i);
    delay(10);
  }
}
