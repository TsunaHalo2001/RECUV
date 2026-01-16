#include "Estacion.h"

Estacion::Estacion() : iterador_internet(0), bandera_wifi(false) {
  this->medidas["fecha"] = "None";

  this->internet.push_back({{"SSID", "Tsuna's Infinix Note 40 Pro"}, {"PASSWORD", "joanisa21"}});
  this->internet.push_back({{"SSID", "Univalle"}, {"PASSWORD", "Univalle"}});
  this->internet.push_back({{"SSID", "univalle"}, {"PASSWORD", "Univalle"}});
  this->internet.push_back({{"SSID", "WirelessNet"}, {"PASSWORD", "eeeeeeee"}});

  inicializar_wifi();
}

Estacion::~Estacion() = default;

[[nodiscard]] Reloj Estacion::obtener_sensor_reloj() const { return this->sensor_reloj; }
[[nodiscard]] std::map<String, String> Estacion::obtener_medidas() const { return this->medidas; }
[[nodiscard]] std::vector<std::map<String, String>> Estacion::obtener_internet() const { return this->internet; }
[[nodiscard]] int Estacion::obtener_iterador_internet() const { return this->iterador_internet; };
[[nodiscard]] bool Estacion::obtener_bandera_wifi() const { return this->bandera_wifi; }

void Estacion::definir_sensor_reloj(const Reloj& _sensor_reloj) { this->sensor_reloj = _sensor_reloj; }
void Estacion::definir_medidas(const std::map<String, String>& _medidas) { this->medidas = _medidas; }
void Estacion::definir_internet(const std::vector<std::map<String, String>>& _internet) { this->internet = _internet; }
void Estacion::definir_iterador_internet(const int _iterador_internet) { this->iterador_internet = _iterador_internet; }
void Estacion::definir_bandera_wifi(const bool _bandera_wifi) { this->bandera_wifi = _bandera_wifi; }

void Estacion::obtener_tiempo() {
  this->medidas["fecha"] = this->sensor_reloj.obtener_tiempo();
  this->medidas["hora"] = this->medidas["fecha"];
  this->medidas["fecha_servidor"] = this->medidas["fecha"];
}

void Estacion::realizar_medidas() {
  obtener_tiempo();
}

void Estacion::enviar_medidas() {
  Serial.println("enviando medidas: " + this->medidas["fecha"]);
}

void Estacion::inicializar_wifi() {
  if (WiFi.status() != WL_CONNECTED) {
    this->bandera_wifi = false;
    std::map<String, String> conexion = this->internet.at(this->iterador_internet);
    Serial.println("Intendando: " + conexion.at("SSID"));
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