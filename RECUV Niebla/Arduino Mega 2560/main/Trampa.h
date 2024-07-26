#include <Arduino.h>
#include <stdint.h>

#include <SEN15901.h>
#include <HX711.h>

class Trampa {
  public:
    int cont_prom;

    //Pluviometro
    double preci_actual1, preci_actual2;
    double preci_min1, preci_min2;
    volatile long rainTime1, rainTime2;

    //Pesos
    float peso1;
    float peso2;

    //Extincion visual
    float visibilidad;

    //Pluviometro
    SEN15901 p1, p2;

    //Pesos
    HX711 celda1, celda2;

    //Extincion visual


    Trampa(SEN15901, SEN15901, HX711, HX711);
    ~Trampa();
    void actualizarPreci();
    void actualizarPeso();
    void actualizarVis();
    void actTrampa();
    void rainCounterInterrupt1();
    void rainCounterInterrupt2();
};