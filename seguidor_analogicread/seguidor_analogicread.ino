// Define os pinos dos sensores TCRT5000
#define sensorDir A0
#define sensorEsq A1

// Define o limiar para distinguir entre a linha e o fundo
int threshold = 400;

// Define os pinos dos motores no L298N
#define dirFrente 6
#define dirTras 5
#define esqFrente 10
#define esqTras 11

// Define as direções dos motores
#define FRENTE 1
#define PARADO 0
#define TRAS -1

 byte velocidade = 100;

// DECLARAÇÃO DE FUNÇÕES
void configMotor();
void motorEsq(int direcao);
void motorDir(int direcao);

void setup() {
  pinMode(sensorDir, INPUT);
  pinMode(sensorEsq, INPUT);
  configMotor();
}

void loop() {
  // Lê os valores dos sensores TCRT5000
  int valorSensorDir = analogRead(sensorDir);
  int valorSensorEsq = analogRead(sensorEsq);
  
  // Verifica os valores dos sensores e toma decisões com base neles
  if (valorSensorDir > threshold && valorSensorEsq > threshold) {
    // Ambos os sensores estão sobre a cor preta - siga em frente
    motorEsq(FRENTE);
    motorDir(FRENTE);
  } else if (valorSensorDir > threshold && valorSensorEsq <= threshold) {
    // Apenas o sensor da esquerda está sobre a linha branca - vire à esquerda
    motorEsq(TRAS);
    motorDir(FRENTE);
  } else if (valorSensorDir <= threshold && valorSensorEsq > threshold) {
    // Apenas o sensor da direita está sobre a linha branca - vire à direita
    motorEsq(FRENTE);
    motorDir(TRAS);
  }
}

// Função para configurar os pinos dos motores
void configMotor() {
  pinMode(dirFrente, OUTPUT);
  pinMode(dirTras, OUTPUT);
  pinMode(esqFrente, OUTPUT);
  pinMode(esqTras, OUTPUT);

  digitalWrite(dirFrente, LOW);
  digitalWrite(dirTras, LOW);
  digitalWrite(esqFrente, LOW);
  digitalWrite(esqTras, LOW);
}

// Função para controlar o motor esquerdo
void motorEsq(int direcao) {
  switch (direcao) {
    case -1:
      digitalWrite(esqFrente, LOW);
      analogWrite(esqTras, velocidade);
      break;
    case 0:
      digitalWrite(esqFrente, HIGH);
      digitalWrite(esqTras, HIGH);
      break;
    case 1:
      analogWrite(esqFrente, velocidade);
      digitalWrite(esqTras, LOW);
      break;
  }
}

// Função para controlar o motor direito
void motorDir(int direcao) {
  switch (direcao) {
    case -1:
      digitalWrite(dirFrente, LOW);
      analogWrite(dirTras, velocidade);
      break;
    case 0:
      digitalWrite(dirFrente, HIGH);
      digitalWrite(dirTras, HIGH);
      break;
    case 1:
      analogWrite(dirFrente, velocidade);
      digitalWrite(dirTras, LOW);
      break;
  }
}