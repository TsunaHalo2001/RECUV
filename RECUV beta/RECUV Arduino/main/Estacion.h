#ifndef ESTACION_H
#define ESTACION_H

#include "config.h"

#include <Arduino.h>
#include <stdio.h>
#include <WiFi.h>
#include <map>
#include <vector>

#include "Reloj.h"

class Estacion {
  protected:
    Reloj sensor_reloj;

    std::map<String, String> medidas;
    std::vector<std::map<String, String>> internet;
    int iterador_internet;
    bool bandera_wifi;

  public:
    explicit Estacion();
    ~Estacion();

    Reloj                                                     obtener_sensor_reloj()   const;
    std::map<String, String>              obtener_medidas()        const;
    std::vector<std::map<String, String>> obtener_internet()       const;
    int obtener_iterador_internet() const;
    bool obtener_bandera_wifi() const;

    void definir_sensor_reloj  (const Reloj&);
    void definir_medidas       (const std::map<String, String>&);
    void definir_internet      (const std::vector<std::map<String, String>>&);
    void definir_iterador_internet(const int);
    void definir_bandera_wifi(const bool);

    void obtener_tiempo();

    void realizar_medidas();
    void enviar_medidas();

    void inicializar_wifi();
    void siguiente_ssid();
};

#endif