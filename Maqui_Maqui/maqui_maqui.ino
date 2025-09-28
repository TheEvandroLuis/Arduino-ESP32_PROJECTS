/*
 ************************************************
 ************** MAKEY MAKEY *********************
 ************************************************
  
 //////////////////////////////////////////////////
 ///////// MaKey MaKey FIRMWARE v1.4.1 ////////////
 //////////////////////////////////////////////////
 by: Eric Rosenbaum, Jay Silver, and Jim Lindblom
 MIT Media Lab & Sparkfun
 start date: 2/16/2012 
 current release: 7/5/2012
 
 Portado para o Arduino UNO em 09/05/2013
 por Daniel O. Basconcello Filho
 
 Verificar a forma de configurar na linha 46
 Verificar a saida pela porta serial nas linhas 341 e 363
 
 Editado por Evandro Luis Araujo de Sousa em 16/11/2021
 Para funcionar usando o Arduino Pro Mini
 */
/*
///////////////////////////////
/// COMO EDITAR ESSE CODIGO ///
///////////////////////////////
*/
/*
  VAMOS LA: PRIMEIRO VOCE PRECISA SABER QUE ESSE CODIGO FOI FEITO PARA SIMULAR O MAKEY MAKEY USANDO ARDUINO MICRO (COMPATIVEL) OU LEONARDO
  (NA VERDADE QUALQUER CHIP 32u4 VAI FUNCIONAR).
  - ALTERE O #NUM_INPUTS PARA A QUANTIDADE DE TECLAS QUE VOCE VAI USAR
  - ALTERE EM pinNumbers QUAIS PINOS DO ARDUINO MICRO VOCE VAI USAR
  - ALTERE NO ARQUIVO settings.h, keyCodes, COLOCANDO NA MESMA ORDEM DOS PINOS QUAIS TECLAS QUER EMULAR 
   (ATENCAO PARA TECLAS COMO SETAS USE OS CODIGOS NO FINAL DO ARQUIVO settings.h)
  - VOCE TAMBEM PODE ADICIONAR UM LED QUE SEMPRE VAI PISCAR QUANDO OUVER UM CLICK PARA ISSO BASTA EDITAR O NUMERO DO PINO EM led_pin
  - AGORA BASTA MANDAR ESSE CODIGO PARA O ARDUINO E CORRER PARA O ABRAÇO
*/

/*
 NAO MEXA NO BLOCO ABAIXO
*/

/////////////////////////
// DEBUG DEFINITIONS ////               
/////////////////////////
//#define DEBUG
//#define DEBUG2 
//#define DEBUG3 
//#define DEBUG_TIMING
//#define DEBUG_MOUSE
//#define DEBUG_TIMING2

////////////////////////
// DEFINED CONSTANTS////
////////////////////////

#define BUFFER_LENGTH    3     // 3 bytes gives us 24 samples
#define NUM_INPUTS       1    // 6 on the front + 12 on the back

/*
  FIQUE LIVRE PARA PREENCHER CONFORME AS INSTRUÇÕES NO COMEÇO DO CODIGO
  ATENCAO PARA NAO ALTERAR O NOME DAS VARIAVEIS
*/

//NUMERO DE ENTRADAS DO MAKEY MAKEY 
#define NUM_INPUTS 1

//PINOS USADOS
int pinNumbers[NUM_INPUTS] = {
  6
};

#define led_pin   13

/**********************************************************************
***********************************************************************
***********************************************************************
********* PARE AQUI SE VOCE TEM DUVIDAS SOBRE O FUNCIONAMENTO *********
********* DESSE CODIGO. VOCE NÃO DEVE ALTERAR NADA DAQUI EM   *********
********* DIANTE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! *********
***********************************************************************
***********************************************************************
***********************************************************************
*/

#define TARGET_LOOP_TIME 744  // (1/56 seconds) / 24 samples = 744 microseconds per sample 

/*
 * IMPLEMENTACAO FUTURA
// id numbers for mouse movement inputs (used in settings.h)
#define MOUSE_MOVE_UP       -1 
#define MOUSE_MOVE_DOWN     -2
#define MOUSE_MOVE_LEFT     -3
#define MOUSE_MOVE_RIGHT    -4
*/

#include "settings.h"

/////////////////////////
// STRUCT ///////////////
/////////////////////////
typedef struct {
  byte pinNumber;
  int keyCode;
  byte measurementBuffer[BUFFER_LENGTH]; 
  boolean oldestMeasurement;
  byte bufferSum;
  boolean pressed;
  boolean prevPressed;
  //boolean isMouseMotion; IMPLEMENTACAO FUTURA
  boolean isMouseButton;
  boolean isKey;
} 
MakeyMakeyInput;

