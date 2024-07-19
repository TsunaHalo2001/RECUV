#include <PinChangeInterrupt.h>
#include <avr/wdt.h>

#include "Estacion.h"

//Pluviometro
#define rainPulsePin1 2
#define rainPulsePin2 3
#define rainPulsePin3 18
#define rainPulsePin4 19

#define tMuestreo 5

//Creacion de objetos
//Pluviometro
SEN15901 p1(1, rainPulsePin1, 1);
SEN15901 p2(1, rainPulsePin2, 1);
SEN15901 p3(1, rainPulsePin3, 1);
SEN15901 p4(1, rainPulsePin4, 1);

Trampa trampa(p1, p2, p3 ,p4);

Comunicador comunicador(trampa);

Estacion estacion(comunicador);

void serialEvent1();
void rainCounterInterrupt1();
void rainCounterInterrupt2();
void rainCounterInterrupt3();
void rainCounterInterrupt4();