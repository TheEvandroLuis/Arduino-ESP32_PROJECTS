#include <Servo.h>

Servo servo1;
Servo servo2;

uint8_t servo1_pin = 10;
uint8_t servo2_pin = 11;

void setup() {
  servo1.attach(servo1_pin);
  servo2.attach(servo2_pin);
}

void loop() {

  servo2.write(random(0,180));
  delay(5000);
}
