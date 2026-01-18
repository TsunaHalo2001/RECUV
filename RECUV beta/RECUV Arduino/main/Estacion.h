#ifndef ESTACION_H
#define ESTACION_H

#include "config.h"

#include <Arduino.h>
#include <stdio.h>
#include <WiFi.h>
#include <map>
#include <vector>

#include "Reloj.h"
#include "SEN15901.h"

class Estacion {
  protected:
    Reloj sensor_reloj;
    SEN15901 sensor_sen15901;

    std::map<String, String> medidas;
    std::vector<std::map<String, String>> internet;
    int iterador_internet;
    bool bandera_wifi;
    int minuto_actual;

  public:
    explicit Estacion(SEN15901);
    ~Estacion();

    Reloj& obtener_sensor_reloj();
    SEN15901& obtener_sensor_sen15901();
    std::map<String, String>              obtener_medidas()        const;
    std::vector<std::map<String, String>> obtener_internet()       const;
    int obtener_iterador_internet() const;
    bool obtener_bandera_wifi() const;
    int obtener_minuto_actual() const;

    void definir_sensor_reloj  (const Reloj&);
    void definir_sensor_sen15901 (const SEN15901&);
    void definir_medidas       (const std::map<String, String>&);
    void definir_internet      (const std::vector<std::map<String, String>>&);
    void definir_iterador_internet(const int);
    void definir_bandera_wifi(const bool);
    void definir_minuto_actual(const int);

    //Reloj
    void pedir_utc();
    bool obtener_bandera_utc() const;
    void definir_bandera_utc(const bool);
    bool obtener_bandera_tiempo_correcto() const;
    void definir_bandera_tiempo_correcto(const bool);

    void pedir_tiempo();
    void pedir_direccion_viento();
    void pedir_velocidad_viento_s();
    void pedir_velocidad_viento_m();

    void realizar_medidas_ms();
    void realizar_medidas_s();
    void realizar_medidas_m();
    void enviar_medidas();
    void enviar_muestra();

    void inicializar_wifi();
    void siguiente_ssid();
};

#endif