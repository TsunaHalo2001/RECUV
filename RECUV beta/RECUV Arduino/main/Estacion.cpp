#include "Estacion.h"

Estacion::Estacion(SEN15901& _sensor_sen15901,
                   DAVIS6450& _sensor_davis6450,
                   DHT_Unified& _sensor_dht
    ) : sensor_sen15901(_sensor_sen15901),
        sensor_davis6450(_sensor_davis6450),
        sensor_dht(_sensor_dht),
        iterador_internet(0), 
        bandera_wifi(false) {

  this->medidas["fecha"] = "None";
  this->medidas["hora"] = "None";
  this->medidas["fecha_servidor"] = "None";
  this->medidas["temperatura_ambiente"] = "None";
  this->medidas["rain"] = "None";
  this->medidas["humedad_ambiente"] = "None";
  this->medidas["rad_solar"] = "None";
  this->medidas["dir_viento"] = "None";
  this->medidas["vel_viento"] = "None";

  this->internet.push_back({{"SSID", "Tsuna's Infinix Note 40 Pro"}, {"PASSWORD", "joanisa21"}});
  this->internet.push_back({{"SSID", "Univalle"}, {"PASSWORD", "Univalle"}});
  this->internet.push_back({{"SSID", "univalle"}, {"PASSWORD", "Univalle"}});
  this->internet.push_back({{"SSID", "WirelessNet"}, {"PASSWORD", "eeeeeeee"}});

  this->sensor_dht.begin();

  inicializar_wifi();
}

Estacion::~Estacion() = default;

[[nodiscard]] Reloj& Estacion::obtener_sensor_reloj() { return this->sensor_reloj; }
[[nodiscard]] SEN15901& Estacion::obtener_sensor_sen15901() { return this->sensor_sen15901; }
[[nodiscard]] DAVIS6450& Estacion::obtener_sensor_davis6450() { return this->sensor_davis6450; }
[[nodiscard]] DHT_Unified& Estacion::obtener_sensor_dht() { return this->sensor_dht; }
[[nodiscard]] std::map<String, String> Estacion::obtener_medidas() const { return this->medidas; }
[[nodiscard]] std::vector<std::map<String, String>> Estacion::obtener_internet() const { return this->internet; }
[[nodiscard]] int Estacion::obtener_iterador_internet() const { return this->iterador_internet; };
[[nodiscard]] bool Estacion::obtener_bandera_wifi() const { return this->bandera_wifi; }
[[nodiscard]] int Estacion::obtener_minuto_actual() const { return this->minuto_actual; }

void Estacion::definir_sensor_reloj(const Reloj& _sensor_reloj) { this->sensor_reloj = _sensor_reloj; }
void Estacion::definir_sensor_sen15901(const SEN15901& _sensor_sen15901) { this->sensor_sen15901 = _sensor_sen15901; }
void Estacion::definir_sensor_davis6450(const DAVIS6450& _sensor_davis6450) { this->sensor_davis6450 = _sensor_davis6450; }
void Estacion::definir_sensor_dht(const DHT_Unified& _sensor_dht) { this->sensor_dht = _sensor_dht; }
void Estacion::definir_medidas(const std::map<String, String>& _medidas) { this->medidas = _medidas; }
void Estacion::definir_internet(const std::vector<std::map<String, String>>& _internet) { this->internet = _internet; }
void Estacion::definir_iterador_internet(const int _iterador_internet) { this->iterador_internet = _iterador_internet; }
void Estacion::definir_bandera_wifi(const bool _bandera_wifi) { this->bandera_wifi = _bandera_wifi; }
void Estacion::definir_minuto_actual(const int _minuto_actual) { this->minuto_actual = _minuto_actual; }

//Reloj
void Estacion::pedir_utc() {
  deshabilitar_interrupcion_viento();
  deshabilitar_interrupcion_lluvia();
  this->sensor_davis6450.definir_bandera_espera(true);
  this->sensor_reloj.pedir_utc();
  habilitar_interrupcion_viento();
  habilitar_interrupcion_lluvia();
  this->sensor_davis6450.definir_bandera_espera(false);
}

