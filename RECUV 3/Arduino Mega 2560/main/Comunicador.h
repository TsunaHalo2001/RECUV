#include <Arduino.h>
#include <stdint.h>

#include "Tiempo.h"
#include "Ambiental.h"
#include "Energia.h"

char *strtok(char *str1, const char *str2);

class Comunicador {
  public:
    String buffer_tx;

    Tiempo tiempo;
    Ambiental ambiental;
    Energia energia;

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
    char ARDString[100];
    int errorrecibo;

    char *ptr = NULL;

    Comunicador(Tiempo, Ambiental, Energia);
    ~Comunicador();
    //Envio
    void enviarTiempo();
    void enviarAmbiental();
    void enviarEnergia();
    void enviarTodo();

    //Recepcion
    void serialEvent1();
    void serialEvent2();
    void reciboEsp();
    void reciboArd();

    //Interfaz
    void mostrarTrama();
};