#include "HCSR04.h"

HCSR04::HCSR04(uint8_t trigger, uint8_t echo) : trigger(trigger), echo(echo) {
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}

HCSR04::~HCSR04() {
}

float HCSR04::getCm() {
  unsigned long tiempo = pulseIn(echo, HIGH);

  float distancia = tiempo * 0.000001 * 34000.0 / 2.0;

  delay(50);

  return distancia;
}