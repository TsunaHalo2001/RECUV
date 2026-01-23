#include "Estacion.h"

Estacion::Estacion(SEN15901& _sensor_sen15901,
                   DAVIS6450& _sensor_davis6450,
                   DHT_Unified& _sensor_dht,
                   DS18B20& _sensor_ds18b20,
                   BMP280_DEV& _sensor_bmp280,
                   FC28& _sensor_fc28
    ) : sensor_sen15901(_sensor_sen15901),
        sensor_davis6450(_sensor_davis6450),
        sensor_dht(_sensor_dht),
        sensor_ds18b20(_sensor_ds18b20),
        sensor_bmp280(_sensor_bmp280),
        sensor_fc28(_sensor_fc28),
        iterador_internet(0), 
        bandera_wifi(false) {

  this->medidas["temperatura_ambiente"] = 0.0;
  this->medidas["rain"] = 0.0;
  this->medidas["presion_atmos"] = 0.0;
  this->medidas["humedad_ambiente"] = 0.0;
  this->medidas["rad_solar"] = 0.0;
  this->medidas["dir_viento"] = 0.0;
  this->medidas["vel_viento"] = 0.0;
  this->medidas["temperatura_suelo"] = 0.0;
  this->medidas["humedad_suelo"] = 0.0;

  this->contador["temperatura_ambiente"] = 1;
  this->contador["rain"] = 1;
  this->contador["presion_atmos"] = 1;
  this->contador["humedad_ambiente"] = 1;
  this->contador["rad_solar"] = 1;
  this->contador["vel_viento"] = 1;
  this->contador["temperatura_suelo"] = 1;
  this->contador["humedad_suelo"] = 1;

  this->trama["fecha"] = "None";
  this->trama["hora"] = "None";
  this->trama["fecha_servidor"] = "None";
  this->trama["temperatura_ambiente"] = "None";
  this->trama["rain"] = "None";
  this->trama["presion_atmos"] = "None";
  this->trama["humedad_ambiente"] = "None";
  this->trama["rad_solar"] = "None";
  this->trama["dir_viento"] = "None";
  this->trama["vel_viento"] = "None";
  this->trama["temperatura_suelo"] = "None";
  this->trama["humedad_suelo"] = "None";

  this->internet.push_back({{"SSID", "Tsuna's Infinix Note 40 Pro"}, {"PASSWORD", "joanisa21"}});
  this->internet.push_back({{"SSID", "Univalle"}, {"PASSWORD", "Univalle"}});
  this->internet.push_back({{"SSID", "univalle"}, {"PASSWORD", "Univalle"}});
  this->internet.push_back({{"SSID", "WirelessNet"}, {"PASSWORD", "eeeeeeee"}});

  this->sensor_dht.begin();

  this->sensor_bmp280.begin(BMP280_I2C_ALT_ADDR);
  this->sensor_bmp280.setTimeStandby(TIME_STANDBY_500MS);
  this->sensor_bmp280.startNormalConversion();

  inicializar_wifi();
}

Estacion::~Estacion() = default;

[[nodiscard]] Reloj& Estacion::obtener_sensor_reloj() { return this->sensor_reloj; }
[[nodiscard]] SEN15901& Estacion::obtener_sensor_sen15901() { return this->sensor_sen15901; }
[[nodiscard]] DAVIS6450& Estacion::obtener_sensor_davis6450() { return this->sensor_davis6450; }
[[nodiscard]] DHT_Unified& Estacion::obtener_sensor_dht() { return this->sensor_dht; }
[[nodiscard]] DS18B20& Estacion::obtener_sensor_ds18b20() { return this->sensor_ds18b20; }
[[nodiscard]] BMP280_DEV& Estacion::obtener_sensor_bmp280() { return this->sensor_bmp280; }
[[nodiscard]] FC28& Estacion::obtener_sensor_fc28() { return this->sensor_fc28; }
[[nodiscard]] std::map<String, float> Estacion::obtener_medidas() const { return this->medidas; }
[[nodiscard]] std::map<String, int> Estacion::obtener_contador() const { return this->contador; }
[[nodiscard]] std::map<String, String> Estacion::obtener_trama() const { return this->trama; }
[[nodiscard]] std::vector<std::map<String, String>> Estacion::obtener_internet() const { return this->internet; }
[[nodiscard]] int Estacion::obtener_iterador_internet() const { return this->iterador_internet; };
[[nodiscard]] bool Estacion::obtener_bandera_wifi() const { return this->bandera_wifi; }
[[nodiscard]] int Estacion::obtener_minuto_actual() const { return this->minuto_actual; }

void Estacion::definir_sensor_reloj(const Reloj& _sensor_reloj) { this->sensor_reloj = _sensor_reloj; }
void Estacion::definir_sensor_sen15901(const SEN15901& _sensor_sen15901) { this->sensor_sen15901 = _sensor_sen15901; }
void Estacion::definir_sensor_davis6450(const DAVIS6450& _sensor_davis6450) { this->sensor_davis6450 = _sensor_davis6450; }
void Estacion::definir_sensor_dht(const DHT_Unified& _sensor_dht) { this->sensor_dht = _sensor_dht; }
void Estacion::definir_sensor_ds18b20(const DS18B20& _sensor_ds18b20) { this->sensor_ds18b20 = _sensor_ds18b20; }
void Estacion::definir_sensor_fc28(const FC28& _sensor_fc28) { this->sensor_fc28 = _sensor_fc28; }
void Estacion::definir_medidas(const std::map<String, float>& _medidas) { this->medidas = _medidas; }
void Estacion::definir_contador(const std::map<String, int>& _contador) { this->contador = _contador; }
void Estacion::definir_trama(const std::map<String, String>& _trama) { this->trama = _trama; }
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
  this->trama["fecha"] = this->sensor_reloj.obtener_tiempo();
  this->trama["hora"] = this->trama["fecha"];
  this->trama["fecha_servidor"] = this->trama["fecha"];
}

