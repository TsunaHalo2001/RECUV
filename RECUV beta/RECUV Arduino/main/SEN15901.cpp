#include "SEN15901.h"

SEN15901* SEN15901::instance = nullptr;

// Inicialización del equipo SEN15901
SEN15901::SEN15901(uint8_t _pin_viento, uint8_t _pin_lluvia, uint8_t _pin_veleta) : 
    pin_viento(_pin_viento), 
    pin_lluvia(_pin_lluvia), 
    pin_veleta(_pin_veleta),
    contador_viento(0),
    contador_lluvia(0),
    tiempo_viento(0),
    tiempo_lluvia(0) {
  pinMode(this->pin_viento, INPUT_PULLUP); //Inicialización del pin para Anemometro
  pinMode(this->pin_lluvia, INPUT_PULLUP); //Inicialización del pin para Pluviometro
  instance = this;
  attachInterrupt(digitalPinToInterrupt(this->pin_viento), contador_viento_interrupcion, FALLING);
  attachInterrupt(digitalPinToInterrupt(this->pin_lluvia), contador_lluvia_interrupcion, FALLING);
}

SEN15901::~SEN15901() = default;

//Precipitación
float SEN15901::pedir_precipitacion() {
  double precipitacion = this->contador_lluvia * SEN15901_MS_FACTOR_LLUVIA; // Conversión para precipitación
  return precipitacion;
}

//Velocidad del viento
float SEN15901::pedir_velocidad_viento_s() {
  float velocidad_viento = this->contador_viento * SEN15901_MS_FACTOR_VIENTO;  // Conversión para velocidad del viento
  return velocidad_viento;
}

float SEN15901::pedir_velocidad_viento_m() {
  float velocidad_viento = this->contador_viento * SEN15901_MS_FACTOR_VIENTO / 60;  // Conversión para velocidad del viento
  return velocidad_viento;
}

float SEN15901::pedir_direccion_viento() {
  int adc_value = analogRead(this->pin_veleta);

  float v_dir = adc_value * SEN15901_ADC_FACTOR;

  if (v_dir >= (V_0_0_BOT ) && v_dir < (V_0_0_TOP)) return 0;
  else if (v_dir >= (V_22_5_BOT ) && v_dir < (V_22_5_TOP)) return 22.5;
  else if (v_dir >= (V_45_0_BOT ) && v_dir < (V_45_0_TOP)) return 45;
  else if (v_dir >= (V_67_5_BOT ) && v_dir < (V_67_5_TOP)) return 67.5;
  else if (v_dir >= (V_90_0_BOT ) && v_dir < (V_90_0_TOP)) return 90;
  else if (v_dir >= (V_112_5_BOT ) && v_dir < (V_112_5_TOP)) return 112.5;
  else if (v_dir >= (V_135_0_BOT ) && v_dir < (V_135_0_TOP)) return 135;
  else if (v_dir >= (V_157_5_BOT ) && v_dir < (V_157_5_TOP)) return 157.5;
  else if (v_dir >= (V_180_0_BOT ) && v_dir < (V_180_0_TOP)) return 180;
  else if (v_dir >= (V_202_5_BOT ) && v_dir < (V_202_5_TOP)) return 202.5;
  else if (v_dir >= (V_225_0_BOT ) && v_dir < (V_225_0_TOP)) return 225;
  else if (v_dir >= (V_247_5_BOT ) && v_dir < (V_247_5_TOP)) return 247.5;
  else if (v_dir >= (V_270_0_BOT ) && v_dir < (V_270_0_TOP)) return 270;
  else if (v_dir >= (V_292_5_BOT ) && v_dir < (V_292_5_TOP)) return 292.5;
  else if (v_dir >= (V_315_0_BOT ) && v_dir < (V_315_0_TOP)) return 315;
  else if (v_dir >= (V_337_5_BOT ) && v_dir < (V_337_5_TOP)) return 337.5;
  else return 404;
}

void SEN15901::contador_lluvia_interrupcion() {
  Serial.println("Lluvia");
  if (!instance) return;
  if (millis() - instance->tiempo_lluvia > 150) {
    instance->contador_lluvia++;
    instance->tiempo_lluvia = millis();
  }
}

void SEN15901::contador_viento_interrupcion() {
  Serial.println("Viento");
  if (!instance) return;
  if (millis() - instance->tiempo_viento > 150) {
    instance->contador_viento++;
    instance->tiempo_viento = millis();
  }
}