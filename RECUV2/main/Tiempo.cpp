#include "Tiempo.h"

Tiempo::Tiempo(DS1302 rtc) : rtc(rtc) {
  annio = 0;
  mes = 0;
  dia = 0;
  hora = 0;
  minn = 0;
  seg = 0;
}

Tiempo::~Tiempo() {
}

void Tiempo::actTiempo() {
  Time now = rtc.time();
  annio = now.yr;
  Serial.print(String(annio));
  mes = now.mon;
  dia = now.date;
  hora = now.hr;
  minn = now.min;
  seg = now.sec;
}