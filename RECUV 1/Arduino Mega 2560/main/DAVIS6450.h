#ifndef DAVIS6450_H
#define DAVIS6450_H

#include <Arduino.h>
#include <stdint.h>

class DAVIS6450 {
  public:
    uint8_t pin;

    DAVIS6450(uint8_t);
    ~DAVIS6450();
    float getRadiacion();
};

#endif // DAVIS6450_H