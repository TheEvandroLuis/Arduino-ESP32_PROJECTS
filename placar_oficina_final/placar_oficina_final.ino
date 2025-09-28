#include "BluetoothSerial.h"
#include <FastLED.h>

#define NUM_LEDS 56
#define NUM_LEDS_MENOR 21
#define LED_L 12
#define LED_R 14
#define LED_SL 27
#define LED_SR 26

CRGB leds_home[NUM_LEDS];
CRGB leds_guest[NUM_LEDS];
CRGB leds_setshome[NUM_LEDS_MENOR];
CRGB leds_setsguest[NUM_LEDS_MENOR];

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

String device_name = "PLACAR";

// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;
int pontosDir=0;
int pontosEsq=0;
int setDir=0;
int setEsq=0;

void setup() {
  SerialBT.begin(device_name);  //Bluetooth device name
  FastLED.addLeds<WS2812, LED_L, GRB>(leds_home, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_R, GRB>(leds_guest, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_SL, GRB>(leds_setshome, NUM_LEDS_MENOR);
  FastLED.addLeds<WS2812, LED_SR, GRB>(leds_setsguest, NUM_LEDS_MENOR);
  FastLED.setBrightness(255);

  mostraNumeroMenor(0, leds_setshome, CRGB::Red);
  mostraNumeroMenor(0, leds_setsguest, CRGB::Red);

  for(int i=10; i>=0; i--){
    mostraNumero(i, leds_home, CRGB::Green);
    mostraNumero(i, leds_guest, CRGB::Blue);
    delay(700);
  }
}

void loop() {
  if (SerialBT.available()) {
    String dadosRecebidos = SerialBT.readString();
    processarDados(dadosRecebidos);
    mostraNumero(pontosDir, leds_home, CRGB::Green);
    mostraNumero(pontosEsq, leds_guest, CRGB::Blue);
    mostraNumeroMenor(setDir, leds_setshome, CRGB::Red);
    mostraNumeroMenor(setEsq, leds_setsguest, CRGB::Red);
  }
  delay(20);
}

void processarDados(String data){
  char dados[data.length()+1];
  data.toCharArray(dados, data.length()+1);

  char *token = strtok(dados, ",");
  if (token != NULL) {
    pontosDir = atoi(token);
    token = strtok(NULL, ",");
    if (token != NULL) {
      pontosEsq = atoi(token);
      token = strtok(NULL, ",");
      if (token != NULL) {
        setDir = atoi(token);
        token = strtok(NULL, ",");
        if (token != NULL) {
          setEsq = atoi(token);
        }
      }
    }
  }
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

void mostraNumeroMenor(int numero, CRGB *leds, CRGB cor) {
    if (numero < 0 || numero > 9) {
        // Tratar números inválidos (opcional)
        for (int i = 0; i < NUM_LEDS_MENOR; i++) {
            leds[i] = CRGB::Black; // Apaga tudo
        }
        FastLED.show();
        return;
    }
    
    int segmentoIndexUnidade = 0;

    for (int segmento = 0; segmento < 7; segmento++) {
        for (int i = 0; i < 3; i++) {
          leds[segmentoIndexUnidade++] = segmentos[numero][segmento] ? cor : CRGB::Black;
        }
    }
    FastLED.show();
}

