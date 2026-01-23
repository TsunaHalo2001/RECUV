#include "config.h"

#include "Estacion.h"

SEN15901* sen15901   = nullptr;
DAVIS6450* davis6450 = nullptr;
DHT_Unified* dht     = nullptr;
DS18B20* ds18b20     = nullptr;
BMP280_DEV* bmp280   = nullptr;
FC28* fc28           = nullptr;
Estacion* estacion   = nullptr;

unsigned long tiempo_base_envio;
unsigned long tiempo_base_internet;
unsigned long tiempo_base_utc;
unsigned long tiempo_base_medida_s;
unsigned long tiempo_base_medida_10s;
unsigned long tiempo_base_medida_m;
unsigned long tiempo_base_muestra;

int tiempo_envio_s         = TIEMPO_ENVIO_S;
int tiempo_sincronizar_utc = TIEMPO_SINCRONIZAR_UTC;

bool bandera_ip           = true;
bool bandera_tiempo_envio = true;

std::vector<String> direcciones;
int version_json = VERSION_JSON;

void chequear_conexion() {
  unsigned long tiempo_transcurrido_internet = millis() - tiempo_base_internet;

  if (tiempo_transcurrido_internet >= TIEMPO_ESPERA_WIFI * VALOR_S) {
    if (!bandera_ip && WiFi.status() != WL_CONNECTED) {
      bandera_ip = true;
    }

    estacion->definir_bandera_wifi(true);

    tiempo_base_internet = millis();
    estacion->inicializar_wifi();

    if(estacion->obtener_bandera_wifi() && bandera_ip) {
      LOG_WIFI("IP address: " + WiFi.localIP().toString());

      estacion->pedir_utc();
      bandera_ip = false;
    }
  }
}

void pedir_variables() {
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

void chequear_variables() {
  unsigned long tiempo_transcurrido_utc = millis() - tiempo_base_utc;

  if ((tiempo_transcurrido_utc >= tiempo_sincronizar_utc * VALOR_S) || estacion->obtener_bandera_utc()) {
    tiempo_base_utc = millis();
    estacion->definir_bandera_utc(false);
    estacion->pedir_utc();
  }
}

void medir_s() {
  unsigned long tiempo_transcurrido_medida_s = millis() - tiempo_base_medida_s;

  if (tiempo_transcurrido_medida_s >= VALOR_S) {
    tiempo_base_medida_s = millis();
    estacion->realizar_medidas_s();

    if((estacion->obtener_minuto_actual() - 9) % 10 == 0) {
      bandera_tiempo_envio = true;
      estacion->definir_bandera_tiempo_correcto(true);
    }
  }
}

void medir_10s() {
  unsigned long tiempo_transcurrido_medida_10s = millis() - tiempo_base_medida_10s;

  if (tiempo_transcurrido_medida_10s >= VALOR_10S * VALOR_S) {
    tiempo_base_medida_10s = millis();
    estacion->realizar_medidas_10s();
  }
}

void medir_m() {
  unsigned long tiempo_transcurrido_medida_m = millis() - tiempo_base_medida_m;

  if (tiempo_transcurrido_medida_m >= VALOR_M * VALOR_S) {
    tiempo_base_medida_m = millis();
    estacion->realizar_medidas_m();
  }
}

void muestra() {
  unsigned long tiempo_transcurrido_muestra = millis() - tiempo_base_muestra;

  if (tiempo_transcurrido_muestra >= TIEMPO_MUESTRA * VALOR_S) {
    tiempo_base_muestra = millis();
    estacion->enviar_muestra();
  }
}

void enviar() {
  unsigned long tiempo_transcurrido_envio = millis() - tiempo_base_envio;

  if ((WiFi.status() == WL_CONNECTED && estacion->obtener_bandera_tiempo_correcto()) && (tiempo_transcurrido_envio >= tiempo_envio_s * VALOR_S || (estacion->obtener_minuto_actual() % 10 == 0 && bandera_tiempo_envio))) {
    bandera_tiempo_envio = false;
    estacion->definir_bandera_tiempo_correcto(false);
    tiempo_base_envio = millis();
    estacion->enviar_medidas();
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  unsigned long tiempo_base = millis();
  tiempo_base_envio      = tiempo_base;
  tiempo_base_internet   = tiempo_base;
  tiempo_base_utc        = tiempo_base;
  tiempo_base_medida_s   = tiempo_base;
  tiempo_base_medida_10s = tiempo_base;
  tiempo_base_medida_m   = tiempo_base;
  tiempo_base_muestra    = tiempo_base;

  direcciones.push_back("http://45.5.164.43:80/2022/sigla/php/post_k18.php");
  direcciones.push_back("http://45.5.164.26:80/2022/sigla/php/post_k18.php");
  direcciones.push_back("http://climate.gismodel.click/2022/sigla/php/post_k18.php");
  direcciones.push_back("http://192.168.46.4:80/2022/sigla/php/post_k18.php");
  direcciones.push_back("http://192.168.46.6:80/2022/sigla/php/post_k18.php");

  sen15901  = new SEN15901(PIN_VIENTO, PIN_PRECIPITACION, PIN_VELETA);
  davis6450 = new DAVIS6450(PIN_RADIACION_SOLAR);
  dht       = new DHT_Unified(PIN_DHT, TIPO_DHT);
  ds18b20   = new DS18B20(PIN_DS18B20);
  bmp280    = new BMP280_DEV(SDA_1, SCL_1);
  fc28      = new FC28(PIN_FC28);
  estacion  = new Estacion(
    *sen15901,
    *davis6450,
    *dht,
    *ds18b20,
    *bmp280,
    *fc28
  );
}

void loop() {
  if (estacion) {
    chequear_conexion();
    chequear_variables();

    estacion->realizar_medidas_ms();
    medir_s();
    medir_10s();
    medir_m();

    muestra();

    enviar();

    delay(100);
  }
}