MakeyMakeyInput inputs[NUM_INPUTS];

///////////////////////////////////
// VARIABLES //////////////////////
///////////////////////////////////
int bufferIndex = 0;
byte byteCounter = 0;
byte bitCounter = 0;
int pressThreshold;
int releaseThreshold;
boolean inputChanged;

/*
 * IMPLEMENTACAO FUTURA
int mouseMovementCounter = 0; // for sending mouse movement events at a slower interval
int mouseHoldCount[NUM_INPUTS]; // used to store mouse movement hold data
 */

//input status LED pin numbers
//const int inputLED_a = 9;
//const int inputLED_b = 10;
//const int inputLED_c = 11;
//const int outputK = 14;
//const int outputM = 16;
//byte ledCycleCounter = 0;

// timing
int loopTime = 0;
int prevTime = 0;
int loopCounter = 0;


///////////////////////////
// FUNCTIONS //////////////
///////////////////////////
void initializeArduino();
void initializeInputs();
void updateMeasurementBuffers();
void updateBufferSums();
void updateBufferIndex();
void updateInputStates();
//void sendMouseButtonEvents(); //OBSOLETO
//void sendMouseMovementEvents(); //IMPLEMENTACAO FUTURA
void addDelay();
void updateOutLEDs();

//////////////////////
// SETUP /////////////
//////////////////////
void setup() 
{
  initializeArduino();
  initializeInputs();
}

////////////////////
// MAIN LOOP ///////
////////////////////
void loop() 
{
  updateMeasurementBuffers();
  updateBufferSums();
  updateBufferIndex();
  updateInputStates();
  //sendMouseMovementEvents(); IMPLEMENTACAO FUTURA
  updateOutLEDs();
  addDelay();
}

//////////////////////////
// INITIALIZE ARDUINO
//////////////////////////
void initializeArduino() {

  Serial.begin(9600);  // Serial for debugging
  Keyboard.begin();
  Mouse.begin();
  
  /* Set up input pins 
   DEactivate the internal pull-ups, since we're using external resistors */
  for (int i=0; i<NUM_INPUTS; i++)
  {
    pinMode(pinNumbers[i], INPUT);
    digitalWrite(pinNumbers[i], LOW);
  }
  pinMode(led_pin, OUTPUT);

#ifdef DEBUG
  delay(4000); // allow us time to reprogram in case things are freaking out
#endif
}

///////////////////////////
// INITIALIZE INPUTS
///////////////////////////
void initializeInputs() {

  float thresholdPerc = SWITCH_THRESHOLD_OFFSET_PERC;
  float thresholdCenterBias = SWITCH_THRESHOLD_CENTER_BIAS/50.0;
  float pressThresholdAmount = (BUFFER_LENGTH * 8) * (thresholdPerc / 100.0);
  float thresholdCenter = ( (BUFFER_LENGTH * 8) / 2.0 ) * (thresholdCenterBias);
  pressThreshold = int(thresholdCenter + pressThresholdAmount);
  releaseThreshold = int(thresholdCenter - pressThresholdAmount);

#ifdef DEBUG
  Serial.println(pressThreshold);
  Serial.println(releaseThreshold);
#endif

  for (int i=0; i<NUM_INPUTS; i++) {
    inputs[i].pinNumber = pinNumbers[i];
    inputs[i].keyCode = keyCodes[i];

    for (int j=0; j<BUFFER_LENGTH; j++) {
      inputs[i].measurementBuffer[j] = 0;
    }
    inputs[i].oldestMeasurement = 0;
    inputs[i].bufferSum = 0;

    inputs[i].pressed = false;
    inputs[i].prevPressed = false;

    if (inputs[i].keyCode == MOUSE_LEFT || inputs[i].keyCode == MOUSE_RIGHT){
      inputs[i].isMouseButton = true;
      inputs[i].isKey = false; 
    }
    else {
      inputs[i].isKey = true;
      inputs[i].isMouseButton = false;
    }
    
    /*
     * IMPLEMENTACAO FUTURA
    //inputs[i].isMouseMotion = false; 
    //if (inputs[i].keyCode < 0) {
      
    #ifdef DEBUG_MOUSE
      Serial.println("GOT IT");  
    #endif

    //inputs[i].isMouseMotion = true;
    //} 
    //else if ((inputs[i].keyCode == MOUSE_LEFT) || (inputs[i].keyCode == MOUSE_RIGHT)) {
    //  inputs[i].isMouseButton = true;
    //} 
    //else {      
    //}

    */
    
#ifdef DEBUG
    Serial.println(i);
#endif

  }
}


