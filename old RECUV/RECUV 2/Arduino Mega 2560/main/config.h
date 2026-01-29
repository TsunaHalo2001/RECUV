#include <OneWire.h>
#include <PinChangeInterrupt.h>
#include <Wire.h>
#include <avr/wdt.h>

#include "Estacion.h"-
// Constantes
// Valor alerta de preciptiacion
#define valor_Alerta 0.5

// Pines

// RTC
#define pinRST 8
#define pinCLK 11
#define pinDAT 10

// Humedad del aire
#define dhtpin 9
#define dhttype DHT11

// Potencia
#define pin_ConsV1 A5
#define pin_ConsV2 A7
#define pin_ConsC1 A9
#define pin_ConsC2 A11

// Anemometro
#define windPulsePin 3

// Pluviometro
#define rainPulsePin 2

// Veleta, Dirección del viento
#define DirVelPin A15

// Radiacion solar
#define pin_sensor_radiacion A1

// Humedad del suelo -- FC28
#define pin_sensor_humedad_suelo A2

// Temperatura del suelo -- DS18B20
#define pin_sensor_temp_suelo 6

// Inicializacion de variables
#define tMuestreo 100

// Creacion de objetos
// Humedad del aire 
DHT dht(dhtpin, dhttype);

// Potencia
Potencia pot1(pin_ConsV1, pin_ConsC1);
Potencia pot2(pin_ConsV2, pin_ConsC2);
//
Energia energia(pot1, pot2);

// Anemometro, Pluviometro y dirección de la veleta del viento
SEN15901 sen15901(windPulsePin, rainPulsePin, DirVelPin);

// Radiacion solar
DAVIS6450 davis6450(pin_sensor_radiacion);

// Humedad del suelo
FC28 fc28(pin_sensor_humedad_suelo);

// Temperatura del suelo
OneWire oneWireObjeto(pin_sensor_temp_suelo);
DallasTemperature sensorDS18B20(&oneWireObjeto);

// Presion atmosferica
SFE_BMP180 bmp180;
//
Ambiental ambiental(dht, davis6450, fc28, sensorDS18B20, bmp180, sen15901);

// Reloj en tiempo real
DS1302 rtc(pinRST,pinDAT,pinCLK);
Tiempo tiempo(rtc);

// Comunicador
Comunicador comunicador(tiempo, ambiental, energia);

// Estacion
Estacion estacion(comunicador);

// Interrupciones
void serialEvent1();
void windCounterInterrupt();
void rainCounterInterrupt();