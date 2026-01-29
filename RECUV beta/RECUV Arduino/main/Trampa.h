#ifndef TRAMPA_H
#define TRAMPA_H

#include "config.h"

#include <Arduino.h>

#include <HX711.h>

class Trampa{
  protected:
    static Trampa* instancia;

    int pin_lluvia_1;
    int pin_lluvia_2;
    int pin_dato_peso_1;
    int pin_dato_peso_2;
    int pin_reloj_peso_1;
    int pin_reloj_peso_2;

    volatile int contador_lluvia_1;
    volatile int contador_lluvia_2;

    unsigned long tiempo_lluvia_1;
    unsigned long tiempo_lluvia_2;

    HX711 peso_1;
    HX711 peso_2;

  public:
    Trampa(int, int, int, int, int, int);
    ~Trampa();

    //Data collection
    float pedir_precipitacion_1_s();
    float pedir_precipitacion_2_s();
    float pedir_peso_1();
    float pedir_peso_2();

    void habilitar_interrupcion_lluvia_1();
    void habilitar_interrupcion_lluvia_2();
    void deshabilitar_interrupcion_lluvia_1();
    void deshabilitar_interrupcion_lluvia_2();
    static void contador_lluvia_1_interrupcion();
    static void contador_lluvia_2_interrupcion();
};

#endif