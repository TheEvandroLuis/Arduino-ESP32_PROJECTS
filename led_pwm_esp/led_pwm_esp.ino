void setup(){
  // configure LED PWM functionalitites
  pinMode(2, OUTPUT);
}
 
void loop(){
  // increase the LED brightness
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    analogWrite(2, dutyCycle);
    delay(15);
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    // changing the LED brightness with PWM
    analogWrite(2, dutyCycle);
    delay(15);
  }
}