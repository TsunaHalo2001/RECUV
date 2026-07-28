#ifndef ESTACION_H
#define ESTACION_H

#include "config.h"

#include <Arduino.h>
#include <stdio.h>
#include <WiFi.h>
#include <map>
#include <vector>

#include "Trampa.h"

class Estacion {
  protected:
    Trampa&      sensor_trampa;

    std::map<String, float>               medidas;
    std::map<String, int>                 contador;
    std::map<String, String>              trama;
    std::vector<std::map<String, String>> internet;
    int                                   iterador_internet;
    bool                                  bandera_wifi;
    int                                   minuto_actual;

  public:
    explicit Estacion(
                      Trampa&);
    ~Estacion();

    std::map<String, float>&              obtener_medidas();
    std::map<String, int>                 obtener_contador()          const;
    std::map<String, String>              obtener_trama()             const;
    std::vector<std::map<String, String>> obtener_internet()          const;
    int                                   obtener_iterador_internet() const;
    bool                                  obtener_bandera_wifi()      const;
    int                                   obtener_minuto_actual()     const;

    void definir_medidas          (const std::map<String, float>&);
    void definir_contador         (const std::map<String, int>&);
    void definir_trama            (const std::map<String, String>&);
    void definir_internet         (const std::vector<std::map<String, String>>&);
    void definir_iterador_internet(const int);
    void definir_bandera_wifi     (const bool);
    void definir_minuto_actual    (const int);

    //Trampa
    void habilitar_interrupcion_trampa();
    void deshabilitar_interrupcion_trampa();

    //Estacion
    void pedir_trampa();

    void realizar_medidas_s();
    void realizar_medidas_10s();
    void realizar_medidas_m();
    void enviar_medidas();
    void enviar_muestra();

    void siguiente_ssid();
};

#endif