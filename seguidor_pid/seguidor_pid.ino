// Define os pinos dos sensores TCRT5000
#define sensorDir A0
#define sensorEsq A1

// Define os pinos dos motores no L298N
#define dirFrente 6
#define dirTras 5
#define esqFrente 10
#define esqTras 11

// Define as direções dos motores
#define FRENTE 1
#define PARADO 0
#define TRAS -1

// Parâmetros do PID
float kp = 0.8;  // Ganho proporcional
float ki = 0.1;  // Ganho integral
float kd = 0.2;  // Ganho derivativo
int erroAnterior = 0;
int erroIntegral = 0;

// DECLARAÇÃO DE FUNÇÕES
void configMotor();
void motorEsq(int direcao, byte velocidade);
void motorDir(int direcao, byte velocidade);

void setup() {
  pinMode(sensorDir, INPUT);
  pinMode(sensorEsq, INPUT);
  configMotor();
}

void loop() {
  // Lê os valores dos sensores TCRT5000
  int valorSensorDir = analogRead(sensorDir);
  int valorSensorEsq = analogRead(sensorEsq);

  // Calcula o erro como a diferença entre os sensores
  int erro = valorSensorEsq - valorSensorDir;

  // Calcula os componentes PID
  int termoP = kp * erro;
  erroIntegral += erro;
  int termoI = ki * erroIntegral;
  int termoD = kd * (erro - erroAnterior);

  // Calcula a saída PID
  int saidaPID = termoP + termoI + termoD;

  // Aplica a saída PID para controlar os motores
  motorEsq(FRENTE, 255 - saidaPID);
  motorDir(FRENTE, 255 + saidaPID);

  // Atualiza o erro anterior para o próximo ciclo
  erroAnterior = erro;

  delay(10); // Aguarda um curto intervalo antes de ler os sensores novamente
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
void motorEsq(int direcao, byte velocidade) {
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
void motorDir(int direcao, byte velocidade) {
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
