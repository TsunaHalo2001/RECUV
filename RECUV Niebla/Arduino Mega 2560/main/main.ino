#include "config.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  estacion.celdabegin1(celda1DTPin, celda1SCKPin, offset1, scale1);
  estacion.celdabegin2(celda2DTPin, celda2SCKPin, offset2, scale2);

  attachInterrupt(digitalPinToInterrupt(rainPulsePin1), rainCounterInterrupt1, FALLING);
  attachInterrupt(digitalPinToInterrupt(rainPulsePin2), rainCounterInterrupt2, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (estacion.recibiendo()) {}
  else {
    if(estacion.cont_M > tMuestreo) {
      estacion.actTrampa();
      estacion.cont_M = 0;
    }

    if(estacion.cont_E > estacion.gettEnvio() || estacion.geterrorenvio() == 1) {
      estacion.enviarTodo();
      estacion.cont_E = 0;
    }

    delay(100);

    estacion.contarTiempo();
    estacion.reciboRX();
  }
}