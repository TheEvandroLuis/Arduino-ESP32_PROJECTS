#define DirFrente 10
#define DirTras 9
#define EsqFrente 8
#define EsqTras 7

#define EEsq A0
#define EDir A1

void moveFrente(int velocidade){
  analogWrite(EDir, velocidade);
  digitalWrite(DirFrente, HIGH);
  digitalWrite(DirTras, LOW);
  analogWrite(EEsq, velocidade);
  digitalWrite(EsqFrente, HIGH);
  digitalWrite(EsqTras, LOW);
}

void frenteDireita(){
  digitalWrite(DirFrente, LOW);
  digitalWrite(DirTras, LOW);
  
  digitalWrite(EsqFrente, HIGH);
  digitalWrite(EsqTras, LOW);
}

void frenteEsquerda(){
  digitalWrite(DirFrente, HIGH);
  digitalWrite(DirTras, LOW);
  
  digitalWrite(EsqFrente, LOW);
  digitalWrite(EsqTras, LOW);
}

void moveRe(int velocidade){
  analogWrite(EDir, velocidade);
  digitalWrite(DirFrente, LOW);
  digitalWrite(DirTras, HIGH);
  analogWrite(EEsq, velocidade);
  digitalWrite(EsqFrente, LOW);
  digitalWrite(EsqTras, HIGH);
}

void reDireita(){
  digitalWrite(DirFrente, LOW);
  digitalWrite(DirTras, LOW);

  digitalWrite(EsqFrente, LOW);
  digitalWrite(EsqTras, HIGH);
}

void reEsquerda(){
  digitalWrite(DirFrente, LOW);
  digitalWrite(DirTras, HIGH);

  digitalWrite(EsqFrente, LOW);
  digitalWrite(EsqTras, HIGH);
}

void direita(){
  digitalWrite(DirFrente, LOW);
  digitalWrite(DirTras, HIGH);

  digitalWrite(EsqFrente, HIGH);
  digitalWrite(EsqTras, LOW);
}

void esquerda(){
  digitalWrite(DirFrente, HIGH);
  digitalWrite(DirTras, LOW);

  digitalWrite(EsqFrente, LOW);
  digitalWrite(EsqTras, HIGH);
}

void parar(){
  digitalWrite(DirFrente, LOW);
  digitalWrite(DirTras, LOW);

  digitalWrite(EsqFrente, LOW);
  digitalWrite(EsqTras, LOW);
}
