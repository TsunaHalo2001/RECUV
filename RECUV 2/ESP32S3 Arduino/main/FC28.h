#ifndef FC28_H
#define FC28_H

#include "config.h"

#include <Arduino.h>

class FC28 {
  protected:
    int pin;

  public:
    FC28(int);
    ~FC28();

    int obtener_pin() const;

    void definir_pin(const int);

    float pedir_humedad();
};

#endif