#include "Estacion.h"

Estacion::Estacion(Comunicador comunicador) : comunicador(comunicador) {
  cont_A = 0;
  cont_E = 0;
  eenable = false;
}

Estacion::~Estacion() {
}

bool Estacion::recibiendo() {
  if(comunicador.banderaL == 1 || comunicador.banderaL2 == 1 || comunicador.banderaL3 == 1) return true;
  else return false;
}

void Estacion::contarTiempo() {
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

double Estacion::getpreci_actual() {
  return comunicador.ambiental.preci_actual;
}

double Estacion::getpreci_actual1() {
  return comunicador.ambiental.preci_actual1;
}

double Estacion::getpreci_actual2() {
  return comunicador.ambiental.preci_actual2;
}

double Estacion::getpreci_min() {
  return comunicador.ambiental.preci_min;
}

double Estacion::getpreci_min1() {
  return comunicador.ambiental.preci_min1;
}

double Estacion::getpreci_min2() {
  return comunicador.ambiental.preci_min2;
}

void Estacion::setpreci_min(double a) {
  comunicador.ambiental.preci_min = a;
}

void Estacion::setpreci_min1(double a) {
  comunicador.ambiental.preci_min1 = a;
}

void Estacion::setpreci_min2(double a) {
  comunicador.ambiental.preci_min2 = a;
}

long int Estacion::gettEnvio() {
  return comunicador.tEnvio;
}

int Estacion::geterrorrecibo() {
  return comunicador.errorrecibo;
}

int Estacion::getmin() {
  return comunicador.tiempo.minn;
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

void Estacion::reciboArd() {
  comunicador.reciboArd();
}