#include "Trampa.h"

Trampa::Trampa(SEN15901 p1, SEN15901 p2, HX711 celda1, HX711 celda2) : p1(p1), p2(p2), celda1(celda1), celda2(celda2) {
  cont_prom = 0;

  //Pluviometro
  preci_actual1 = 0;
  preci_min1 = 0;
  rainTime1 = 0;

  preci_actual2 = 0;
  preci_min2 = 0;
  rainTime2 = 0;

  //Pesos
  peso1 = 0;
  peso2 = 0;

  //Extincion visual
  visibilidad = 0;
}

Trampa::~Trampa() {
}

void Trampa::actualizarPreci() {
  preci_actual1 += p1.getPrecipitacion();
  preci_actual2 += p2.getPrecipitacion();

  p1.rainCont = 0;
  p2.rainCont = 0;
}

void Trampa::actualizarPeso() {
  peso1 += celda1.get_units(5);
  peso2 += celda2.get_units(5);
}

void Trampa::actualizarVis() {
}

void Trampa::actTrampa() {
  actualizarPreci();
  actualizarPeso();
  actualizarVis();
  cont_prom++;
}

void Trampa::rainCounterInterrupt1() {
  if (millis() - rainTime1 > 150) {
    p1.rainCont++;
    rainTime1 = millis();
  }
}

void Trampa::rainCounterInterrupt2() {
  if (millis() - rainTime2 > 150) {
    p2.rainCont++;
    rainTime2 = millis();
  }
}