#ifndef RELOJ_H
#define RELOJ_H

#include "config.h"

//#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP32Time.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include "log.h";

class Reloj {
  protected:
    ESP32Time rtc;
    bool bandera_utc;
    bool bandera_tiempo_correcto;

  public:
    explicit Reloj();
    ~Reloj();

    ESP32Time obtener_rtc() const;
    bool obtener_bandera_utc() const;
    bool obtener_bandera_tiempo_correcto() const;

    void definir_rtc(const ESP32Time&);
    void definir_bandera_utc(const bool);
    void definir_bandera_tiempo_correcto(const bool);

    String obtener_tiempo();
    int obtener_minuto();
    void pedir_utc();
};

#endif