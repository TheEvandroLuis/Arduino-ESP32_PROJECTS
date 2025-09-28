 #define ESQ_T 1 // ESQUERDA TRAS
 #define ESQ_F 2 // ESQUERDA FRENTE
 #define ESQ_PWM 3 // ESQUERDA PWM
 #define DIR_T 4 // DIREITA TRAS
 #define DIR_F 5 // DIREITA FRENTE
 #define DIR_PWM 6 // DIREITA PWM

void configuraMotor(){
  pinMode(ESQ_T, OUTPUT); // ESQUERDA TRAS
  pinMode(ESQ_F, OUTPUT); // ESQUERDA FRENTE
  pinMode(ESQ_PWM, OUTPUT); // ESQUERDA PWM
  pinMode(DIR_T, OUTPUT); // DIREITA TRAS
  pinMode(DIR_F, OUTPUT); // DIREITA FRENTE
  pinMode(DIR_PWM, OUTPUT); // DIREITA PWM
}

void inciarMotores(int velEsq, int velDir){
  if(velEsq>0){
    digitalWrite(ESQ_T, LOW);
    digitalWrite(ESQ_F, HIGH);
    if (velEsq>255) velEsq = 255;
  }
  if(velEsq<0){
    digitalWrite(ESQ_F, LOW);
    digitalWrite(ESQ_T, HIGH);
    if (velEsq<-255) velEsq = -255;
  }
  if(velDir>0){
    digitalWrite(DIR_T, LOW);
    digitalWrite(DIR_F, HIGH);
    if (velDir>255) velDir = 255;
  }
  if(velDir<0){
    digitalWrite(DIR_F, LOW);
    digitalWrite(DIR_T, HIGH);
    if (velDir<-255) velDir = -255;
  }
  
  analogWrite(ESQ_PWM, abs(velEsq));
  analogWrite(DIR_PWM, abs(velDir));
}



void setup() {
  // put your setup code here, to run once:
  configuraMotor();
}

void loop() {
  // put your main code here, to run repeatedly:
  inciarMotores(400, -400);
  
}
