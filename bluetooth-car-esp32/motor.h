#define DirFrente 4
#define DirTras 12
#define EsqFrente 2
#define EsqTras 13

void moveFrente(){
  digitalWrite(DirFrente, HIGH);
  digitalWrite(DirTras, LOW);
  
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

void moveRe(){
  digitalWrite(DirFrente, LOW);
  digitalWrite(DirTras, HIGH);
  
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
