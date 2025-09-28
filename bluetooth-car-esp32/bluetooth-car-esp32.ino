#include "motor.h"
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

void setup() {
  // put your setup code here, to run once:
  Dabble.begin("MyEsp32");       //set bluetooth name of your device
  pinMode(DirFrente, OUTPUT);
  pinMode(DirTras, OUTPUT);
  pinMode(EsqFrente, OUTPUT);
  pinMode(EsqTras, OUTPUT);
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  if (GamePad.isUpPressed())
  {
    moveFrente();
  }

  else if (GamePad.isDownPressed())
  {
    moveRe();
  }

  else if (GamePad.isLeftPressed())
  {
    esquerda();
  }

  else if (GamePad.isRightPressed())
  {
    direita();
  }
  else{
    parar();
  }
}
