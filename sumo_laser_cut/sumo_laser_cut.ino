/******************************************************************************************
 * Mapa do Sketch
 * 1- Cabeçalho (bibliotecas, definições, variáveis e objetos globais)
 * 2- setup()
 * 3- loop()
 * 4- ci74HC595Write()
 * 5- delayPWM()
 * 
 * Desenvolvido por Ideias Tecnologia / Brincando com Ideias
 */

#include <Servo.h>

#define pinSH_CP  4   //Pino Clock  DIR_CLK
#define pinST_CP  12  //Pino Latch  DIR_LATCH
#define pinDS     8   //Pino Data   DIR_SER
#define pinEnable 7   //Pino Enable DIR_EN

#define pinMotor1PWM 11
#define pinMotor2PWM 3
#define pinMotor3PWM 5
#define pinMotor4PWM 6

#define pinServo1 10
#define pinServo2 9

#define qtdeCI   1

#define bitMotor1A 2
#define bitMotor1B 3
#define bitMotor2A 1
#define bitMotor2B 4
#define bitMotor3A 5
#define bitMotor3B 7
#define bitMotor4A 0
#define bitMotor4B 6

void ci74HC595Write(byte pino, bool estado);

void setup() {
   pinMode(pinSH_CP, OUTPUT);
   pinMode(pinST_CP, OUTPUT);
   pinMode(pinEnable, OUTPUT);
   pinMode(pinDS, OUTPUT);

   pinMode(pinMotor1PWM, OUTPUT);
   pinMode(pinMotor2PWM, OUTPUT);
   pinMode(pinMotor3PWM, OUTPUT);
   pinMode(pinMotor4PWM, OUTPUT);

   digitalWrite(pinEnable, LOW);

}

void loop() {
  ci74HC595Write(bitMotor1A, HIGH);
  ci74HC595Write(bitMotor1B, LOW);
  ci74HC595Write(bitMotor2A, HIGH);
  ci74HC595Write(bitMotor2B, LOW);  
}

void ci74HC595Write(byte pino, bool estado) {
  static byte ciBuffer[qtdeCI];

  bitWrite(ciBuffer[pino / 8], pino % 8, estado);
  
  digitalWrite(pinST_CP, LOW); //Inicia a Transmissão
  
  digitalWrite(pinDS, LOW);    //Apaga Tudo para Preparar Transmissão
  digitalWrite(pinSH_CP, LOW);

  for (int nC = qtdeCI-1; nC >= 0; nC--) {
      for (int nB = 7; nB >= 0; nB--) {
  
          digitalWrite(pinSH_CP, LOW);  //Baixa o Clock      
          
          digitalWrite(pinDS,  bitRead(ciBuffer[nC], nB) );     //Escreve o BIT
          
          digitalWrite(pinSH_CP, HIGH); //Eleva o Clock
          digitalWrite(pinDS, LOW);     //Baixa o Data para Previnir Vazamento      
      }  
  }
  
  digitalWrite(pinST_CP, HIGH);  //Finaliza a Transmissão
}
