#ifndef SEN15901_H
#define SEN15901_H

#include "config.h"

#include <Arduino.h>
#include <stdint.h>
#include "driver/adc.h"
#include <esp_adc_cal.h>

class SEN15901 {
  protected:
    static SEN15901* instancia;

    uint8_t pin_viento;
    uint8_t pin_lluvia;
    uint8_t pin_veleta;
    volatile int contador_viento;
    volatile int contador_lluvia;
    unsigned long tiempo_viento;
    unsigned long tiempo_lluvia;

  public:
    explicit SEN15901(uint8_t, uint8_t, uint8_t);//Inicialización
    ~SEN15901(); //LLamador de funciones de colección

    uint8_t obtener_pin_viento() const;
    uint8_t obtener_pin_lluvia() const;

    void definir_pin_viento(const uint8_t);
    void definir_pin_lluvia(const uint8_t);

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