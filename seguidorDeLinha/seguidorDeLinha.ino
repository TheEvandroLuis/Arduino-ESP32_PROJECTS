/*
     CÓDIGO:	  Q0702
     AUTOR:		  BrincandoComIdeias
     ACOMPANHE:	https://www.youtube.com/brincandocomideias ; https://www.instagram.com/canalbrincandocomideias/
     APRENDA:	  https://cursodearduino.net/ ; https://cursoderobotica.net
     COMPRE:	  https://www.arducore.com.br/
     SKETCH:    Seguidor de Linha
     DATA:		  22/09/2021
*/

// DEFINIÇÕES DE PINOS
#define pinSensorDir 4
#define pinSensorEsq 12
 
#define dirFrente 6
#define dirTras   5
#define esqFrente 10
#define esqTras   11

// DEFINIÇÕES
#define LINHA LOW

#define FRENTE  1
#define PARADO  0
#define TRAS   -1

// DECLARAÇÃO DE FUNÇÕES
void configMotor();
void motorEsq(int direcao, byte velocidade = 80);
void motorDir(int direcao, byte velocidade = 95);

// DECLARAÇÃO DE VARIÁVEIS
bool leituraEsquerda;
bool leituraDireita;

void setup() {
  Serial.begin(9600);

  pinMode(pinSensorDir, INPUT);
  pinMode(pinSensorEsq, INPUT);

  configMotor();
}

void loop() {
  bool valE = digitalRead(pinSensorEsq);
  bool valD = digitalRead(pinSensorDir);

  if (valE == LINHA && valD == LINHA) {
    motorEsq(PARADO);
    motorDir(PARADO);
    delay(300);
    motorEsq(TRAS);
    motorDir(TRAS);
    delay(150);
    motorEsq(PARADO);
    motorDir(PARADO);
    delay(3000);
  } else if (valD == LINHA) {
    motorEsq(FRENTE, 100);
    motorDir(TRAS, 100);
  } else if (valE == LINHA) {
    motorEsq(TRAS, 100);
    motorDir(FRENTE, 100);
  } else {
    motorEsq(FRENTE);
    motorDir(FRENTE);
  }
}



// IMPLEMENTO DE FUNÇÕES

void configMotor() {
  pinMode(dirFrente,  OUTPUT);
  pinMode(dirTras,    OUTPUT);
  pinMode(esqFrente,  OUTPUT);
  pinMode(esqTras,    OUTPUT);

  digitalWrite(dirFrente,  LOW);
  digitalWrite(dirTras,    LOW);
  digitalWrite(esqFrente,  LOW);
  digitalWrite(esqTras,    LOW);
}

void motorEsq(int direcao, byte velocidade = 80) {
  switch (direcao) {
    case -1: {
        //        Serial.println("Esq Trás");
        digitalWrite(esqFrente,  LOW);
        analogWrite (esqTras,    velocidade);
        break;
      }
    case 0: {
        //        Serial.println("Esq PARADOdo");
        digitalWrite(esqFrente,  HIGH);
        digitalWrite(esqTras,    HIGH);
        break;
      }
    case 1: {
        //        Serial.println("Esq Frente");
        analogWrite (esqFrente,  velocidade);
        digitalWrite(esqTras,    LOW);
        break;
      }
  }
}

void motorDir(int direcao, byte velocidade = 95) {
  switch (direcao) {
    case -1: {
        //        Serial.println("Dir Trás");
        digitalWrite(dirFrente,  LOW);
        analogWrite (dirTras,    velocidade);
        break;
      }
    case 0: {
        //        Serial.println("Dir PARADOdo");
        digitalWrite(dirFrente,  HIGH);
        digitalWrite(dirTras,    HIGH);
        break;
      }
    case 1: {
        //        Serial.println("Dir Frente");
        analogWrite (dirFrente,  velocidade);
        digitalWrite(dirTras,    LOW);
        break;
      }
  }
}
