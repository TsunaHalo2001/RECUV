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
  
  float auxV = (sens_consumoV * 0.068) + 22.0;
  vdc_bat_comp += auxV;
  idc_bat_comp += sens_consumoC; //m                    //b
  cbat_comp += (sens_consumoV + 150) * 6;
  Serial.println("(sens_consumoV + 150) * 6 = " + String((sens_consumoV + 150) * 6));
  idc_siscomp += sens_consumoC;
  valcon_siscomp += auxV * sens_consumoC;
}