#include "Estacion.h"

Estacion::Estacion(SEN15901 _sensor_sen15901) : sensor_sen15901(_sensor_sen15901), iterador_internet(0), bandera_wifi(false) {
  this->medidas["fecha"] = "None";
  this->medidas["hora"] = "None";
  this->medidas["fecha_servidor"] = "None";
  this->medidas["dir_viento"] = "None";
  this->medidas["vel_viento"] = "None";

  this->internet.push_back({{"SSID", "Tsuna's Infinix Note 40 Pro"}, {"PASSWORD", "joanisa21"}});
  this->internet.push_back({{"SSID", "Univalle"}, {"PASSWORD", "Univalle"}});
  this->internet.push_back({{"SSID", "univalle"}, {"PASSWORD", "Univalle"}});
  this->internet.push_back({{"SSID", "WirelessNet"}, {"PASSWORD", "eeeeeeee"}});

  inicializar_wifi();
}

Estacion::~Estacion() = default;

[[nodiscard]] Reloj& Estacion::obtener_sensor_reloj() { return this->sensor_reloj; }
[[nodiscard]] SEN15901& Estacion::obtener_sensor_sen15901() { return this->sensor_sen15901; }
[[nodiscard]] std::map<String, String> Estacion::obtener_medidas() const { return this->medidas; }
[[nodiscard]] std::vector<std::map<String, String>> Estacion::obtener_internet() const { return this->internet; }
[[nodiscard]] int Estacion::obtener_iterador_internet() const { return this->iterador_internet; };
[[nodiscard]] bool Estacion::obtener_bandera_wifi() const { return this->bandera_wifi; }
[[nodiscard]] int Estacion::obtener_minuto_actual() const { return this->minuto_actual; }

void Estacion::definir_sensor_reloj(const Reloj& _sensor_reloj) { this->sensor_reloj = _sensor_reloj; }
void Estacion::definir_sensor_sen15901(const SEN15901& _sensor_sen15901) { this->sensor_sen15901 = _sensor_sen15901; }
void Estacion::definir_medidas(const std::map<String, String>& _medidas) { this->medidas = _medidas; }
void Estacion::definir_internet(const std::vector<std::map<String, String>>& _internet) { this->internet = _internet; }
void Estacion::definir_iterador_internet(const int _iterador_internet) { this->iterador_internet = _iterador_internet; }
void Estacion::definir_bandera_wifi(const bool _bandera_wifi) { this->bandera_wifi = _bandera_wifi; }
void Estacion::definir_minuto_actual(const int _minuto_actual) { this->minuto_actual = _minuto_actual; }

//Reloj
void Estacion::pedir_utc() { this->sensor_reloj.pedir_utc(); }
bool Estacion::obtener_bandera_utc() const { return this->sensor_reloj.obtener_bandera_utc(); }
void Estacion::definir_bandera_utc(const bool _bandera_utc) { this->sensor_reloj.definir_bandera_utc(_bandera_utc); }
bool Estacion::obtener_bandera_tiempo_correcto() const { return this->sensor_reloj.obtener_bandera_tiempo_correcto(); }
void Estacion::definir_bandera_tiempo_correcto(const bool _bandera_tiempo_correcto) { this->sensor_reloj.definir_bandera_tiempo_correcto(_bandera_tiempo_correcto); }

void Estacion::pedir_tiempo() {
  this->minuto_actual = this->sensor_reloj.obtener_minuto();
  this->medidas["fecha"] = this->sensor_reloj.obtener_tiempo();
  this->medidas["hora"] = this->medidas["fecha"];
  this->medidas["fecha_servidor"] = this->medidas["fecha"];
}

void Estacion::pedir_direccion_viento() {
  this->medidas["dir_viento"] = String(this->sensor_sen15901.pedir_direccion_viento());
}

void Estacion::pedir_velocidad_viento_s() {
  this->medidas["vel_viento"] = String(this->sensor_sen15901.pedir_velocidad_viento_s());
}

void Estacion::pedir_velocidad_viento_m() {
  this->medidas["vel_viento"] = String(this->sensor_sen15901.pedir_velocidad_viento_m());
}

void Estacion::realizar_medidas_ms() {
  
}

void Estacion::realizar_medidas_s() {
  pedir_tiempo();
  pedir_direccion_viento();
}

void Estacion::realizar_medidas_m() { 
  pedir_velocidad_viento_m();
}

void Estacion::enviar_medidas() {
  LOG_ADVER("No hay metodo de envio");
}

void Estacion::enviar_muestra() {
  LOG_INFO("Tiempo: " + this->medidas["fecha"]);
  LOG_INFO("Direccion del viento: " + this->medidas["dir_viento"]);
  LOG_INFO("Velocidad del viento: " + this->medidas["vel_viento"]);
}

void Estacion::inicializar_wifi() {
  if (WiFi.status() != WL_CONNECTED) {
    this->bandera_wifi = false;

    WiFi.disconnect(true); // Deletes current connection
    WiFi.mode(WIFI_OFF);   // Optional: turn off radio
    delay(100);
    WiFi.mode(WIFI_STA);   // Re-enable station mode

    std::map<String, String> conexion = this->internet.at(this->iterador_internet);
    LOG_WIFI("Intentando: " + conexion.at("SSID"));
    WiFi.begin(conexion.at("SSID"), conexion.at("PASSWORD"));

    siguiente_ssid();
  }
}

void Estacion::siguiente_ssid() {
  this->iterador_internet++;
  if (this->iterador_internet == this->internet.size()) {
    this->iterador_internet = 0;
  }
}