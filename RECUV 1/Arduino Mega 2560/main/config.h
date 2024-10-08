#include <OneWire.h>
#include <PinChangeInterrupt.h>
#include <Wire.h>
#include <avr/wdt.h>

#include "Estacion.h"

// Constantes
// Valor alerta de preciptiacion
#define valor_Alerta 0.5

// Pines
// Humedad del aire
#define dhtpin 7
#define dhttype DHT22

// Potencia
#define pin_ConsV1 A4
#define pin_ConsV2 A6
#define pin_ConsC1 A8
#define pin_ConsC2 A10

// Anemometro
#define windPulsePin 3

// Pluviometro
#define rainPulsePin 2

// Radiacion solar
#define pin_sensor_radiacion A0

// Humedad del suelo -- FC28
#define pin_sensor_humedad_suelo A2

// Temperatura del suelo -- DS18B20
#define pin_sensor_temp_suelo 5

// Inicializacion de variables
#define tMuestreo 50

// Creacion de objetos
// Humedad del aire 
DHT dht(dhtpin, dhttype);

// Potencia
Potencia pot1(pin_ConsV1, pin_ConsC1);
Potencia pot2(pin_ConsV2, pin_ConsC2);
//
Energia energia(pot1, pot2);

// Anemometro y Pluviometro
SEN15901 sen15901(windPulsePin, rainPulsePin);

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
RTC_DS3231 rtc;
//
Tiempo tiempo(rtc);

// Comunicador
Comunicador comunicador(tiempo, ambiental, energia);

// Estacion
Estacion estacion(comunicador);

// Interrupciones
void serialEvent1();
void windCounterInterrupt();
void rainCounterInterrupt();