#include "Estacion.h"

Estacion::Estacion(
                   Trampa& _sensor_trampa
    ) : sensor_trampa(_sensor_trampa),
        iterador_internet(0), 
        bandera_wifi(false) {

  this->medidas["peso_malla1"] = 0.0;
  this->medidas["peso_malla2"] = 0.0;
  this->medidas["rainh1"] = 0.0;
  this->medidas["rainh2"] = 0.0;

  this->contador["peso_malla1"] = 1;
  this->contador["peso_malla2"] = 1;
  this->contador["rainh1"] = 1;
  this->contador["rainh2"] = 1;

  this->trama["peso_malla1"] = "0.0";
  this->trama["peso_malla2"] = "0.0";
  this->trama["rainh1"] = "0.0";
  this->trama["rainh2"] = "0.0";

  this->internet.push_back({{"SSID", "Tsuna's Infinix Note 40 Pro"}, {"PASSWORD", "joanisa21"}});
  this->internet.push_back({{"SSID", "Univalle"}, {"PASSWORD", "Univalle"}});
  this->internet.push_back({{"SSID", "univalle"}, {"PASSWORD", "Univalle"}});
  this->internet.push_back({{"SSID", "WirelessNet"}, {"PASSWORD", "eeeeeeee"}});
  this->internet.push_back({{"SSID", "GISMODEL"}, {"PASSWORD", "GISMODEL2023"}});
  this->internet.push_back({{"SSID", "GISMODEL02"}, {"PASSWORD", "GISMODEL24"}});
  this->internet.push_back({{"SSID", "BACHUE"}, {"PASSWORD", "Samantha72"}});
}

Estacion::~Estacion() = default;

[[nodiscard]] std::map<String, float>& Estacion::obtener_medidas() { return this->medidas; }
[[nodiscard]] std::map<String, int> Estacion::obtener_contador() const { return this->contador; }
[[nodiscard]] std::map<String, String> Estacion::obtener_trama() const { return this->trama; }
[[nodiscard]] std::vector<std::map<String, String>> Estacion::obtener_internet() const { return this->internet; }
[[nodiscard]] int Estacion::obtener_iterador_internet() const { return this->iterador_internet; };
[[nodiscard]] bool Estacion::obtener_bandera_wifi() const { return this->bandera_wifi; }
[[nodiscard]] int Estacion::obtener_minuto_actual() const { return this->minuto_actual; }

void Estacion::definir_medidas(const std::map<String, float>& _medidas) { this->medidas = _medidas; }
void Estacion::definir_contador(const std::map<String, int>& _contador) { this->contador = _contador; }
void Estacion::definir_trama(const std::map<String, String>& _trama) { this->trama = _trama; }
void Estacion::definir_internet(const std::vector<std::map<String, String>>& _internet) { this->internet = _internet; }
void Estacion::definir_iterador_internet(const int _iterador_internet) { this->iterador_internet = _iterador_internet; }
void Estacion::definir_bandera_wifi(const bool _bandera_wifi) { this->bandera_wifi = _bandera_wifi; }
void Estacion::definir_minuto_actual(const int _minuto_actual) { this->minuto_actual = _minuto_actual; }

//Trampa
void Estacion::habilitar_interrupcion_trampa() {
  this->sensor_trampa.habilitar_interrupcion_lluvia_1();
  this->sensor_trampa.habilitar_interrupcion_lluvia_2();
}

void Estacion::deshabilitar_interrupcion_trampa() {
  this->sensor_trampa.deshabilitar_interrupcion_lluvia_1();
  this->sensor_trampa.deshabilitar_interrupcion_lluvia_2();
}

void Estacion::pedir_trampa() {
  this->medidas["rainh1"] += this->sensor_trampa.pedir_precipitacion_1_s();
  this->contador["rainh1"]++;
  this->medidas["rainh2"] += this->sensor_trampa.pedir_precipitacion_2_s();
  this->contador["rainh2"]++;
  this->medidas["peso_malla1"] += this->sensor_trampa.pedir_peso_1();
  this->contador["peso_malla1"]++;
  this->medidas["peso_malla2"] += this->sensor_trampa.pedir_peso_2();
  this->contador["peso_malla2"]++;
}

void Estacion::realizar_medidas_s() {
  pedir_trampa();
}

void Estacion::realizar_medidas_10s() {
}

void Estacion::realizar_medidas_m() {
}

void Estacion::enviar_medidas() {
  this->medidas["peso_malla1"] = this->medidas["peso_malla1"] / this->contador["peso_malla1"];
  this->medidas["peso_malla2"] = this->medidas["peso_malla2"] / this->contador["peso_malla2"];
  this->medidas["rainh1"] = this->medidas["rainh1"] / this->contador["rainh1"];
  this->medidas["rainh2"] = this->medidas["rainh2"] / this->contador["rainh2"];

  this->contador["peso_malla1"] = 1;
  this->contador["peso_malla2"] = 1;
  this->contador["rainh1"] = 1;
  this->contador["rainh2"] = 1;

  this->trama["peso_malla1"] = String(this->medidas["peso_malla1"], DEC);
  this->trama["peso_malla2"] = String(this->medidas["peso_malla2"], DEC);
  this->trama["rainh1"] = String(this->medidas["rainh1"], DEC);
  this->trama["rainh2"] = String(this->medidas["rainh2"], DEC);

  String buffer_tx = "";
  buffer_tx = "A/" + this->trama["rainh1"] +
               "/" + this->trama["rainh2"] +
               "/" + this->trama["peso_malla1"] +
               "/" + this->trama["peso_malla2"] +
               "/" + "0" +
               "/F";

  Serial1.println(buffer_tx);
  Serial.println(buffer_tx);
}

void Estacion::enviar_muestra() {
  std::map<String, String> muestra;

  muestra["peso_malla1"] = String(this->medidas["peso_malla1"] / this->contador["peso_malla1"]);
  muestra["peso_malla2"] = String(this->medidas["peso_malla2"] / this->contador["peso_malla2"]);
  muestra["rainh1"] = String(this->medidas["rainh1"] / this->contador["rainh1"]);
  muestra["rainh2"] = String(this->medidas["rainh2"] / this->contador["rainh2"]);

  LOG_INFO("Peso Malla 1: " + muestra["peso_malla1"]);
  LOG_INFO("Peso Malla 2: " + muestra["peso_malla2"]);
  LOG_INFO("Pluviometro 1: " + muestra["rainh1"]);
  LOG_INFO("Pluviometro 2: " + muestra["rainh2"]);
}

void Estacion::siguiente_ssid() {
  this->iterador_internet++;
  if (this->iterador_internet == this->internet.size()) {
    this->iterador_internet = 0;
  }
}