//////////////////////////////
// UPDATE MEASUREMENT BUFFERS
//////////////////////////////
void updateMeasurementBuffers() {

  for (int i=0; i<NUM_INPUTS; i++) {

    // store the oldest measurement, which is the one at the current index,
    // before we update it to the new one 
    // we use oldest measurement in updateBufferSums
    byte currentByte = inputs[i].measurementBuffer[byteCounter];
    inputs[i].oldestMeasurement = (currentByte >> bitCounter) & 0x01; 

    // make the new measurement
    boolean newMeasurement = digitalRead(inputs[i].pinNumber);

    // invert so that true means the switch is closed
    newMeasurement = !newMeasurement; 

    // store it    
    if (newMeasurement) {
      currentByte |= (1<<bitCounter);
    } 
    else {
      currentByte &= ~(1<<bitCounter);
    }
    inputs[i].measurementBuffer[byteCounter] = currentByte;
  }
}

///////////////////////////
// UPDATE BUFFER SUMS
///////////////////////////
void updateBufferSums() {

  // the bufferSum is a running tally of the entire measurementBuffer
  // add the new measurement and subtract the old one

  for (int i=0; i<NUM_INPUTS; i++) {
    byte currentByte = inputs[i].measurementBuffer[byteCounter];
    boolean currentMeasurement = (currentByte >> bitCounter) & 0x01; 
    if (currentMeasurement) {
      inputs[i].bufferSum++;
    }
    if (inputs[i].oldestMeasurement) {
      inputs[i].bufferSum--;
    }
  }  
}

///////////////////////////
// UPDATE BUFFER INDEX
///////////////////////////
void updateBufferIndex() {
  bitCounter++;
  if (bitCounter == 8) {
    bitCounter = 0;
    byteCounter++;
    if (byteCounter == BUFFER_LENGTH) {
      byteCounter = 0;
    }
  }
}

///////////////////////////
// UPDATE INPUT STATES
///////////////////////////
void updateInputStates() {
  inputChanged = false;
  for (int i=0; i<NUM_INPUTS; i++) {
    inputs[i].prevPressed = inputs[i].pressed; // store previous pressed state (only used for mouse buttons)
    if (inputs[i].pressed) {
      if (inputs[i].bufferSum < releaseThreshold) {  
        inputChanged = true;
        inputs[i].pressed = false;
        
        if (inputs[i].isKey) {
          
          //Tecla solta - envio pela porta serial
          //o numero da tecla no vetor de teclas seguido de
          //um numero 0 que indica que a tecla foi solta
          Keyboard.release(inputs[i].keyCode);
        }
        if (inputs[i].isMouseButton){
          Mouse.release(inputs[i].keyCode);
        }
        /*
         * IMPLEMENTACAO FUTURA
         */
       // if (inputs[i].isMouseMotion) {  
       //   mouseHoldCount[i] = 0;  // input becomes released, reset mouse hold
       // }
      }
      //else if (inputs[i].isMouseMotion) {  
       // mouseHoldCount[i]++; // input remains pressed, increment mouse hold
      //}
    } 
    else if (!inputs[i].pressed) {
      if (inputs[i].bufferSum > pressThreshold) {  // input becomes pressed
      
        inputChanged = true;
        inputs[i].pressed = true; 

        if (inputs[i].isKey) {
          //Tecla pressionada - envio pela porta serial
          //o numero da tecla no vetor de teclas seguido de
          //um numero 1 que indica que a tecla foi pressionada
          Keyboard.press(inputs[i].keyCode);
        }
        if (inputs[i].isMouseButton){
          Mouse.press(inputs[i].keyCode);
        }
      }
    }
  }
#ifdef DEBUG3
  if (inputChanged) {
    Serial.println("change");
  }
#endif
}

/* OBSOLETO
///////////////////////////
 // SEND KEY EVENTS (obsolete, used in versions with pro micro bootloader)
 ///////////////////////////
 void sendKeyEvents() {
 if (inputChanged) {
 KeyReport report = {
 0                                                        };
 for (int i=0; i<6; i++) {
 report.keys[i] = 0;
 } 
 int count = 0;
 for (int i=0; i<NUM_INPUTS; i++) {
 if (inputs[i].pressed && (count < 6)) {
 report.keys[count] = inputs[i].keyCode;
 
 #ifdef DEBUG3
 Serial.println(report.keys[count]);
 #endif
 
 count++;        
 }
 }
 if (count > 0) {
 report.modifiers = 0x00;
 report.reserved = 1;
 Keyboard.sendReport(&report);
 } 
 else {
 report.modifiers = 0x00;
 report.reserved = 0;
 Keyboard.sendReport(&report);
 }      
 } 
 else {
 // might need a delay here to compensate for the time it takes to send keyreport
 }
 }
 */
