#include <OneWire.h>
#include <PinChangeInterrupt.h>
#include <Wire.h>
#include <avr/wdt.h>

#include "Estacion.h"
// Constantes
// Valor alerta de preciptiacion
#define valor_Alerta 0.5

// Pines

// RTC
#define pinRST 24
#define pinCLK 22
#define pinDAT 23

// Humedad del aire
#define dhtpin 7
#define dhttype DHT22

// Anemometro
#define windPulsePin 3

// Pluviometro
#define rainPulsePin 2

// Veleta, Dirección del viento
#define DirVelPin A15

// Radiacion solar
#define pin_sensor_radiacion A0

// Humedad del suelo -- FC28
#define pin_sensor_humedad_suelo A2

// Temperatura del suelo -- DS18B20
#define pin_sensor_temp_suelo 6

//Trampa
//Pluviometro
#define rainPulsePin1 18
#define rainPulsePin2 19

//Celdas Larga
#define celda1DTPin 8
#define celda1SCKPin 9
#define offset1 506369
#define scale1 -431.630065
 //Corta
#define celda2DTPin 10
#define celda2SCKPin 11
#define offset2 4294539100
#define scale2 -419.598388

// Inicializacion de variables
#define tMuestreo 50

// Creacion de objetos
// Humedad del aire 
DHT dht(dhtpin, dhttype);

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

//Trampa
//Pluviometro
SEN15901 p1(1, rainPulsePin1, 1);
SEN15901 p2(1, rainPulsePin2, 1);

//Celdas de carga
HX711 celda1;
HX711 celda2;

//IR
Adafruit_TSL2591 tsl;

Trampa trampa(p1, p2, celda1, celda2, tsl);

// Comunicador
Comunicador comunicador(tiempo, ambiental, trampa);

// Estacion
Estacion estacion(comunicador);

// Interrupciones
void serialEvent1();
void windCounterInterrupt();
void rainCounterInterrupt();
void rainCounterInterrupt1();
void rainCounterInterrupt2();