bool Estacion::obtener_bandera_utc() const { return this->sensor_reloj.obtener_bandera_utc(); }
void Estacion::definir_bandera_utc(const bool _bandera_utc) { this->sensor_reloj.definir_bandera_utc(_bandera_utc); }
bool Estacion::obtener_bandera_tiempo_correcto() const { return this->sensor_reloj.obtener_bandera_tiempo_correcto(); }
void Estacion::definir_bandera_tiempo_correcto(const bool _bandera_tiempo_correcto) { this->sensor_reloj.definir_bandera_tiempo_correcto(_bandera_tiempo_correcto); }

//SEN15901
void Estacion::habilitar_interrupcion_viento() {
  this->sensor_sen15901.habilitar_interrupcion_viento();
}
void Estacion::habilitar_interrupcion_lluvia() {
  this->sensor_sen15901.habilitar_interrupcion_lluvia();
}
void Estacion::deshabilitar_interrupcion_viento() {
  this->sensor_sen15901.deshabilitar_interrupcion_viento();
}
void Estacion::deshabilitar_interrupcion_lluvia() {
  this->sensor_sen15901.deshabilitar_interrupcion_lluvia();
}

void Estacion::pedir_tiempo() {
  this->minuto_actual = this->sensor_reloj.obtener_minuto();
  this->medidas["fecha"] = this->sensor_reloj.obtener_tiempo();
  this->medidas["hora"] = this->medidas["fecha"];
  this->medidas["fecha_servidor"] = this->medidas["fecha"];
}

void Estacion::pedir_temperatura_ambiente() {
  sensors_event_t event;
  this->sensor_dht.temperature().getEvent(&event);
  this->medidas["temperatura_ambiente"] = String(event.temperature);
}

void Estacion::pedir_precipitacion() {
  this->medidas["rain"] = String(this->sensor_sen15901.pedir_precipitacion_s());
}

void Estacion::pedir_humedad_ambiente() {
  sensors_event_t event;
  this->sensor_dht.humidity().getEvent(&event);
  this->medidas["humedad_ambiente"] = String(event.relative_humidity);
}

void Estacion::pedir_radiacion_solar() {
  if (this->sensor_davis6450.obtener_bandera_espera()) return;
  this->medidas["rad_solar"] = String(this->sensor_davis6450.pedir_radiacion_solar());
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
  pedir_temperatura_ambiente();
  pedir_precipitacion();
  pedir_humedad_ambiente();
  pedir_radiacion_solar();
  pedir_direccion_viento();
  pedir_velocidad_viento_s();
}

void Estacion::realizar_medidas_m() {
}

void Estacion::enviar_medidas() {
  LOG_ADVER("No hay metodo de envio");
}

void Estacion::enviar_muestra() {
  LOG_INFO("Tiempo: " + this->medidas["fecha"]);
  LOG_INFO("Temperatura ambiente: " + this->medidas["temperatura_ambiente"]);
  LOG_INFO("Precipitacion: " + this->medidas["rain"]);
  LOG_INFO("Humedad ambiente: " + this->medidas["humedad_ambiente"]);
  LOG_INFO("Radiacion solar: " + this->medidas["rad_solar"]);
  LOG_INFO("Direccion del viento: " + this->medidas["dir_viento"]);
  LOG_INFO("Velocidad del viento: " + this->medidas["vel_viento"]);
}

void Estacion::inicializar_wifi() {
  if (WiFi.status() != WL_CONNECTED) {
    deshabilitar_interrupcion_viento();
    deshabilitar_interrupcion_lluvia();
    this->bandera_wifi = false;

    WiFi.disconnect(true); // Deletes current connection
    WiFi.mode(WIFI_OFF);   // Optional: turn off radio
    delay(100);
    WiFi.mode(WIFI_STA);   // Re-enable station mode

    std::map<String, String> conexion = this->internet.at(this->iterador_internet);
    LOG_WIFI("Intentando: " + conexion.at("SSID"));
    WiFi.begin(conexion.at("SSID"), conexion.at("PASSWORD"));

    siguiente_ssid();
    habilitar_interrupcion_viento();
    habilitar_interrupcion_lluvia();
  }
}

void Estacion::siguiente_ssid() {
  this->iterador_internet++;
  if (this->iterador_internet == this->internet.size()) {
    this->iterador_internet = 0;
  }
}