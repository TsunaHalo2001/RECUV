#include <Arduino.h>
#include <stdint.h>

#include "Potencia.h"

class Energia {
  public:
    float vdc_bat_comp;
    float idc_bat_comp;
    float cbat_comp;
    float idc_siscomp;
    float valcon_siscomp;

    Potencia pot1;
    Potencia pot2;

    Energia(Potencia, Potencia);
    ~Energia();
    void actualizarEnergia();
};