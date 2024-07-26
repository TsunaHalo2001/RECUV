#include <Arduino.h>
#include <stdint.h>

#include "RTClib.h"

class Tiempo {
  public:
    int annio;
    int mes;
    int dia;
    int hora;
    int minn;
    int seg;
    RTC_DS3231 rtc;

    Tiempo(RTC_DS3231);
    ~Tiempo();
    void actTiempo();
};