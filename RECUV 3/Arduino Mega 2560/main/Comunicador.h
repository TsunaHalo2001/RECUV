#include <Arduino.h>
#include <stdint.h>

#include "Tiempo.h"
#include "Ambiental.h"
#include "Trampa.h"

char *strtok(char *str1, const char *str2);

class Comunicador {
  public:
    String buffer_tx;

    Tiempo tiempo;
    Ambiental ambiental;
    Trampa trampa;

    long int tEnvio;

    int banderaL;
    int banderaL2;
    int banderaL3;
    char banderaESPRx;
    char banderaESPRx3;
    char banderaARDRX;
    char indiceESPRX;
    char indiceARDRX;
    int contadorseparador1;
    int contadorseparador2;
    char contadorFRAMEESPRX;
    char contadorFRAMEARDRX;
    char ESPString[100];
    int errorrecibo;

    char *ptr = NULL;

    Comunicador(Tiempo, Ambiental, Trampa);
    ~Comunicador();
    //Envio
    void enviarTiempo();
    void enviarAmbiental();
    void enviarTrampa();
    void enviarTodo();

    //Recepcion
    void serialEvent1();
    void reciboEsp();

    //Interfaz
    void mostrarTrama();
};