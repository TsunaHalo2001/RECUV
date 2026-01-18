#include "Reloj.h"

Reloj::Reloj() : rtc(DESFASE_RTC), bandera_utc(true), bandera_tiempo_correcto(false) {
}

Reloj::~Reloj() = default;

[[nodiscard]] ESP32Time Reloj::obtener_rtc() const { return this->rtc; }
[[nodiscard]] bool Reloj::obtener_bandera_utc() const { return this->bandera_utc; }
[[nodiscard]] bool Reloj::obtener_bandera_tiempo_correcto() const { return this->bandera_tiempo_correcto; }

void Reloj::definir_rtc(const ESP32Time& _rtc) { this->rtc = _rtc; }
void Reloj::definir_bandera_utc(const bool _bandera_utc) { this->bandera_utc = _bandera_utc; }
void Reloj::definir_bandera_tiempo_correcto(const bool _bandera_tiempo_correcto) { this->bandera_tiempo_correcto = _bandera_tiempo_correcto; }

String Reloj::obtener_tiempo() {
  return String(this->rtc.getYear())      + "-" +
         String(this->rtc.getMonth() + 1) + "-" +
         String(this->rtc.getDay())       + " " +
         String(this->rtc.getHour(true))  + ":" +
         String(this->rtc.getMinute())    + ":" +
         String(this->rtc.getSecond());
}

int Reloj::obtener_minuto() { return this->rtc.getMinute(); }

void Reloj::pedir_utc() {
  if (WiFi.status() != WL_CONNECTED) return;

  HTTPClient http;
  http.begin(UTC_API); // Uses WiFiClient internally
  http.addHeader(UTC_HEADER_NAME, UTC_HEADER_VALUE);
  LOG_HTTP("GET: " + String(UTC_API));
  int code = http.GET();
  LOG_HTTP("Codigo de estado: " + String(code));
  if (code == -1 || code == -4 || code == -5 || code == -7 || code == -11) {
    this->bandera_utc = true;
  }
  else if (code == 200) {
    this->bandera_utc = false;
    this->bandera_tiempo_correcto = true;
    WiFiClient *client = http.getStreamPtr();

    const size_t capacity = JSON_OBJECT_SIZE(15) + 300;
    DynamicJsonDocument doc(capacity);

    DeserializationError error = deserializeJson(doc, *client);

    if (error) {
      LOG_ERROR("JSON parseado fallido: " + String(error.c_str()));
      http.end();
      return;
    }

    const char* datetime = doc["datetime"];        // e.g., "2026-01-17T19:45:30.123456+00:00"
    long unixtime = doc["unixtime"];               // e.g., 1768677930
    int utcOffset = doc["utc_offset"];             // for Etc/UTC, this is "+00:00"

    LOG_JSON("Tiempo UTC parseado: " + String(datetime));
    LOG_JSON("Tiempo Unix: " + String(unixtime));

    rtc.setTime(unixtime - UTC_Bogota);
  }
  else {
    this->bandera_utc = false;
  }
  http.end();
}