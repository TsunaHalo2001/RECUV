#include "Energia.h"

Energia::Energia(Potencia pot1, Potencia pot2) : pot1(pot2), pot2(pot2) {
  vdc_bat_comp = 0.0;
  idc_bat_comp = 0.0;
  cbat_comp = 0.0;
  idc_siscomp = 0.0;
  valcon_siscomp = 0.0;
}

Energia::~Energia() {
}

void Energia::actualizarEnergia() {
  float sens_consumoV = (pot1.getConsumoV() + pot2.getConsumoV()) / 2;
  float sens_consumoC = (pot1.getConsumoC() + pot2.getConsumoC()) / 2;

  vdc_bat_comp = (sens_consumoV * 0.068) + 22.0;
  idc_bat_comp = sens_consumoC;
  cbat_comp = sens_consumoV;
  idc_siscomp = -1 * sens_consumoC;
  valcon_siscomp = vdc_bat_comp * idc_siscomp;
}