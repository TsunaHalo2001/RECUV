#include <Arduino.h>
#include <stdint.h>

class FC28 {
  public:
    uint8_t pin;

    FC28(uint8_t);
    ~FC28();
    float getHum();
};