/* OBSOLETO 
/////////////////////////////
// SEND MOUSE BUTTON EVENTS 
/////////////////////////////


void sendMouseButtonEvents() {
  if (inputChanged) {
    for (int i=0; i<NUM_INPUTS; i++) {
      if (inputs[i].isMouseButton) {
        if (inputs[i].pressed) {
          if (inputs[i].keyCode == MOUSE_LEFT) {
            Mouse.press(MOUSE_LEFT);
          } 
          if (inputs[i].keyCode == MOUSE_RIGHT) {
            Mouse.press(MOUSE_RIGHT);
          } 
        } 
        else if (inputs[i].prevPressed) {
          if (inputs[i].keyCode == MOUSE_LEFT) {
            Mouse.release(MOUSE_LEFT);
          } 
          if (inputs[i].keyCode == MOUSE_RIGHT) {
            Mouse.release(MOUSE_RIGHT);
          }           
        }
      }
    }
  }
}
*/
/*
 * IMPLEMENTACAO FUTURA
//////////////////////////////
// SEND MOUSE MOVEMENT EVENTS
//////////////////////////////
void sendMouseMovementEvents() {
  byte right = 0;
  byte left = 0;
  byte down = 0;
  byte up = 0;
  byte horizmotion = 0;
  byte vertmotion = 0;

  mouseMovementCounter++;
  mouseMovementCounter %= MOUSE_MOTION_UPDATE_INTERVAL;
  if (mouseMovementCounter == 0) {
    for (int i=0; i<NUM_INPUTS; i++) {
#ifdef DEBUG_MOUSE
      //  Serial.println(inputs[i].isMouseMotion);  
#endif

      if (inputs[i].isMouseMotion) {
        if (inputs[i].pressed) {
          if (inputs[i].keyCode == MOUSE_MOVE_UP) {
            // JL Changes (x4): now update to 1 + a hold factor, constrained between 1 and mouse max movement speed
            up=constrain(1+mouseHoldCount[i]/MOUSE_RAMP_SCALE, 1, MOUSE_MAX_PIXELS);
          }  
          if (inputs[i].keyCode == MOUSE_MOVE_DOWN) {
            down=constrain(1+mouseHoldCount[i]/MOUSE_RAMP_SCALE, 1, MOUSE_MAX_PIXELS);
          }  
          if (inputs[i].keyCode == MOUSE_MOVE_LEFT) {
            left=constrain(1+mouseHoldCount[i]/MOUSE_RAMP_SCALE, 1, MOUSE_MAX_PIXELS);
          }  
          if (inputs[i].keyCode == MOUSE_MOVE_RIGHT) {
            right=constrain(1+mouseHoldCount[i]/MOUSE_RAMP_SCALE, 1, MOUSE_MAX_PIXELS);
          }  
        }
      }
    }

    // diagonal scrolling and left/right cancellation
    if(left > 0)
    {
      if(right > 0)
      {
        horizmotion = 0; // cancel horizontal motion because left and right are both pushed
      }
      else
      {
        horizmotion = -left; // left yes, right no
      }
    }
    else
    {
      if(right > 0)
      {
        horizmotion = right; // right yes, left no
      }
    }

    if(down > 0)
    {
      if(up > 0)
      {
        vertmotion = 0; // cancel vertical motion because up and down are both pushed
      }
      else
      {
        vertmotion = down; // down yes, up no
      }
    }
    else
    {
      if (up > 0)
      {
        vertmotion = -up; // up yes, down no
      }
    }
    // now move the mouse
    if( !((horizmotion == 0) && (vertmotion==0)) )
    {
      Mouse.move(horizmotion * PIXELS_PER_MOUSE_STEP, vertmotion * PIXELS_PER_MOUSE_STEP);
    }
  }
}

*/

///////////////////////////
// ADD DELAY
///////////////////////////
void addDelay() {

  loopTime = micros() - prevTime;
  if (loopTime < TARGET_LOOP_TIME) {
    int wait = TARGET_LOOP_TIME - loopTime;
    delayMicroseconds(wait);
  }

  prevTime = micros();

#ifdef DEBUG_TIMING
  if (loopCounter == 0) {
    int t = micros()-prevTime;
    Serial.println(t);
  }
  loopCounter++;
  loopCounter %= 999;
#endif

}

void updateOutLEDs() {
  boolean Pressed = false;

  for (int i=0; i<NUM_INPUTS; i++){
    if (inputs[i].pressed) Pressed=true;
  }

  if (Pressed) digitalWrite(led_pin, HIGH);
  else digitalWrite( led_pin, LOW);
  }
