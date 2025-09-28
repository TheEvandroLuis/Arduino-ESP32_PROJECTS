#define trigPin 2
#define echoPin 3

#define led1 7
#define led2 8
#define led3 9 
#define led4 10
#define led5 11
#define led6 12


long duration;
int distance;
int ledLevel;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Gera um pulso no pino trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Lê a duração do pulso do pino echoPin
  duration = pulseIn(echoPin, HIGH);

  // Calcula a distância em centímetros
  distance = (duration / 2) / 29.1;

  // Ajusta o nível dos LEDs com base na distância
  if (distance <= 10) {
    ledLevel = 6;
  } else if (distance <= 20) {
    ledLevel = 5;
  } else if (distance <= 30) {
    ledLevel = 4;
  } else if (distance <= 40) {
    ledLevel = 3;
  } else if (distance <= 50) {
    ledLevel = 2;
  } else if (distance <=60) {
    ledLevel = 1;
  }else{
    ledLevel = 0;
  }

  // Acende os LEDs com base no nível calculado
  for (int i = 7; i <= 12; i++) {
    if (i - 6 <= ledLevel) {
      digitalWrite(i, HIGH);
    } else {
      digitalWrite(i, LOW);
    }
  }

  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(100); // Aguarda um curto período para evitar leituras rápidas repetidas
}