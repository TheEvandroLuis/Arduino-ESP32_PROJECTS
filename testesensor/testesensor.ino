void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int esq = analogRead(A0);
  int dir = analogRead(A1);
  int erro;

  Serial.print("esq: ");
  Serial.print(esq);
  Serial.print(" dir: ");
  Serial.print(dir);
  erro = esq -dir;
  erro = erro*0.5; 
  Serial.print(" erro: ");
  Serial.println(erro);
}
