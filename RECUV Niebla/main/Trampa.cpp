#include "Trampa.h"

Trampa::Trampa(SEN15901 p1, SEN15901 p2, SEN15901 p3, SEN15901 p4) : p1(p1), p2(p2), p3(p3), p4(p4) {
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

Trampa::actualizarPreci() {
  preci_actual1 = p1.getPrecipitacion();
  preci_actual2 = p2.getPrecipitacion();
  preci_actual3 = p3.getPrecipitacion();
  preci_actual4 = p4.getPrecipitacion();

  p1.windCont = 0;
  p2.windCont = 0;
  p3.windCont = 0;
  p4.windCont = 0;
}