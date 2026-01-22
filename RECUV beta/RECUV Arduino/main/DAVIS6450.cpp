#include "DAVIS6450.h"

DAVIS6450::DAVIS6450(uint8_t _pin) : pin(_pin), bandera_espera(false) {
  pinMode(this->pin, INPUT);
}

DAVIS6450::~DAVIS6450() = default;

[[nodiscard]] uint8_t DAVIS6450::obtener_pin() const { return this->pin; }
[[nodiscard]] bool DAVIS6450::obtener_bandera_espera() const { return this->bandera_espera; }

void DAVIS6450::definir_pin(const uint8_t _pin) { this->pin = _pin; }
void DAVIS6450::definir_bandera_espera(const bool _bandera_espera) { this->bandera_espera = _bandera_espera; }

float DAVIS6450::pedir_radiacion_solar() {
  int radiacion_conver = analogRead(this->pin);
  float radiacion_valor = radiacion_conver * DAVIS6450_ADC_FACTOR;

  delay(100);

  return radiacion_valor;
}