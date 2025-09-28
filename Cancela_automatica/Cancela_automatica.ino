#include <Servo.h>
#include <HCSR04.h>

// Pin definitions
const int trigPin = 9;
const int echoPin = 8;
const int servoPin = 5;

HCSR04 hc(trigPin, echoPin); //initialisation class HCSR04 (trig pin , echo pin)
Servo gateServo;

void setup() {
  gateServo.attach(servoPin);
  // Move servo to closed position
  gateServo.write(0);
  Serial.begin(9600);
}

void loop() {
  int distancia = hc.dist();
  Serial.println(distancia);
  if (distancia < 10 ) {
    gateServo.write(90);
    delay(5000);
    gateServo.write(0);
  }
}
