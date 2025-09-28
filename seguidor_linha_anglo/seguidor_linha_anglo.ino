#include <L298N.h>

// Pin definition
const unsigned int EN_A = 3;
const unsigned int IN1_A = 5;
const unsigned int IN2_A = 6;
const unsigned int IN1_B = 7;
const unsigned int IN2_B = 8;
const unsigned int EN_B = 9;
#define sensorEsq A0
#define sensorDir A1

// Initialize both motors
L298N motorEsq(EN_A, IN1_A, IN2_A);
L298N motorDir(EN_B, IN1_B, IN2_B);

//CONSTANTES
#define velocidadeBase 200 //200
int leituraEsq, leituraDir;
float kp = 5.2;  //4.8
float ki = 0.0002; //0.0002
float kd = 2.4; //2.4
int P;
int I =0;
int D;
int erro, correcao;
int ultimoErro = 0;

int velEsq, velDir;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  leituraEsq = map(analogRead(sensorEsq), 0, 1023, 100, 0);
  leituraDir = map(analogRead(sensorDir), 0, 1023, 100, 0);

  //CALCULA O ERRO
  erro = leituraEsq - leituraDir;

  //CALCULA CORRECAO
  P = erro;
  I = I + erro;
  D = erro - ultimoErro;
  ultimoErro = erro;
  correcao = P*kp + I*ki + D*kd;

  velEsq = velocidadeBase - correcao;
  velDir = velocidadeBase + correcao;

  if(velEsq>255) velEsq=255;
  else if(velEsq<-255)velEsq=-255;
  if(velDir>255) velDir=255;
  else if(velDir<-255)velDir=-255;
  
  motorEsq.setSpeed(abs(velEsq));
  motorDir.setSpeed(abs(velDir));

  if(velEsq>=0){
    motorEsq.forward();
  }else{
    motorEsq.backward();
  }
   if(velDir>=0){
    motorDir.forward();
  }else{
    motorDir.backward();
  }
}