void Estacion::pedir_temperatura_ambiente() {
  sensors_event_t event;
  if(isnan(event.temperature)) return;
  this->medidas["temperatura_ambiente"] += event.temperature;
  this->contador["temperatura_ambiente"]++;
}

void Estacion::pedir_precipitacion() {
  this->medidas["rain"] = this->sensor_sen15901.pedir_precipitacion_s();
  this->contador["rain"]++;
}

void Estacion::pedir_presion() {
  float temperatura, presion, altitud;
  if(!this->sensor_bmp280.getMeasurements(temperatura, presion, altitud)) return;
  this->medidas["presion_atmos"] = presion;
  this->contador["presion_atmos"]++;
}

void Estacion::pedir_humedad_ambiente() {
  sensors_event_t event;
  this->sensor_dht.humidity().getEvent(&event);
  this->medidas["humedad_ambiente"] = event.relative_humidity;
  this->contador["humedad_ambiente"]++;
}

void Estacion::pedir_radiacion_solar() {
  if (this->sensor_davis6450.obtener_bandera_espera()) return;
  this->medidas["rad_solar"] = this->sensor_davis6450.pedir_radiacion_solar();
  this->contador["rad_solar"]++;
}

void Estacion::pedir_direccion_viento() {
  this->medidas["dir_viento"] = this->sensor_sen15901.pedir_direccion_viento();
}

void Estacion::pedir_velocidad_viento_s() {
  this->medidas["vel_viento"] = this->sensor_sen15901.pedir_velocidad_viento_s();
  this->contador["vel_viento"]++;
}

void Estacion::pedir_velocidad_viento_m() {
  this->medidas["vel_viento"] = this->sensor_sen15901.pedir_velocidad_viento_m();
  this->contador["vel_viento"]++;
}

void Estacion::pedir_temperatura_suelo() {
  float valor = this->sensor_ds18b20.pedir_temperatura();
  if (valor < -120) return;
  this->medidas["temperatura_suelo"] = valor;
  this->contador["temperatura_suelo"]++;
}

void Estacion::pedir_humedad_suelo() {
  float valor = this->sensor_fc28.pedir_humedad();
  this->medidas["humedad_suelo"] = valor;
  this->contador["humedad_suelo"]++;
}

void Estacion::realizar_medidas_ms() {
  if (!this->sensor_ds18b20.obtener_bandera_exito()) {
    pedir_temperatura_suelo();
  }
}

void Estacion::realizar_medidas_s() {
  pedir_tiempo();
  pedir_temperatura_ambiente();
  pedir_precipitacion();
  pedir_presion();
  pedir_humedad_ambiente();
  pedir_radiacion_solar();
  pedir_direccion_viento();
  pedir_velocidad_viento_s();
  pedir_temperatura_suelo();
  pedir_humedad_suelo();
}

void Estacion::realizar_medidas_10s() {
}

void Estacion::realizar_medidas_m() {
}

void Estacion::enviar_medidas() {
  LOG_ADVER("No hay metodo de envio");
}

void Estacion::enviar_muestra() {
  std::map<String, String> muestra;

  muestra["fecha"] = this->trama["fecha"];
  muestra["temperatura_ambiente"] = String(this->medidas["temperatura_ambiente"] / this->contador["temperatura_ambiente"]);
  muestra["rain"] = String(this->medidas["rain"] / this->contador["rain"]);
  muestra["presion_atmos"] = String(this->medidas["presion_atmos"] / this->contador["presion_atmos"]);
  muestra["humedad_ambiente"] = String(this->medidas["humedad_ambiente"] / this->contador["humedad_ambiente"]);
  muestra["rad_solar"] = String(this->medidas["rad_solar"] / this->contador["rad_solar"]);
  muestra["dir_viento"] = String(this->medidas["dir_viento"]);
  muestra["vel_viento"] = String(this->medidas["vel_viento"] / this->contador["vel_viento"]);
  muestra["temperatura_suelo"] = String(this->medidas["temperatura_suelo"] / this->contador["temperatura_suelo"]);
  muestra["humedad_suelo"] = String(this->medidas["humedad_suelo"] / this->contador["humedad_suelo"]);

  LOG_INFO("Tiempo: " + muestra["fecha"]);
  LOG_INFO("Temperatura ambiente: " + muestra["temperatura_ambiente"]);
  LOG_INFO("Precipitacion: " + muestra["rain"]);
  LOG_INFO("Presion atmosferica: " + muestra["presion_atmos"]);
  LOG_INFO("Humedad ambiente: " + muestra["humedad_ambiente"]);
  LOG_INFO("Radiacion solar: " + muestra["rad_solar"]);
  LOG_INFO("Direccion del viento: " + muestra["dir_viento"]);
  LOG_INFO("Velocidad del viento: " + muestra["vel_viento"]);
  LOG_INFO("Temperatura del suelo: " + muestra["temperatura_suelo"]);
  LOG_INFO("Humedad del suelo: " + muestra["humedad_suelo"]);
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