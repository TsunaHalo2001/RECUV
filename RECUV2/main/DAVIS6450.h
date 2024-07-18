#include <Arduino.h>
#include <stdint.h>

class DAVIS6450 {
  public:
    uint8_t pin;

    DAVIS6450(uint8_t);
    ~DAVIS6450();
    float getRadiacion();
};