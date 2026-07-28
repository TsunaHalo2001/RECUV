#include "FC28.h"

FC28::FC28(int _pin) : pin(_pin) {
}

FC28::~FC28() = default;

[[nodiscard]] int FC28::obtener_pin() const { return this->pin; }

void FC28::definir_pin(const int _pin) { this->pin = _pin; }

float FC28::pedir_humedad() {
  int valor_adc = analogRead(this->pin);

  float valor_humedad = 100 + valor_adc * FC28_FACTOR;
  return valor_humedad;
}