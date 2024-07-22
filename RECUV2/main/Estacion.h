#include <Arduino.h>
#include <stdint.h>

#include "Comunicador.h"

class Estacion {
  public:
    Comunicador comunicador;

    long int cont_A;
    long int cont_E;
    long int cont_M;

    Estacion(Comunicador);
    ~Estacion();
    bool recibiendo();
    void contarTiempo();

    void bmp180begin();
    void dhtbegin();
    void ds18b20begin();

    double getpreci_actual();
    double getpreci_min();
    void setpreci_min(double);
    long int gettEnvio();
    int geterrorrecibo();

    void actTiempo();
    void actualizarAmbiental();
    void actualizarEnergia();
    void enviarTodo();
    void reciboEsp();
    void reciboArd();
};