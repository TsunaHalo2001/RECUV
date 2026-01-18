#include "Tiempo.h"

Tiempo::Tiempo(RTC_DS3231 rtc) : rtc(rtc) {
  annio = 0;
  mes = 0;
  dia = 0;
  hora = 0;
  minn = 0;
  seg = 0;
  //rtc.adjust(DateTime(2026, 1, 16, 14, 38, 0));
}

Tiempo::~Tiempo() {
}

void Tiempo::actTiempo() {
  DateTime now = rtc.now();
  annio = now.year();
  mes = now.month();
  dia = now.day();
  hora = now.hour();
  minn = now.minute();
  seg = now.second();
}