#include <PinChangeInterrupt.h>
#include <avr/wdt.h>

#include "Estacion.h"

//Pluviometro
#define rainPulsePin1 2
#define rainPulsePin2 3

//Celdas
#define celda1DTPin 6
#define celda1SCKPin 4
#define offset1 21469
#define scale1 -409.057128

#define celda2DTPin 7
#define celda2SCKPin 5
#define offset2 194414
#define scale2 -413.962249

//Extincion


#define tMuestreo 5

//Creacion de objetos
//Pluviometro
SEN15901 p1(1, rainPulsePin1, 1);
SEN15901 p2(1, rainPulsePin2, 1);

//Celdas de carga
HX711 celda1;
HX711 celda2;

Trampa trampa(p1, p2, celda1, celda2);

Comunicador comunicador(trampa);

Estacion estacion(comunicador);

void serialEvent1();
void rainCounterInterrupt1();
void rainCounterInterrupt2();