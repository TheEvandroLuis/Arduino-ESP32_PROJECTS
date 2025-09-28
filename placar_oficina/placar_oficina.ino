#include <FastLED.h>
#define NUM_LEDS 56
#define LED_L 12
#define LED_R 14

CRGB leds_home[NUM_LEDS];
CRGB leds_guest[NUM_LEDS];


// Mapeamento dos segmentos para cada número (0-9)
const bool segmentos[10][7] = {
  {0, 1, 1, 1, 1, 1, 1}, // 0
  {0, 1, 0, 0, 0, 0, 1}, // 1
  {1, 1, 1, 0, 1, 1, 0}, // 2
  {1, 1, 1, 0, 0, 1, 1}, // 3
  {1, 1, 0, 1, 0, 0, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {0, 1, 1, 0, 0, 0, 1}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812, LED_L, GRB>(leds_home, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_R, GRB>(leds_guest, NUM_LEDS);
  FastLED.setBrightness(255);
}

void loop() {
  // put your main code here, to run repeatedly:
   mostraNumero(7, leds_home, CRGB::Green);
   mostraNumero(4, leds_guest, CRGB::Blue);
}

void mostraNumero(int numero, CRGB *leds, CRGB cor) {
    if (numero < 0 || numero > 99) {
        // Tratar números inválidos (opcional)
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i] = CRGB::Black; // Apaga tudo
        }
        FastLED.show();
        return;
    }

    int dezena = numero / 10;
    int unidade = numero % 10;

    int segmentoIndexDezena = 0;
    int segmentoIndexUnidade = 28;

    for (int segmento = 0; segmento < 7; segmento++) {
        for (int i = 0; i < 4; i++) {
            leds[segmentoIndexDezena++] = segmentos[dezena][segmento] ? cor : CRGB::Black;
            leds[segmentoIndexUnidade++] = segmentos[unidade][segmento] ? cor : CRGB::Black;
        }
    }
    FastLED.show();
}
