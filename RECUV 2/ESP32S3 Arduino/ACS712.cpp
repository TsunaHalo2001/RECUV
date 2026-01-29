#include "ACS712.h"

ACS712::ACS712(int _pin) : pin(_pin) {
}

ACS712::~ACS712() = default;

[[nodiscard]] int ACS712::obtener_pin() const { return this->pin; }

void ACS712::definir_pin(const int _pin) { this->pin = _pin; }

float ACS712::pedir_corriente() {
  int valor_adc = analogRead(this->pin);
  float voltaje = ACS712_ADC_FACTOR * valor_adc;
  float corriente = (voltaje - ACS712_VCC / 2) / ACS712_SENSIBILIDAD;
  return corriente;
}