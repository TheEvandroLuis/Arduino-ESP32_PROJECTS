#include <FastLED.h>

#define NUM_LEDS 32
#define FITA_LED 9
#define BOTAO 7
#define RELE 6

CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812, FITA_LED, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  pinMode(BOTAO, INPUT_PULLUP);
  pinMode(RELE, OUTPUT);
  digitalWrite(RELE, HIGH);

  for (int i=0; i<NUM_LEDS; i++){
      leds[i]=CRGB::Black;
  }
  FastLED.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(BOTAO)==0){
    for (int i=0; i<NUM_LEDS; i++){
      leds[i]=CRGB::Green;
      FastLED.show();
      delay(200);
    }
    digitalWrite(RELE, LOW);

    for (int i=31; i>=0; i--){
      leds[i]=CRGB::Red;
      FastLED.show();
      delay(200);
    }
    delay(2000);
    digitalWrite(RELE, HIGH);
      for (int i=0; i<NUM_LEDS; i++){
      leds[i]=CRGB::Black;
    }
    FastLED.show();
  }
}
