#include "config.h"


void setup() {
  Serial.begin(9600);
  wdt_disable();
  // put your setup code here, to run once:
  //Se inicializa el metodo de presion atmosferica
  estacion.bmp180begin();

  //Se inicializa el metodo de humedad del aire
  estacion.dhtbegin();

  //Se inicializa el metodo de temperatura del suelo
  estacion.ds18b20begin();

  estacion.celdabegin1(celda1DTPin, celda1SCKPin, offset1, scale1);
  estacion.celdabegin2(celda2DTPin, celda2SCKPin, offset2, scale2);

  attachInterrupt(digitalPinToInterrupt(rainPulsePin1), rainCounterInterrupt1, FALLING);
  attachInterrupt(digitalPinToInterrupt(rainPulsePin2), rainCounterInterrupt2, FALLING);

  //Se inicializa la interrupcion del anemometro
  attachInterrupt(digitalPinToInterrupt(windPulsePin), windCounterInterrupt, FALLING);

  //Se inicializa la interrupcion del pluviometro
  attachInterrupt(digitalPinToInterrupt(rainPulsePin), rainCounterInterrupt, FALLING);

  estacion.actTiempo();

  wdt_enable(WDTO_8S); //WATCHDOG HABILITACIÓN
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (estacion.recibiendo()) {}
  else {
    //Valor alerta de precipitacion
    if(estacion.cont_A >= 12) {
       estacion.cont_A = 0;
       if((estacion.getpreci_actual() - estacion.getpreci_min()) > valor_Alerta) estacion.cont_E = estacion.gettEnvio();
       else estacion.setpreci_min(estacion.getpreci_actual());
    }

    if(estacion.cont_M > tMuestreo) {
      estacion.actTiempo();
      estacion.actualizarAmbiental();
      estacion.actTrampa();
      estacion.cont_A++;
      estacion.cont_M = 0;
    }

    if(estacion.cont_E > estacion.gettEnvio() || estacion.geterrorrecibo() == 1) {
      estacion.enviarTodo();
      estacion.cont_E = 0;
    }
  	
    if(estacion.cont_E % 100 == 0) estacion.comunicador.mostrarTrama();
    delay(100);

    estacion.contarTiempo();

    estacion.reciboEsp();

    estacion.actTiempo();
  }
  wdt_reset();
}