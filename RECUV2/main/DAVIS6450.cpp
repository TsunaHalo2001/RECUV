#include "DAVIS6450.h"

DAVIS6450::DAVIS6450(uint8_t pin) : pin(pin) {
}

DAVIS6450::~DAVIS6450() {
}

float DAVIS6450::getRadiacion() {
  int radiacion_conver = analogRead(pin);
  float radiacion_valor = radiacion_conver * 2.93255132;

  return radiacion_valor;
}