int potPin = A0;    // select the input pin for the potentiometer
int ledPins[] = {5, 6, 7, 8, 9, 10};   // select the output pins for the LEDs
int numLeds = sizeof(ledPins)/sizeof(int);   // calculate the number of LEDs

void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);    // initialize the LED pins as outputs
  }
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);   // read the potentiometer value
  int ledCount = map(potValue, 0, 1023, 0, numLeds);   // map the potentiometer value to the number of LEDs to light up
  Serial.print("POT: ");
  Serial.print(potValue);
  Serial.print("LEDS: ");
  Serial.println(ledCount);
  for (int i = 0; i < numLeds; i++) {
    if (i < ledCount) {
      digitalWrite(ledPins[i], HIGH);   // turn on the LED
    } else {
      digitalWrite(ledPins[i], LOW);    // turn off the LED
    }
  }
}
