#ifndef SensorLinhaPro_h
#define SensorLinhaPro_h
#include <SoftwareSerial.h>
/******************************************************************************
* Definitions
******************************************************************************/
class SensorLinhaPro{
private:
    SoftwareSerial *sf;
    int8_t valor;
public:
    static const uint8_t PROCESSADO = 1;
    static const uint8_t RAW = 2;
    
    static const uint8_t BAIXA = 1;
    static const uint8_t MEDIA = 2;
    static const uint8_t ALTA = 3;
	
	// public methods
    SensorLinhaPro();
    ~SensorLinhaPro();
    //size_t write(uint8_t byte);
    bool le();
    int8_t getValor();
    void begin(uint8_t receivePin, uint8_t transmitPin);
    void calibraFora();
    void calibraLinha();
    void testeSensor();
    void alteraModo(uint8_t tipo);
    void alteraTaxaAtualizacao(uint8_t);
    
    
};

#endif