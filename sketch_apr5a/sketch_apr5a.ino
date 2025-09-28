#include <L298N.h>

// Pin definition
const unsigned int EN_A = 3;
const unsigned int IN1_A = 5;
const unsigned int IN2_A = 6;

const unsigned int IN1_B = 7;
const unsigned int IN2_B = 8;
const unsigned int EN_B = 9;

// Initialize both motors
L298N motorEsq(EN_A, IN1_A, IN2_A);
L298N motorDir(EN_B, IN1_B, IN2_B);

//variaveis

int erro = 0;
float kp = 1;
int velocidadeBase =50;
int velEsq, velDir;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int esq = analogRead(A0);
  int dir = analogRead(A1);

  Serial.print("esq ");
  Serial.print(esq);
  Serial.print(" dir ");
  Serial.print(dir );

  erro = esq-dir;
  erro = erro*kp;

  velEsq = velocidadeBase - erro;
  
 Serial.print(" erro ");
 Serial.println( erro*kp );
}
