#include "Comunicador.h"

Comunicador::Comunicador(Tiempo tiempo, Ambiental ambiental, Trampa trampa) : tiempo(tiempo), ambiental(ambiental), trampa(trampa) {
  Serial1.begin(9600);
  Serial2.begin(9600);

  buffer_tx = "";

  banderaL = 0;
  banderaL2 = 0;
  banderaL3 = 0;
  banderaESPRx = 0;
  banderaESPRx3 = 0;
  indiceESPRX = 0;
  indiceARDRX = 0;
  contadorseparador1 = 0;
  contadorseparador2 = 0;
  contadorFRAMEESPRX = 0;
  ESPString[100] = "";
  errorrecibo = 0;

  tEnvio = 600;
}

Comunicador::~Comunicador() {
}

void Comunicador::enviarTiempo() {
  buffer_tx = "";
  buffer_tx = "T/" + String(tiempo.annio, DEC) +
               "/" + String(tiempo.mes, DEC) +
               "/" + String(tiempo.dia, DEC) +
               "/" + String(tiempo.hora, DEC) +
               "/" + String(tiempo.minn, DEC) +
               "/" + String(tiempo.seg, DEC) +
               "/F";
  
  Serial1.println(buffer_tx);
}

void Comunicador::enviarAmbiental() {
  ambiental.radiacion_valor_prom = ambiental.radiacion_valor_prom / ambiental.cont_prom;
  ambiental.temp_suelo_prom = ambiental.temp_suelo_prom / ambiental.cont_prom;
  ambiental.humedad_valor_prom = ambiental.humedad_valor_prom / ambiental.cont_prom;
  ambiental.t_prom = ambiental.t_prom / ambiental.cont_prom;
  ambiental.h_prom = ambiental.h_prom / ambiental.cont_prom;
  ambiental.P_prom = ambiental.P_prom / ambiental.cont_prom;
  ambiental.wind_Speed_Prom = ambiental.wind_Speed_Temp / ambiental.cont_prom;
  ambiental.wind_Speed_Temp = ambiental.wind_Speed_Prom;

  buffer_tx = "";
  buffer_tx = "A/" + String(ambiental.radiacion_valor_prom, DEC) +
               "/" + String(ambiental.humedad_valor_prom, DEC) + 
               "/" + String(ambiental.t_prom, DEC) +
               "/" + String(ambiental.h_prom, DEC) +
               "/" + String(ambiental.temp_suelo_prom, DEC) +
               "/" + String(ambiental.wind_Speed_Prom, DEC) +
               "/" + String(ambiental.preci_actual, DEC) +
               "/" + String(ambiental.P_prom, DEC) +
               "/" + String(ambiental.dirviento, DEC) +
               "/" + String(ambiental.preci_actual1, DEC) +
               "/" + String(ambiental.preci_actual2, DEC) +
               "/" + String(ambiental.peso1, DEC) +
               "/" + String(ambiental.peso2, DEC) +
               "/" + String(ambiental.visibilidad, DEC) +
               "/F";

  Serial1.println(buffer_tx);
  Serial.println(buffer_tx);
}

void Comunicador::enviarTrampa() {
  trampa.preci_actual1 = trampa.preci_actual1 / trampa.cont_prom;
  trampa.preci_actual2 = trampa.preci_actual2 / trampa.cont_prom;
  trampa.peso1 = trampa.peso1 / trampa.cont_prom;
  trampa.peso2 = trampa.peso2 / trampa.cont_prom;
  trampa.visibilidad = trampa.visibilidad / trampa.cont_prom;
  
  buffer_tx = "";
  buffer_tx = "K/" + String(trampa.preci_actual1, DEC) +
               "/" + String(trampa.preci_actual2, DEC) +
               "/" + String(trampa.peso1, DEC) +
               "/" + String(trampa.peso2, DEC) +
               "/" + String(trampa.visibilidad, DEC) +
               "/F";

  Serial1.println(buffer_tx);
  Serial.println(buffer_tx);

  trampa.cont_prom = 1;
}

void Comunicador::enviarTodo() {
  enviarTiempo();
  enviarAmbiental();
  enviarTrampa();
  Serial1.println("E/enviar/F");
  ambiental.cont_prom = 1;
  errorrecibo = 0;
}

