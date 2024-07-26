#include "Estacion.h"

Estacion::Estacion(Comunicador comunicador) : comunicador(comunicador) {
  cont_E = 0;
  cont_M = 0;
}

Estacion::~Estacion() {
}

bool Estacion::recibiendo() {
  return comunicador.banderaL;
}

void Estacion::contarTiempo() {
  cont_E++;
  cont_M++;
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
    ConfigureIRSensor();
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


long int Estacion::gettEnvio() {
  return comunicador.tEnvio;
}

int Estacion::geterrorenvio() {
  return comunicador.errorenvio;
}

void Estacion::actTrampa() {
  comunicador.trampa.actTrampa();
}

void Estacion::enviarTodo() {
  comunicador.enviarTrampa();
}

void Estacion::reciboRX() {
  comunicador.reciboEstacion();
}