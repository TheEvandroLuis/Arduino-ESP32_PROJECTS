#include "sensorLinhaPro.h"
#include <L298N.h>

#define BOTAO 10
#define LED 7
#define APERTADO LOW
#define PINO_CONTADOR_VOLTA 4
#define MARCACOES_TOTAIS 4
#define LEITURA_LINHA_PRA_CONSIDERAR_MARCACAO 2
#define CONSIDERADO_BRANCO LOW

uint16_t contadorMarcacao = 0;
uint8_t quantidadeMarcacoes = 0;
uint8_t ledAceso = 0;

// MOTORES 
 #define ESQ_T 1 // ESQUERDA TRAS
 #define ESQ_F 2 // ESQUERDA FRENTE
 #define ESQ_PWM 3 // ESQUERDA PWM
 #define DIR_T 4 // DIREITA TRAS
 #define DIR_F 5 // DIREITA FRENTE
 #define DIR_PWM 6 // DIREITA PWM

L298N motorEsq(ESQ_PWM, ESQ_F, ESQ_T);
L298N motorDir(DIR_PWM, DIR_F, DIR_T);

void inciarMotores(int velEsq, int velDir);

//algoritmo PID
int erro = 0;
float Kp = 2;//2---;4
float Kd = 0;//0---;0
int erroAnterior;
int potenciaMotorDireito;
int potenciaMotorEsquerdo;
int velocidade = 255;//255----;500

//RX-TX
SensorLinhaPro sensor;

void setup(){
	pinMode(BOTAO,INPUT_PULLUP);

	pinMode(LED,OUTPUT);
  pinMode(PINO_CONTADOR_VOLTA, INPUT);
  
    Serial.begin(9600); //38400
    Serial.println("Comecou...");
    sensor.begin(12,13);

    if(digitalRead(BOTAO) == APERTADO){
        while(digitalRead(BOTAO) == APERTADO){//espero desapertar
            //vou piscar o led
            digitalWrite(LED,HIGH);
            delay(200);
            digitalWrite(LED,LOW);
            delay(200);
        }

        while(digitalRead(BOTAO) != APERTADO){//espero apertar e fico piscando
            digitalWrite(LED,HIGH);
            delay(100);
            digitalWrite(LED,LOW);
            delay(100);
        }
        delay(2000);
        sensor.calibraFora();

        while(digitalRead(BOTAO) != APERTADO){//espero apertar e fico piscando
            digitalWrite(LED,HIGH);
            delay(100);
            digitalWrite(LED,LOW);
            delay(100);
        }
        delay(2000);
        sensor.calibraLinha();
        
        
    }
	
	//espera o botao ser apertado pra começar a correr
	while(digitalRead(BOTAO) != APERTADO){//espero apertar e fico piscando
            digitalWrite(LED,HIGH);
            delay(100);
            digitalWrite(LED,LOW);
            delay(100);
  }

  TCCR1A = 0b10100001; //clear on compare / fast pwm
  TCCR1B = 0b00001100;
  OCR1A = 0;
  //digitalWrite(MOTOR1_PINO2, LOW);
  OCR1B = 0;
  //digitalWrite(MOTOR2_PINO2, LOW);
	//pinMode(MOTOR1_PINO1_PWM, OUTPUT);
	//pinMode(MOTOR2_PINO1_PWM, OUTPUT);
	//digitalWrite(MOTOR2_PINO1_PWM , LOW);
	//digitalWrite(MOTOR2_PINO1_PWM , LOW);
  delay(2000);
	/*while(1){
    //digitalWrite(MOTOR2_PINO2, LOW);
    //digitalWrite(MOTOR2_PINO1_PWM, HIGH);
		setMotorSpeed(40,40);
		delay(3000);
		setMotorSpeed(-40,-40);
    //digitalWrite(MOTOR2_PINO2, HIGH);
    //digitalWrite(MOTOR2_PINO1_PWM, LOW);
		delay(3000);
	}*/
  /*while(1){
    Serial.println(digitalRead(PINO_CONTADOR_VOLTA));
    delay(100);
  }
  */
}

void loop(){
    if(sensor.le()){
        erro = sensor.getValor();
        
        Serial.print("ERRO: ");
        Serial.println(erro);
 
		//return;
		potenciaMotorDireito = velocidade - ((int)((erro*Kp) + Kd*(erro - erroAnterior)));
		potenciaMotorEsquerdo = velocidade + ((int)((erro*Kp) + Kd*(erro - erroAnterior)));
		erroAnterior = erro;
    
    /*
    uint8_t leituraDigital = digitalRead(PINO_CONTADOR_VOLTA);
      //Serial.println(leituraAnalogica);
      if(leituraDigital == CONSIDERADO_BRANCO){
        contadorMarcacao++;
      }else{
        contadorMarcacao=0;
      }
      if(contadorMarcacao == LEITURA_LINHA_PRA_CONSIDERAR_MARCACAO){
        Serial.println("detectei");
        //delay(300);
        //toma acao  
        quantidadeMarcacoes++;
          if(quantidadeMarcacoes==MARCACOES_TOTAIS){
            while(1){
              setMotorSpeed(0, 0);
              digitalWrite(LED,HIGH);
              delay(200);
              digitalWrite(LED,LOW);
              delay(200);
            }
          }
        ledAceso = 200;
        digitalWrite(LED,HIGH);
      }
        ledAceso--;
        if(ledAceso <= 0){
          ledAceso = 0;
          digitalWrite(LED, LOW);
        }
        delay(1);
      */

	inciarMotores(potenciaMotorEsquerdo, potenciaMotorDireito);

	} 
}

void inciarMotores(int velEsq, int velDir){

  if (velEsq>255) velEsq = 255;
  else if (velEsq<-255) velEsq = -255;

  if (velDir>255) velDir = 255;
  else if (velDir<-255) velDir = -255;

  motorEsq.setSpeed(abs(velEsq));
  motorDir.setSpeed(abs(velDir));

  if(velEsq>=0) motorEsq.forward();
  else if(velEsq<0) motorEsq.backward();

  if(velDir>=0) motorDir.forward();
  else if(velDir<0) motorDir.backward();
 /*
  if(velEsq>=0){
    if (velEsq>255) velEsq = 255;
    velEsq = map(velEsq, 0, 255, 100, 255);
    motorEsq.setSpeed(abs(velEsq));
    motorEsq.forward();
  }
  else if(velEsq<0){
    if (velEsq<-255) velEsq = -255;
    velEsq = map(velEsq, -255, 0, -255, -100);
    motorEsq.setSpeed(abs(velEsq));
    motorEsq.backward();
  }
  if(velDir>=0){
    motorDir.forward();
    if (velDir>255) velDir = 255;
    velDir = map(velDir, 0, 255, 100, 255);
    motorDir.setSpeed(abs(velDir));
    motorDir.forward();    
  }
  else if(velDir<0){
    if (velDir<-255) velDir = -255;
    velDir = map(velDir, -255, 0, -255, -100);
    motorDir.setSpeed(abs(velDir));
    motorDir.backward();
  }
  /*
  Serial.print("   ");
  Serial.print(velEsq);
  Serial.print(" || ");
  Serial.println(velDir);
  */
}