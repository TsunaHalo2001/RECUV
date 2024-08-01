#include "Comunicador.h"

Comunicador::Comunicador(Trampa trampa) : trampa(trampa) {
  Serial1.begin(9600);

  buffer_tx = "";

  banderaL = 0;
  banderaRX = 0;
  indiceRX = 0;
  RXString[100] = "";
  errorenvio = 0;

  tEnvio = 600;
}

Comunicador::~Comunicador() {
}

void Comunicador::enviarTrampa() {
  trampa.preci_actual1 = trampa.preci_actual1 / trampa.cont_prom;
  trampa.preci_actual2 = trampa.preci_actual2 / trampa.cont_prom;
  trampa.peso1 = trampa.peso1 / trampa.cont_prom;
  trampa.peso2 = trampa.peso2 / trampa.cont_prom;
  trampa.visibilidad = trampa.visibilidad / trampa.cont_prom;
  
  buffer_tx = "";
  buffer_tx = "A/" + String(trampa.preci_actual1, DEC) +
               "/" + String(trampa.preci_actual2, DEC) +
               "/" + String(trampa.peso1, DEC) +
               "/" + String(trampa.peso2, DEC) +
               "/" + String(trampa.visibilidad, DEC) +
               "/F";

  Serial1.println(buffer_tx);
  Serial.println(buffer_tx);

  trampa.cont_prom = 1;

  errorenvio = 1;
}

void Comunicador::serialEvent1() {
  if (Serial1.available()) {
    char inChar = (char)Serial1.read();
    if (inChar == 'K') banderaL = true;
    if (banderaL) {
      RXString[indiceRX] = inChar;
      if (inChar == '/') contadorseparador++;
      if (inChar == 'X') {
        if(contadorseparador == 2) {
          banderaRX = true;
          indiceRX = 0;
          banderaL = false;
        }
        else {
          contadorseparador = 0;
          banderaRX = false;
          indiceRX = 0;
          banderaL = false;
        }
      }
      else indiceRX++;
    }
  }
}

void Comunicador::reciboEstacion() {
  char delimitadores[] = "/";

  if (banderaRX) {
    contadorFRAMERX = 0;
    Serial.println(errorenvio);

    ptr = strtok(RXString, "X");
    ptr = strtok(RXString, "/");

    while(ptr != NULL) {
      switch(contadorFRAMERX) {
        case 1: errorenvio = atoi(ptr); break;
      }
      ptr = strtok(NULL, delimitadores);
      contadorFRAMERX++;
    }
    Serial.println(errorenvio);
    banderaRX = false;
  }
}

void Comunicador::mostrarTrama() {
  buffer_tx = "";
  buffer_tx = "A/" + String(trampa.preci_actual1 / trampa.cont_prom, DEC) +
               "/" + String(trampa.preci_actual2 / trampa.cont_prom, DEC) +
               "/" + String(trampa.peso1 / trampa.cont_prom, DEC) +
               "/" + String(trampa.peso2 / trampa.cont_prom, DEC) +
               "/" + String(trampa.visibilidad / trampa.cont_prom, DEC) +
               "/F";

  Serial.println(buffer_tx);
}