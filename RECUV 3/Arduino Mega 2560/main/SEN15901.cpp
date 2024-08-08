#include "SEN15901.h"

// Inicialización del equipo SEN15901
SEN15901::SEN15901(uint8_t pinViento, uint8_t pinLluvia, uint8_t pinVientoDir) : pinViento(pinViento), pinLluvia(pinLluvia), pinVientoDir(pinVientoDir){
  pinMode(pinViento, INPUT_PULLUP); //Inicialización del pin para Anemometro
  pinMode(pinLluvia, INPUT_PULLUP); //Inicialización del pin para Pluviometro
  windCont = 0;
  rainCont = 0;
  timeWindSpeed = 5;
}

SEN15901::~SEN15901() {
}

//Precipitación
float SEN15901::getPrecipitacion() {
  double preci_temp = rainCont * 0.2794; // Conversión para precipitación
  return preci_temp;
}

//Velocidad del viento
float SEN15901::getVelViento() {
  float windSpeed = windCont * 2.4 / timeWindSpeed;  // Conversión para velocidad del viento
  return windSpeed;
}

float SEN15901::getDirViento() {
  int adc_value = analogRead(pinVientoDir);
  Serial.println(adc_value);

  float v_dir = adc_value * 0.0048876;
  Serial.println(v_dir);

  if (v_dir >= (V_ANGLE_0_0 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 0;
  if (v_dir >= (V_ANGLE_22_5 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 22.5;
  if (v_dir >= (V_ANGLE_45_0 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 45;
  if (v_dir >= (V_ANGLE_67_5 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 67.5;
  if (v_dir >= (V_ANGLE_90_0 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 90;
  if (v_dir >= (V_ANGLE_112_5 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 112.5;
  if (v_dir >= (V_ANGLE_135_0 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 135;
  if (v_dir >= (V_ANGLE_157_5 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 157.5;
  if (v_dir >= (V_ANGLE_180_0 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 180;
  if (v_dir >= (V_ANGLE_202_5 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 202.5;
  if (v_dir >= (V_ANGLE_225_0 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 225;
  if (v_dir >= (V_ANGLE_247_5 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 247.5;
  if (v_dir >= (V_ANGLE_270_0 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 270;
  if (v_dir >= (V_ANGLE_292_5 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 292.5;
  if (v_dir >= (V_ANGLE_315_0 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 315;
  if (v_dir >= (V_ANGLE_337_5 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 337.5;
}