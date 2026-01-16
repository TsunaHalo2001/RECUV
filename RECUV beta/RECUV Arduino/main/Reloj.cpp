#include "Reloj.h"

Reloj::Reloj() : rtc(DESFASE_RTC) {
  rtc.setTime(30, 24, 15, 17, 1, 2021);
}

Reloj::~Reloj() = default;

[[nodiscard]] ESP32Time Reloj::obtener_rtc() const { return this->rtc; }

void Reloj::definir_rtc(const ESP32Time& _rtc) { this->rtc = _rtc; }

String Reloj::obtener_tiempo() {
  return String(this->rtc.getYear())      + "-" +
         String(this->rtc.getMonth() + 1) + "-" +
         String(this->rtc.getDay())       + " " +
         String(this->rtc.getHour(true))  + ":" +
         String(this->rtc.getMinute())    + ":" +
         String(this->rtc.getSecond());
}