#include "Estacion.h"

Estacion::Estacion(Comunicador comunicador) : comunicador(comunicador) {
  cont_A = 0;
  cont_E = 0;
}

Estacion::~Estacion() {
}

bool Estacion::recibiendo() {
  if(comunicador.banderaL == 1 || comunicador.banderaL2 == 1 || comunicador.banderaL3 == 1) return true;
  else return false;
}

void Estacion::contarTiempo() {
  cont_E++;
  cont_M++;
}

void Estacion::bmp180begin() {
  comunicador.ambiental.bmp180.begin();
}

void Estacion::dhtbegin() {
  comunicador.ambiental.dht.begin();
}

void Estacion::ds18b20begin() {
  comunicador.ambiental.ds18b20.begin();
}

bool Estacion::rtcbegin() {
  return comunicador.tiempo.rtc.begin();
}

bool Estacion::rtclostPower() {
  return comunicador.tiempo.rtc.lostPower();
}

double Estacion::getpreci_actual() {
  return comunicador.ambiental.preci_actual;
}

double Estacion::getpreci_min() {
  return comunicador.ambiental.preci_min;
}

void Estacion::setpreci_min(double a) {
  comunicador.ambiental.preci_min = a;
}

long int Estacion::gettEnvio() {
  return comunicador.tEnvio;
}

int Estacion::geterrorrecibo() {
  return comunicador.errorrecibo;
}

void Estacion::actTiempo() {
  comunicador.tiempo.actTiempo();
}

void Estacion::actualizarAmbiental() {
  comunicador.ambiental.actualizarAmbiental();
}

void Estacion::actualizarEnergia () {
  comunicador.energia.actualizarEnergia();
}

void Estacion::enviarTodo() {
  comunicador.enviarTodo();
}

void Estacion::reciboEsp() {
  comunicador.reciboEsp();
}