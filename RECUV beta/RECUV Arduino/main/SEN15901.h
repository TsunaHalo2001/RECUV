#ifndef SEN15901_H
#define SEN15901_H

#include "config.h"

#include <Arduino.h>
#include <stdint.h>

class SEN15901 {
  protected:
    static SEN15901* instance;

    uint8_t pin_viento;
    uint8_t pin_lluvia;
    uint8_t pin_veleta;
    int contador_viento;
    int contador_lluvia;
    unsigned long tiempo_viento;
    unsigned long tiempo_lluvia;

  public:
    explicit SEN15901(uint8_t, uint8_t, uint8_t);//Inicialización
    ~SEN15901(); //LLamador de funciones de colección

    //Data collection
    float pedir_precipitacion();
    float pedir_velocidad_viento_s();
    float pedir_velocidad_viento_m();
    float pedir_direccion_viento();

    static void contador_lluvia_interrupcion();
    static void contador_viento_interrupcion();
};

#endif