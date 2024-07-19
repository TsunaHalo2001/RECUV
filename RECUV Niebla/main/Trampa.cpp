#include "Trampa.h"

Trampa::Trampa(SEN15901 p1, SEN15901 p2, SEN15901 p3, SEN15901 p4)
  : p1(p1), p2(p2), p3(p3), p4(p4) {
  cont_prom = 0;

  //Pluviometro
  preci_actual1 = 0;
  preci_min1 = 0;
  rainTime1 = 0;

  preci_actual2 = 0;
  preci_min2 = 0;
  rainTime2 = 0;

  preci_actual3 = 0;
  preci_min3 = 0;
  rainTime3 = 0;

  preci_actual4 = 0;
  preci_min4 = 0;
  rainTime4 = 0;

  //Pesos

  //Extincion visual
}

Trampa::~Trampa() {
}

void Trampa::actualizarPreci() {
  preci_actual1 += p1.getPrecipitacion();
  preci_actual2 += p2.getPrecipitacion();
  preci_actual3 += p3.getPrecipitacion();
  preci_actual4 += p4.getPrecipitacion();

  p1.rainCont = 0;
  p2.rainCont = 0;
  p3.rainCont = 0;
  p4.rainCont = 0;
}

void Trampa::actualizarPeso() {
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

void Trampa::rainCounterInterrupt3() {
  if (millis() - rainTime3 > 150) {
    p3.rainCont++;
    rainTime3 = millis();
  }
}

void Trampa::rainCounterInterrupt4() {
  if (millis() - rainTime4 > 150) {
    p4.rainCont++;
    rainTime4 = millis();
  }
}