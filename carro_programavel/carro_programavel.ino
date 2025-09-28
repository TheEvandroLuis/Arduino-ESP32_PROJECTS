#define IN1  8
#define IN2  9
#define IN3  10
#define IN4  11
#define IN5  4
#define IN6  5
#define IN7  6
#define IN8  7

const int botao_frente = 1;
const int botao_direita = 1;
const int botao_esquerda = 1;
const int led = 13;

enum movimento {
  frente,
  direita,
  esquerda,
  parado
};

int qtd_comandos=0;
movimento memoria[20];

const byte interruptPlay = 2;
const byte interruptApagar = 2;

void setup(){
  Serial.begin(9600);
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT);   
  pinMode(IN5, OUTPUT); 
  pinMode(IN6, OUTPUT); 
  pinMode(IN7, OUTPUT); 
  pinMode(IN8, OUTPUT); 

  pinMode(botao_frente, INPUT);
  pinMode(botao_direita, INPUT);
  pinMode(botao_esquerda, INPUT);

  pinMode(led, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(interruptPlay), iniciar, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptApagar), apagar, CHANGE);
}
void loop(){
  mover_frente();
  delay(5000);

  /*
   * if (digitalRead(botao_frente)==0){
   *  memoria[qtd_comandos] = frente;
   *  qtd_comandos++;
   * }
   * else if (digitalRead(botao_direita)){
   *  memoria[qtd_comandos] = direita;
   *  qtd_comandos++;
   * }
   * else if (digitalRead(botao_esquerda)){
   *  memoria[qtd_comandos] = esquerda;
   *  qtd_comandos++;
   * }
   */
}

void iniciar(){
  for(int i=0; i<qtd_comandos; i++){
    switch (memoria[i]){
      case frente:
        mover_frente();
        break;

      case direita:
        mover_direita();
        break;

      case esquerda:
        mover_esquerda();
        break;

      default:
        break;
    }
    delay(1000);
  }
}

void apagar(){
  for(int i=0; i<qtd_comandos; i++){
    memoria[i] = parado;
  }
  qtd_comandos = 0;
}
void mover_frente(){
  Serial.println("Frente");
  for (int i=0; i<100; i++){
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
     digitalWrite(IN5, HIGH); 
     digitalWrite(IN6, HIGH);
     digitalWrite(IN7, HIGH);
     digitalWrite(IN8, LOW);
  }     
}

void mover_direita(){
  Serial.println("Direita");   
}

void mover_esquerda(){
  Serial.println("Esquerda");   
}
