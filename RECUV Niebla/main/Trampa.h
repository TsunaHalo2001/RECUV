#include <Arduino.h>
#include <stdint.h>

#include <SEN15901.h>

class Trampa {
  public:
    int cont_prom;

    //Pluviometro
    double preci_actual1, preci_actual2, preci_actual3, preci_actual4;
    double preci_min1, preci_min2, preci_min3, preci_min4;
    volatile long rainTime1, rainTime2, rainTime3 ,rainTime4;

    //Pesos

    //Extincion visual

    //Pluviometro
    SEN15901 p1, p2, p3, p4;

    //Pesos

    //Extincion visual


    Trampa(SEN15901, SEN15901, SEN15901, SEN15901);
    ~Trampa();
    void actualizarPreci();
    void actualizarPeso();
    void actualizarVis();
    void rainCounterInterrupt();
};