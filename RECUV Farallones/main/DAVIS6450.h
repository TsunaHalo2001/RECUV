#ifndef DAVIS6450_H
#define DAVIS6450_H

#include "config.h"

#include <Arduino.h>
#include <stdint.h>

class DAVIS6450 {
  protected:
    uint8_t pin;
    bool bandera_espera;

  public:
    DAVIS6450(uint8_t);
    ~DAVIS6450();

    uint8_t obtener_pin() const;
    bool obtener_bandera_espera() const;

    void definir_pin(const uint8_t);
    void definir_bandera_espera(const bool);

    float pedir_radiacion_solar();
};

#endif