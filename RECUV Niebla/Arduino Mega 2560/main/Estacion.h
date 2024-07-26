#include <Arduino.h>
#include <stdint.h>

#include "Comunicador.h"

class Estacion {
  public:
    Comunicador comunicador;

    long int cont_E;
    long int cont_M;

    Estacion(Comunicador);
    ~Estacion();
    bool recibiendo();
    void contarTiempo();

    long int gettEnvio();
    int geterrorenvio();
    void actTrampa();
    void enviarTodo();
    void reciboRX();
};