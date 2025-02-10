#include "Estacion.h"

Estacion::Estacion(Comunicador comunicador) : comunicador(comunicador) {
  cont_A = 0;
  cont_E = 0;
}

Estacion::~Estacion() {
}

bool Estacion::recibiendo() {
  if(comunicador.banderaL == 1 || comunicador.banderaL2 == 1 || comunicador.banderaL3 == 1) return true;
  else return false;
}

void Estacion::contarTiempo() {
  cont_E++;
  cont_M++;
}

void Estacion::bmp180begin() {
  comunicador.ambiental.bmp180.begin();
}

void Estacion::dhtbegin() {
  comunicador.ambiental.dht.begin();
}

void Estacion::ds18b20begin() {
  comunicador.ambiental.ds18b20.begin();
}

void Estacion::celdabegin1(uint8_t dt, uint8_t sck, long offset, float scale) {
  comunicador.trampa.celda1.begin(dt, sck);
  comunicador.trampa.celda1.set_offset(offset);
  comunicador.trampa.celda1.set_scale(scale);
}

void Estacion::celdabegin2(uint8_t dt, uint8_t sck, long offset, float scale) {
  comunicador.trampa.celda2.begin(dt, sck);
  comunicador.trampa.celda2.set_offset(offset);
  comunicador.trampa.celda2.set_scale(scale);
}

void Estacion::irbegin(){
  Serial.println(F("Starting Adafruit TSL2591 Test!"));
  
  if (comunicador.trampa.tsl.begin()) 
  {
    Serial.println(F("Found a TSL2591 sensor"));
  } 
  else 
  {
    Serial.println(F("No sensor found ... check your wiring?"));
  }

  comunicador.trampa.tsl.setGain(TSL2591_GAIN_MED);      // 25x gain
  comunicador.trampa.tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
  Serial.println(F("------------------------------------"));
  Serial.print  (F("Gain:         "));
  tsl2591Gain_t gain = comunicador.trampa.tsl.getGain();
  switch(gain)
  {
    case TSL2591_GAIN_LOW:
      Serial.println(F("1x (Low)"));
      break;
    case TSL2591_GAIN_MED:
      Serial.println(F("25x (Medium)"));
      break;
    case TSL2591_GAIN_HIGH:
      Serial.println(F("428x (High)"));
      break;
    case TSL2591_GAIN_MAX:
      Serial.println(F("9876x (Max)"));
      break;
  }
  Serial.print  (F("Timing:       "));
  Serial.print((comunicador.trampa.tsl.getTiming() + 1) * 100, DEC); 
  Serial.println(F(" ms"));
  Serial.println(F("------------------------------------"));
  Serial.println(F(""));
}

double Estacion::getpreci_actual() {
  return comunicador.ambiental.preci_actual;
}

double Estacion::getpreci_actual1() {
  return comunicador.ambiental.preci_actual1;
}

double Estacion::getpreci_actual2() {
  return comunicador.ambiental.preci_actual2;
}

double Estacion::getpreci_min() {
  return comunicador.ambiental.preci_min;
}

double Estacion::getpreci_min1() {
  return comunicador.ambiental.preci_min1;
}

double Estacion::getpreci_min2() {
  return comunicador.ambiental.preci_min2;
}

void Estacion::setpreci_min(double a) {
  comunicador.ambiental.preci_min = a;
}

void Estacion::setpreci_min1(double a) {
  comunicador.ambiental.preci_min1 = a;
}

void Estacion::setpreci_min2(double a) {
  comunicador.ambiental.preci_min2 = a;
}

long int Estacion::gettEnvio() {
  return comunicador.tEnvio;
}

int Estacion::geterrorrecibo() {
  return comunicador.errorrecibo;
}

void Estacion::actTiempo() {
  comunicador.tiempo.actTiempo();
}

void Estacion::actualizarAmbiental() {
  comunicador.ambiental.actualizarAmbiental();
}

void Estacion::actTrampa() {
  comunicador.trampa.actTrampa();
}

void Estacion::enviarTodo() {
  comunicador.enviarTodo();
}

void Estacion::reciboEsp() {
  comunicador.reciboEsp();
}