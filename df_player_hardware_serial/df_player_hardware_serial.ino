#include "DFRobotDFPlayerMini.h"
DFRobotDFPlayerMini myDFPlayer;
 
//botões
int botao1 = 7;
int botao2 = 6;
int botao3 = 5;
int botao4 = 4;
int botao5 = 3;
int botao6 = 2;
 
//Led
int led1 = 8;
int led2 = 9;
int led3 = 10;
int led4 = 11;
int led5 = 12;
int led6 = 13;
 
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myDFPlayer.begin(Serial);
  myDFPlayer.volume(30);
 
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);
  pinMode(botao3, INPUT_PULLUP);
  pinMode(botao4, INPUT_PULLUP);
  pinMode(botao5, INPUT_PULLUP);
  pinMode(botao6, INPUT_PULLUP);
 
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(botao1)==LOW){
    myDFPlayer.playFolder(1, 1);
    digitalWrite(led1, HIGH);
    delay(5000);
    digitalWrite(led1, LOW);
  }
  
   if(digitalRead(botao2)==LOW){
    myDFPlayer.playFolder(1, 2);
    digitalWrite(led2, HIGH);
    delay(5000);
    digitalWrite(led2, LOW);
  }
     if(digitalRead(botao3)==LOW){
    myDFPlayer.playFolder(1, 3);
    digitalWrite(led3, HIGH);
    delay(5000);
    digitalWrite(led3, LOW);
  }
   if(digitalRead(botao4)==LOW){
    myDFPlayer.playFolder(1, 4);
    digitalWrite(led4, HIGH);
    delay(5000);
    digitalWrite(led4, LOW);
  }
   if(digitalRead(botao5)==LOW){
    myDFPlayer.playFolder(1, 5);
    digitalWrite(led5, HIGH);
    delay(5000);
    digitalWrite(led5, LOW);
  }
   if(digitalRead(botao6)==LOW){
    myDFPlayer.playFolder(1, 6);
    digitalWrite(led6, HIGH);
    delay(5000);
    digitalWrite(led6, LOW);
  }
}