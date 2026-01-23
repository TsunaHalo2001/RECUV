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
#include "DAVIS6450.h"
#include <DHT_U.h>
#include "DS18B20.h"
#include <Wire.h>
#include <BMP280_DEV.h>
#include "FC28.h"

class Estacion {
  protected:
    Reloj        sensor_reloj;
    SEN15901&    sensor_sen15901;
    DAVIS6450&   sensor_davis6450;
    DHT_Unified& sensor_dht;
    DS18B20&     sensor_ds18b20;
    BMP280_DEV&  sensor_bmp280;
    FC28&        sensor_fc28;

    std::map<String, float>               medidas;
    std::map<String, int>                 contador;
    std::map<String, String>              trama;
    std::vector<std::map<String, String>> internet;
    int                                   iterador_internet;
    bool                                  bandera_wifi;
    int                                   minuto_actual;

  public:
    explicit Estacion(SEN15901&, 
                      DAVIS6450&, 
                      DHT_Unified&,
                      DS18B20&,
                      BMP280_DEV&,
                      FC28&);
    ~Estacion();

    Reloj&                                obtener_sensor_reloj();
    SEN15901&                             obtener_sensor_sen15901();
    DAVIS6450&                            obtener_sensor_davis6450();
    DHT_Unified&                          obtener_sensor_dht();
    DS18B20&                              obtener_sensor_ds18b20();
    BMP280_DEV&                           obtener_sensor_bmp280();
    FC28&                                 obtener_sensor_fc28();
    std::map<String, float>               obtener_medidas()           const;
    std::map<String, int>                 obtener_contador()          const;
    std::map<String, String>              obtener_trama()             const;
    std::vector<std::map<String, String>> obtener_internet()          const;
    int                                   obtener_iterador_internet() const;
    bool                                  obtener_bandera_wifi()      const;
    int                                   obtener_minuto_actual()     const;

    void definir_sensor_reloj     (const Reloj&);
    void definir_sensor_sen15901  (const SEN15901&);
    void definir_sensor_davis6450 (const DAVIS6450&);
    void definir_sensor_dht       (const DHT_Unified&);
    void definir_sensor_ds18b20   (const DS18B20&);
    void definir_sensor_fc28      (const FC28&);
    void definir_medidas          (const std::map<String, float>&);
    void definir_contador         (const std::map<String, int>&);
    void definir_trama            (const std::map<String, String>&);
    void definir_internet         (const std::vector<std::map<String, String>>&);
    void definir_iterador_internet(const int);
    void definir_bandera_wifi     (const bool);
    void definir_minuto_actual    (const int);

    //Reloj
    void pedir_utc();
    bool obtener_bandera_utc() const;
    void definir_bandera_utc(const bool);
    bool obtener_bandera_tiempo_correcto() const;
    void definir_bandera_tiempo_correcto(const bool);

    //SEN15901
    void habilitar_interrupcion_viento();
    void habilitar_interrupcion_lluvia();
    void deshabilitar_interrupcion_viento();
    void deshabilitar_interrupcion_lluvia();

    //Estacion
    void pedir_tiempo();
    void pedir_temperatura_ambiente();
    void pedir_precipitacion();
    void pedir_presion();
    void pedir_humedad_ambiente();
    void pedir_radiacion_solar();
    void pedir_direccion_viento();
    void pedir_velocidad_viento_s();
    void pedir_velocidad_viento_m();
    void pedir_temperatura_suelo();
    void pedir_humedad_suelo();

    void realizar_medidas_ms();
    void realizar_medidas_s();
    void realizar_medidas_10s();
    void realizar_medidas_m();
    void enviar_medidas();
    void enviar_muestra();

    void inicializar_wifi();
    void siguiente_ssid();
};

#endif