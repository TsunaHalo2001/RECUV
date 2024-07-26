#include "SEN15901.h"
#include "Arduino.h"

// Inicialización del equipo SEN15901
SEN15901::SEN15901(uint8_t pinViento, uint8_t pinLluvia) : pinViento(pinViento), pinLluvia(pinLluvia) {
  pinMode(pinViento, INPUT_PULLUP); //Inicialización del pin para Anemometro
  pinMode(pinLluvia, INPUT_PULLUP); //Inicialización del pin para Pluviometro
  windCont = 0;
  rainCont = 0;
  timeWindSpeed = 5;
}

SEN15901::~SEN15901() {
}

float SEN15901::getPrecipitacion() {
  double preci_temp = rainCont * 0.2794; // Conversión para precipitación
  return preci_temp;
}

float SEN15901::getVelViento() {
  float windSpeed = windCont * 2.4 / timeWindSpeed;  // Conversión para velocidad del viento
  return windSpeed;
}