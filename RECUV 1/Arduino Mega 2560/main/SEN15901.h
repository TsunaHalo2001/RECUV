#ifndef SEN15901_H
#define SEN15901_H
#include <Arduino.h>
#include <stdint.h>

class SEN15901 {
  public:
    uint8_t pinViento;
    uint8_t pinLluvia;
    volatile int windCont;
    volatile int rainCont;
    float timeWindSpeed;

    SEN15901(uint8_t, uint8_t);
    ~SEN15901();
    float getPrecipitacion();
    float getVelViento();
};
#endif // SEN15901_H