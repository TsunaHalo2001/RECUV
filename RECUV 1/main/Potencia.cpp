#include "Potencia.h"

Potencia::Potencia(uint8_t pinVoltaje, uint8_t pinCorriente) : pinVoltaje(pinVoltaje), pinCorriente(pinCorriente) {
  m = 0.7906388361796;
  b = 323.7824161922831;
  sensibilidad = 0.066;
}

Potencia::~Potencia() {
}

float Potencia::getConsumoV() {
  int consumoV = analogRead(pinVoltaje);
  float vol_bat = (consumoV * m) - b;

  return vol_bat;
}

float Potencia::getConsumoC() {
  float i_bat = 0.0;
  float consumoC = analogRead(pinCorriente) * (5.0 / 1023.0);
  i_bat = -((consumoC - 2.5) / sensibilidad);

  return i_bat;
}