#include <L298N.h>

#define BOTAO 10
#define LED 7

//MOTOR DIREITO
const unsigned int EN_A = 3;
const unsigned int IN1_A = 1;
const unsigned int IN2_A = 2;
L298N motorDir(EN_A, IN1_A, IN2_A);
//MOTOR ESQ
const unsigned int IN1_B = 4;
const unsigned int IN2_B = 5;
const unsigned int EN_B = 6;
L298N motorEsq(EN_B, IN1_B, IN2_B);

//VARIAIVEIS PARA CALCULO PID
float kp = 1.2; //3.34; 3.24; 3.2; 3.3; 3.4; 3; 3.15
float kd = 0; //2.7; 2.45; 2.4; 2 
int P;
int D;
int erro, correcao;
int ultimoErro = 0;

//VARIAVEIS PARA VELOCIDADE
int velocidadeBase = 150; 
int velocidadeEsq, velocidadeDir;
int velocidadeMax = 250;
int velocidadeMin = -250;
int minimoParaAndar = -60;

void setup() {
  pinMode(BOTAO,INPUT_PULLUP);
	pinMode(LED,OUTPUT);
  Serial.begin(9600);

  while(digitalRead(BOTAO) != LOW){//espero apertar e fico piscando
    digitalWrite(LED,HIGH);
    delay(100);
    digitalWrite(LED,LOW);
    delay(100);
  }
}
 
void loop() {

  
  //CALCULO DO ERRO
  int esq = analogRead(A0);
  int dir = analogRead(A1);
  erro = esq-dir;
/*
  Serial.print("ESQ: ");
  Serial.print(esq);
  Serial.print(" DIR: ");
  Serial.print(dir);
  Serial.println();
*/
//  delay(20);

  //CALCULO PID
  P = erro;
  D = erro - ultimoErro;
  ultimoErro = erro;
  correcao = P*kp + D*kd;

  velocidadeEsq = velocidadeBase + correcao;
  velocidadeDir = velocidadeBase - correcao;
  
  if(velocidadeEsq>255)velocidadeEsq = 255;
  else if(velocidadeEsq<-255) velocidadeEsq = -255;

  if (velocidadeEsq >= 0) velocidadeEsq = map (velocidadeEsq, 0, 255, 70, 255);
  else velocidadeEsq = map (velocidadeEsq, 0, -255, -70, -255);

  if(velocidadeDir>255)velocidadeDir = 255;
  else if(velocidadeDir<-255) velocidadeDir = -255;

  //ACERTA A DIREÇÃO DO MOTOR DIREITO
  if (velocidadeDir >= 0) velocidadeDir = map (velocidadeDir, 0, 255, 70, 255);
  else if (velocidadeDir < 0) velocidadeDir = map (velocidadeDir, 0, -255, -70, -255); //teste: -80; senao:-70

  //ENVIA AS VELOCIDADES PARA OS MOTORES
  motorEsq.setSpeed(abs(velocidadeEsq));
  motorDir.setSpeed(abs(velocidadeDir));
/*
  Serial.print("ESQ: ");
  Serial.print(velocidadeEsq);
  Serial.print(" DIR: ");
  Serial.print(velocidadeDir);
  Serial.println();
*/
  
  //ACERTA A DIREÇÃO DO MOTOR ESQUERDO
  if (velocidadeEsq >= 0) motorEsq.forward();
  else motorEsq.backward();

  //ACERTA A DIREÇÃO DO MOTOR DIREITO
  if (velocidadeDir >= 0) motorDir.forward();
  else motorDir.backward();  


}