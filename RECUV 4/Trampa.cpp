#include "Trampa.h"

Trampa* Trampa::instancia = nullptr;

Trampa::Trampa(int _pin_lluvia_1,
               int _pin_lluvia_2,
               int _pin_dato_peso_1,
               int _pin_dato_peso_2,
               int _pin_reloj_peso_1,
               int _pin_reloj_peso_2) : pin_lluvia_1(_pin_lluvia_1),
                                  pin_lluvia_2(_pin_lluvia_2),
                                  pin_dato_peso_1(_pin_dato_peso_1),
                                  pin_dato_peso_2(_pin_dato_peso_2),
                                  pin_reloj_peso_1(_pin_reloj_peso_1),
                                  pin_reloj_peso_2(_pin_reloj_peso_2),
                                  contador_lluvia_1(0),
                                  contador_lluvia_2(0),
                                  tiempo_lluvia_1(0),
                                  tiempo_lluvia_2(0) {

  instancia = this;

  pinMode(this->pin_lluvia_1, INPUT_PULLUP);
  pinMode(this->pin_lluvia_2, INPUT_PULLUP);

  this->peso_1.begin(this->pin_dato_peso_1, this->pin_reloj_peso_1);
  this->peso_1.set_offset(PESO_1_OFFSET);
  this->peso_1.set_scale(PESO_1_SCALE);

  this->peso_2.begin(this->pin_dato_peso_2, this->pin_reloj_peso_2);
  this->peso_2.set_offset(PESO_2_OFFSET);
  this->peso_2.set_scale(PESO_2_SCALE);


  habilitar_interrupcion_lluvia_1();
  habilitar_interrupcion_lluvia_2();
}

Trampa::~Trampa() = default;

float Trampa::pedir_precipitacion_1_s() {
  double precipitacion = this->contador_lluvia_1 * SEN15901_MS_FACTOR_LLUVIA; // Conversión para precipitación
  this->contador_lluvia_1 = 0;
  return precipitacion;
}

float Trampa::pedir_precipitacion_2_s() {
  double precipitacion = this->contador_lluvia_2 * SEN15901_MS_FACTOR_LLUVIA; // Conversión para precipitación
  this->contador_lluvia_2 = 0;
  return precipitacion;
}

float Trampa::pedir_peso_1() {
  return this->peso_1.get_units(5);
}

float Trampa::pedir_peso_2() {
  return this->peso_2.get_units(5);
}

void Trampa::habilitar_interrupcion_lluvia_1() {
  attachInterrupt(digitalPinToInterrupt(this->pin_lluvia_1), contador_lluvia_1_interrupcion, FALLING);
}

void Trampa::habilitar_interrupcion_lluvia_2() {
  attachInterrupt(digitalPinToInterrupt(this->pin_lluvia_2), contador_lluvia_2_interrupcion, FALLING);
}

void Trampa::deshabilitar_interrupcion_lluvia_1() {
  detachInterrupt(digitalPinToInterrupt(this->pin_lluvia_1));
}

void Trampa::deshabilitar_interrupcion_lluvia_2() {
  detachInterrupt(digitalPinToInterrupt(this->pin_lluvia_2));
}

void Trampa::contador_lluvia_1_interrupcion() {
  if (!instancia) return;
  if (millis() - instancia->tiempo_lluvia_1 > 150) {
    instancia->contador_lluvia_1++;
    instancia->tiempo_lluvia_1 = millis();
  }
}

void Trampa::contador_lluvia_2_interrupcion() {
  if (!instancia) return;
  if (millis() - instancia->tiempo_lluvia_2 > 150) {
    instancia->contador_lluvia_2++;
    instancia->tiempo_lluvia_2 = millis();
  }
}