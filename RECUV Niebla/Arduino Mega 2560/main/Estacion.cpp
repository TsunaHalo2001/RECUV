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

void Estacion::celdabegin1(uint8_t dt, uint8_t sck, long offset, float scale) {
  comunicador.trampa.celda1.begin(dt, sck);
  comunicador.trampa.celda1.set_offset(offset);
  comunicador.trampa.celda1.set_scale(scale);
}

void Estacion::celdabegin2(uint8_t dt, uint8_t sck, long offset, float scale) {
  comunicador.trampa.celda2.begin(dt, sck);
  comunicador.trampa.celda2.set_offset(offset);
  comunicador.trampa.celda2.set_scale(scale);
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