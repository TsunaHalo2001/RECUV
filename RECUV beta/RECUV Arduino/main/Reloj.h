#ifndef RELOJ_H
#define RELOJ_H

#include "config.h"

//#include <Arduino.h>
#include <ESP32Time.h>

class Reloj {
  protected:
    ESP32Time rtc;

  public:
    explicit Reloj();
    ~Reloj();

    ESP32Time obtener_rtc() const;

    void definir_rtc(const ESP32Time&);

    String obtener_tiempo();
};

#endif