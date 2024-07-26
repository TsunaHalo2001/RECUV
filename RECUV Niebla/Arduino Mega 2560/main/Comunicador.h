#include <Arduino.h>
#include <stdint.h>

#include "Trampa.h"

char *strtok(char *str1, const char *str2);

class Comunicador {
  public:
    String buffer_tx;

    Trampa trampa;

    long int tEnvio;

    bool banderaL;
    bool banderaRX;
    char indiceRX;
    int contadorseparador;
    char contadorFRAMERX;
    char RXString[100];
    int errorenvio;

    char *ptr = NULL;

    Comunicador(Trampa);
    ~Comunicador();
    //Envio
    void enviarTrampa();
    //Recepcion
    void serialEvent1();
    void reciboEstacion();
};