#include <Arduino.h>
#include <stdint.h>

class HCSR04 {
  public:
    uint8_t trigger;
    uint8_t echo;

    HCSR04(uint8_t, uint8_t);
    ~HCSR04();
    float getCm();
};