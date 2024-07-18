#include <Arduino.h>
#include <stdint.h>

#include <DHT.h>
#include <DallasTemperature.h>
#include <SFE_BMP180.h>
#include "DAVIS6450.h"
#include "FC28.h"
#include "SEN15901.h"

class Ambiental {
  public:
    int cont_prom;
    //Humedad del aire
    float h;
    float t;
    float h_prom;
    float t_prom;

    //Anemometro
    float wind_Speed;
    float wind_Speed_Temp;
    float wind_Speed_Prom;
    volatile long windTime;

    //Veleta, Dirección del viento
    float dirviento;

    //Pluviometro
    double preci_actual;
    double preci_min;
    volatile long rainTime;

    //Radiacion solar
    float radiacion_valor;
    float radiacion_valor_prom;

    //Humedad del suelo
    float humedad_valor;
    float humedad_valor_prom;

    //Temperatura del suelo
    float temp_suelo;
    float temp_suelo_prom;

    //Presion atmosferica
    double T;
    double P;
    float T_prom;
    float P_prom;

    //Humedad del aire
    DHT dht;

    //Anemometro y Pluviometro
    SEN15901 sen15901;

    //Radiacion solar
    DAVIS6450 davis6450;

    //Humedad del suelo
    FC28 fc28;

    //Temperatura del suelo
    DallasTemperature ds18b20;

    //Presion atmosferica
    SFE_BMP180 bmp180;

    Ambiental(DHT, DAVIS6450, FC28, DallasTemperature, SFE_BMP180, SEN15901);
    ~Ambiental();
    void actualizarHumAire();
    void actualizarVelViento();
    void actualizarDirViento();
    void actualizarPreci();
    void actualizarRad();
    void actualizarHumSuelo();
    void actualizarTempSuelo();
    void actualizarPres();
    void actualizarNiebla();
    void actualizarAmbiental();
    void windCounterInterrupt();
    void rainCounterInterrupt();
};