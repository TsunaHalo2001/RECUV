#include "FC28.h"

FC28::FC28(uint8_t pin) : pin(pin) {
}

FC28::~FC28() {
}

float FC28::getHum() {
  int humedad_conver = analogRead(pin);
  float humedad_valor = 100 - (humedad_conver * 0.09765625);

  return humedad_valor;
}