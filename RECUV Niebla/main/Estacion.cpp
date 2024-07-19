#include "Estacion.h"

Estacion::Estacion(Comunicador comunicador) : comunicador(comunicador) {
  cont_E = 0;
  cont_M = 0;
}

Estacion::~Estacion() {
}

bool Estacion::recibiendo() {
  return comunicador.banderaL;
}

void Estacion::contarTiempo() {
  cont_E++;
  cont_M++;
}

long int Estacion::gettEnvio() {
  return comunicador.tEnvio;
}

int Estacion::geterrorenvio() {
  return comunicador.errorenvio;
}

void Estacion::actTrampa() {
  comunicador.trampa.actTrampa();
}

void Estacion::enviarTodo() {
  comunicador.enviarTrampa();
}

void Estacion::reciboRX() {
  comunicador.reciboEstacion();
}