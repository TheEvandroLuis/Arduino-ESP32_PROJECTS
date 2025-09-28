// C++ code
//
#define vermelho 9
#define azul 8
#define verde 7

void setup()
{
  pinMode(vermelho, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(verde, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  Serial.print("Valor do vermelho? ");
  while(Serial.available()==0){}
  int r =Serial.parseInt();
  Serial.println();

  Serial.print("Valor do verde? ");
  while(Serial.available()==0){}
  int g =Serial.parseInt();
  Serial.println();

  Serial.print("Valor do azul? ");
  while(Serial.available()==0){}
  int b =Serial.parseInt();
  Serial.println();

  definirCor(v, g, b);
}

void definirCor(int r, int g, int b){
  analogWrite(vermelho, r);
  analogWrite(verde, g);
  analogWrite(azul, b);
}



