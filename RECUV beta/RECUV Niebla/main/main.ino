#include "config.h"

#include "Estacion.h"

Trampa* trampa     = nullptr;
Estacion* estacion = nullptr;

unsigned long tiempo_base_envio;
unsigned long tiempo_base_medida_s;
unsigned long tiempo_base_medida_10s;
unsigned long tiempo_base_medida_m;
unsigned long tiempo_base_muestra;

int tiempo_envio_s = TIEMPO_ENVIO_S;
bool bandera_envio        = false;
bool bandera_tiempo_envio = true;

String buffer_tx = "";
bool banderaL = 0;
bool banderaRX = 0;
int indiceRX = 0;
char RXString[100] = "";
bool errorenvio = 0;
char *ptr = NULL;
int contadorseparador = 0;
int contadorFRAMERX = 0;

void medir_s() {
  unsigned long tiempo_transcurrido_medida_s = millis() - tiempo_base_medida_s;

  if (tiempo_transcurrido_medida_s >= VALOR_S) {
    tiempo_base_medida_s = millis();
    estacion->realizar_medidas_s();
  }
}

void muestra() {
  unsigned long tiempo_transcurrido_muestra = millis() - tiempo_base_muestra;

  if (tiempo_transcurrido_muestra >= TIEMPO_MUESTRA * VALOR_S) {
    tiempo_base_muestra = millis();
    estacion->enviar_muestra();
  }
}

void enviar() {
  unsigned long tiempo_transcurrido_envio = millis() - tiempo_base_envio;

  if (bandera_envio || tiempo_transcurrido_envio >= tiempo_envio_s * VALOR_S) {
    bandera_envio = false;
    bandera_tiempo_envio = false;
    tiempo_base_envio = millis();
    estacion->enviar_medidas();
    errorenvio = 1;
    delay(100);
  }
}

void serialEvent1() {
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

void reciboEstacion() {
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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, RX_1, TX_1);
  delay(2000);

  unsigned long tiempo_base = millis();
  tiempo_base_envio      = tiempo_base;
  tiempo_base_medida_s   = tiempo_base;
  tiempo_base_medida_10s = tiempo_base;
  tiempo_base_medida_m   = tiempo_base;
  tiempo_base_muestra    = tiempo_base;

  trampa    = new Trampa(PIN_LLUVIA_1, PIN_LLUVIA_2, PIN_DATO_PESO_1, PIN_DATO_PESO_2, PIN_RELOJ_PESO_1, PIN_RELOJ_PESO_2);
  estacion  = new Estacion(
    *trampa
  );
}

void loop() {
  // put your main code here, to run repeatedly:
  if (estacion) {
    medir_s();

    muestra();

    enviar();

    delay(100);
  }
}
