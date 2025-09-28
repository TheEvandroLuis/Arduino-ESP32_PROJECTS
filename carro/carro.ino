/*
   BYJ48 Stepper motor code
   Connect :
   IN1 >> D8
   IN2 >> D9
   IN3 >> D10
   IN4 >> D11
   VCC ... 5V Prefer to use external 5V Source
   Gnd
   written By :Mohannad Rawashdeh
https://www.instructables.com/member/Mohannad+Rawashdeh/
     28/9/2013
  */

#define IN1  8
#define IN2  9
#define IN3  10
#define IN4  11
#define IN5  4
#define IN6  5
#define IN7  6
#define IN8  7

long time;
void setup()
{
pinMode(IN1, OUTPUT); 
pinMode(IN2, OUTPUT); 
pinMode(IN3, OUTPUT); 
pinMode(IN4, OUTPUT); 

pinMode(IN5, OUTPUT); 
pinMode(IN6, OUTPUT); 
pinMode(IN7, OUTPUT); 
pinMode(IN8, OUTPUT); 
// delay(1000);

}
void loop()
{
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);

     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, HIGH);
}
/*
void stepper(int xw){
  for (int x=0;x<xw;x++){
switch(Steps){
   case 0:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);

     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, HIGH);
     
   break; 
   case 1:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, HIGH);

     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, HIGH);
     digitalWrite(IN8, HIGH);
   break; 
   case 2:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);

     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, HIGH);
     digitalWrite(IN8, LOW);
   break; 
   case 3:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);

     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, HIGH);
     digitalWrite(IN7, HIGH);
     digitalWrite(IN8, LOW);
   break; 
   case 4:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);

     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, HIGH);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, LOW);
   break; 
   case 5:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);

     digitalWrite(IN5, HIGH); 
     digitalWrite(IN6, HIGH);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, LOW);
   break; 
     case 6:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);

     digitalWrite(IN5, HIGH); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, LOW);
   break; 
   case 7:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);

     digitalWrite(IN5, HIGH); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, HIGH);
   break; 
   default:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);

     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, LOW);
   break; 
}
}
} */