void Comunicador::serialEvent1() {
  if (Serial1.available()) {
    char inChar = (char)Serial1.read();
    if (inChar == 'V') banderaL2 = 1;
    if (inChar == 'S') banderaL3 = 1;
    if (banderaL3 == 1) {
      ESPString[indiceESPRX] = inChar;
      if (inChar == '#') {
        banderaESPRx3 = 1;
        indiceESPRX = 0;
        banderaL3 = 0;
      }
      else indiceESPRX++;
    }
    if (banderaL2 == 1) {
      ESPString[indiceESPRX] = inChar;
      if (inChar == '/') contadorseparador1++;
      if (inChar == '#') {
        if(contadorseparador1 == 12) {
          banderaESPRx = 1;
          indiceESPRX = 0;
          banderaL2 = 0;
          contadorseparador1 = 0;
        }
        else {
          contadorseparador1 = 0;
          banderaESPRx = 0;
          indiceESPRX = 0;
          banderaL2 = 0;
          Serial1.print("G/enviar/F");
        }
      }
      else {
        indiceESPRX++;
        banderaESPRx = 0;
      }
    }
  }
}

void Comunicador::reciboEsp() {
  char delimitadores[] = "/";

  if(banderaESPRx == 1) {
    contadorFRAMEESPRX = 0;
    
    ptr = strtok(ESPString, "#");
    ptr = strtok(ESPString, "/");
           
    while(ptr != NULL) {
      switch(contadorFRAMEESPRX) {
        case 4: tEnvio = atoi(ptr); break;
        case 5: tiempo.mes = atoi(ptr); break;
        case 6: tiempo.dia = atoi(ptr); break;
        case 7: tiempo.annio = atoi(ptr); break;
        case 8: tiempo.hora = atoi(ptr); break;
        case 9: tiempo.minn = atoi(ptr); break;
        case 10: tiempo.seg = atoi(ptr); break;
      }
      ptr = strtok(NULL, delimitadores);
      contadorFRAMEESPRX++;
    }

    tEnvio = tEnvio * 10;
    
    banderaESPRx = 0;
  }

  if(banderaESPRx3 == 1) {
    contadorFRAMEESPRX = 0;
    ptr = strtok(ESPString, "#");
    ptr = strtok(ESPString, "/");
           
    while(ptr != NULL) {
      switch(contadorFRAMEESPRX) {
        case 1: errorrecibo = atoi(ptr); break;
      }
      ptr = strtok(NULL,delimitadores);
      contadorFRAMEESPRX++;
    }
    errorrecibo = 1;
    banderaESPRx3 = 0;
  }
}

void Comunicador::mostrarTrama() {
  buffer_tx = "";
  buffer_tx = "A/" + String(ambiental.radiacion_valor_prom / ambiental.cont_prom, DEC) +
               "/" + String(ambiental.humedad_valor_prom / ambiental.cont_prom, DEC) + 
               "/" + String(ambiental.t_prom / ambiental.cont_prom, DEC) +
               "/" + String(ambiental.h_prom / ambiental.cont_prom, DEC) +
               "/" + String(ambiental.temp_suelo_prom / ambiental.cont_prom, DEC) +
               "/" + String(ambiental.wind_Speed_Prom / ambiental.cont_prom, DEC) +
               "/" + String(ambiental.preci_actual / ambiental.cont_prom, DEC) +
               "/" + String(ambiental.P_prom / ambiental.cont_prom, DEC) +
               "/" + String(ambiental.dirviento / ambiental.cont_prom, DEC) +
               "/" + String(ambiental.preci_actual1 / ambiental.cont_prom, DEC) +
               "/" + String(ambiental.preci_actual2 / ambiental.cont_prom, DEC) +
               "/" + String(ambiental.peso1 / ambiental.cont_prom, DEC) +
               "/" + String(ambiental.peso2 / ambiental.cont_prom, DEC) +
               "/" + String(ambiental.visibilidad / ambiental.cont_prom, DEC) +
               "/F";

  Serial.println(buffer_tx);

  buffer_tx = "";
  buffer_tx = "T/" + String(tiempo.annio, DEC) +
               "/" + String(tiempo.mes, DEC) +
               "/" + String(tiempo.dia, DEC) +
               "/" + String(tiempo.hora, DEC) +
               "/" + String(tiempo.minn, DEC) +
               "/" + String(tiempo.seg, DEC) +
               "/F";

  Serial.println(buffer_tx);

  buffer_tx = "";
  buffer_tx = "K/" + String(trampa.preci_actual1 / trampa.cont_prom, DEC) +
               "/" + String(trampa.preci_actual2 / trampa.cont_prom, DEC) +
               "/" + String(trampa.peso1 / trampa.cont_prom, DEC) +
               "/" + String(trampa.peso2 / trampa.cont_prom, DEC) +
               "/" + String(trampa.visibilidad / trampa.cont_prom, DEC) +
               "/F";

  Serial.println(buffer_tx);
}