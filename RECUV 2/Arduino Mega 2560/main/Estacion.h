#include <Arduino.h>
#include <stdint.h>

#include "Comunicador.h"

class Estacion {
  public:
    Comunicador comunicador;

    long int cont_A;
    long int cont_E;
    long int cont_M;
    bool eenable;

    Estacion(Comunicador);
    ~Estacion();
    bool recibiendo();
    void contarTiempo();

    void bmp180begin();
    void dhtbegin();
    void ds18b20begin();

    double getpreci_actual();
    double getpreci_actual1();
    double getpreci_actual2();
    double getpreci_min();
    double getpreci_min1();
    double getpreci_min2();
    void setpreci_min(double);
    void setpreci_min1(double);
    void setpreci_min2(double);
    long int gettEnvio();
    int geterrorrecibo();
    int getmin();

    void actTiempo();
    void actualizarAmbiental();
    void actualizarEnergia();
    void enviarTodo();
    void reciboEsp();
    void reciboArd();
};