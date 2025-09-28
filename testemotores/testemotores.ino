#include <L298N.h>

//MOTOR ESQUERDA
const unsigned int EN_A = 3;
const unsigned int IN1_A = 5;
const unsigned int IN2_A = 6;
L298N motorDir(EN_A, IN1_A, IN2_A);
//MOTOR DIREITA
const unsigned int IN1_B = 7;
const unsigned int IN2_B = 8;
const unsigned int EN_B = 9;
L298N motorEsq(EN_B, IN1_B, IN2_B);

int i = 85;

void setup(){
  motorEsq.setSpeed(i);
  motorDir.setSpeed(i);
}

void loop(){
  
    motorEsq.backward();
    motorDir.backward();

}