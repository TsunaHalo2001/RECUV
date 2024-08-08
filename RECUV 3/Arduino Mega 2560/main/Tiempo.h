#include <Arduino.h>
#include <stdint.h>

#include <DS1302.h>

class Tiempo {
  public:
    int annio;
    int mes;
    int dia;
    int hora;
    int minn;
    int seg;
    DS1302 rtc;

    Tiempo(DS1302);
    ~Tiempo();
    void actTiempo();
};