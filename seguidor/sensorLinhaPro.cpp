#include "arduino.h"
#include "sensorLinhaPro.h"


SensorLinhaPro::SensorLinhaPro()
{
}


SensorLinhaPro::~SensorLinhaPro()
{
    sf->end();
}


void SensorLinhaPro::begin(uint8_t receivePin, uint8_t transmitPin)
{
    //sf = new EspSoftwareSerial::UART(receivePin,transmitPin);
    //sf->begin(38400);
    #ifdef AVR
        this->sf = new SoftwareSerial(receivePin, transmitPin);
        sf->begin(38400);
    #endif
    #ifdef ESP32
        this->sf = new EspSoftwareSerial::UART();
        sf->begin(38400, SWSERIAL_8N1, receivePin, transmitPin, false);
    #endif
}
bool SensorLinhaPro::le(){
    uint8_t temp;
    if(sf->available()){
        while(sf->available()){
            temp = sf->read();
        }  
    }else{
        return false;
    }
    this->valor = temp;
    return true;
}


int8_t SensorLinhaPro::getValor(){
    return this->valor;
}

void SensorLinhaPro::calibraFora(){
    sf->write("FFF",3);
    delay(2000);
}

void SensorLinhaPro::calibraLinha(){
    sf->write("WWW",3);
    delay(8000);
}
void SensorLinhaPro::testeSensor(){
    sf->write("TTT", 3);
}

void SensorLinhaPro::alteraModo(uint8_t tipo){
    switch(tipo){
        case 1:
            sf->write("111", 3);
        break;
        case 2:
            sf->write("222",3);
        break;
    }
}

void SensorLinhaPro::alteraTaxaAtualizacao(uint8_t taxaAtualizacao){
    switch(taxaAtualizacao){
        case 1:
            sf->write("fff",3);
        break;
        case 2:
            sf->write("ggg",3);
        break;
        case 3:
            sf->write("iii",3);
        break;
    }
}