#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>
#include <L298NX2.h>

// Pin definition
const unsigned int EN_A = 3;
const unsigned int IN1_A = 5;
const unsigned int IN2_A = 6;

const unsigned int IN1_B = 7;
const unsigned int IN2_B = 8;
const unsigned int EN_B = 9;

// Initialize both motors
L298N motorD(EN_A, IN1_A, IN2_A);
L298N motorE(EN_A, IN1_A, IN2_A);

void setup() {
  // put your setup code here, to run once:
  Dabble.begin(9600);      //Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  float y = GamePad.getYaxisData();
  float x = GamePad.getXaxisData();
  int py = y*36;
  int px = x*36; 

  if(py >= 0){
    motorD.forward();
    motorE.forward();

    if (px <= 0){
      motorE.setSpeed(py + px);
    }else{
      motorD.setSpeed(py - px);
    }
  } else{
    motorD.backward();
    motorE.backward();
  }
}
