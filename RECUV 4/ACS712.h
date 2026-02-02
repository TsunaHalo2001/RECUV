#ifndef ACS712_H
#define ACS712_H

#include "config.h"

#include <Arduino.h>

class ACS712 {
  protected:
    int pin;

  public:
    ACS712(int);
    ~ACS712();

    int obtener_pin() const;

    void definir_pin(const int);

    float pedir_corriente();
};

#endif