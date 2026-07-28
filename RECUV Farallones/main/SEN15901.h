#ifndef SEN15901_H
#define SEN15901_H

#include "config.h"

#include <Arduino.h>
#include "driver/adc.h"
#include <esp_adc_cal.h>

class SEN15901 {
  protected:
    static SEN15901* instancia;

    int pin_viento;
    int pin_lluvia;
    int pin_veleta;
    volatile int contador_viento;
    volatile int contador_lluvia;
    unsigned long tiempo_viento;
    unsigned long tiempo_lluvia;

  public:
    explicit SEN15901(int, int, int);//Inicialización
    ~SEN15901(); //LLamador de funciones de colección

    int obtener_pin_viento() const;
    int obtener_pin_lluvia() const;

    void definir_pin_viento(const int);
    void definir_pin_lluvia(const int);

    //Data collection
    float pedir_precipitacion_s();
    float pedir_velocidad_viento_s();
    float pedir_velocidad_viento_m();
    float pedir_direccion_viento();

    void habilitar_interrupcion_viento();
    void habilitar_interrupcion_lluvia();
    void deshabilitar_interrupcion_viento();
    void deshabilitar_interrupcion_lluvia();
    static void contador_lluvia_interrupcion();
    static void contador_viento_interrupcion();
};

#endif