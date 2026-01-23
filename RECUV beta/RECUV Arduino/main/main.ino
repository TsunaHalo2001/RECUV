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
bool bandera_variables    = true;
bool bandera_envio        = false;

std::vector<String> direcciones;
std::vector<bool> banderas_envio;
int version_json = VERSION_JSON;

String buffer_tx = "";
char ARDString[100] = "";
bool banderaARDRX = false;
int contadorFRAMEARDRX = 0;
char *ptr = NULL;

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
      pedir_variables();
      bandera_ip = false;
    }
  }
}

void pedir_variables() {
  if (WiFi.status() != WL_CONNECTED) return;

  estacion->deshabilitar_interrupcion_viento();
  estacion->deshabilitar_interrupcion_lluvia();
  
  HTTPClient http;
  http.begin(VARIABLES_API); // Uses WiFiClient internally
  http.addHeader(UTC_HEADER_NAME, UTC_HEADER_VALUE);
  LOG_HTTP("GET: " + String(VARIABLES_API));
  int code = http.GET();
  LOG_HTTP("Codigo de estado: " + String(code));
  if (code == -1 || code == -4 || code == -5 || code == -7 || code == -11) {
    bandera_variables = true;
  }
  else if (code == 200) {
    bandera_variables = false;
    WiFiClient *client = http.getStreamPtr();

    JsonDocument doc;

    DeserializationError error = deserializeJson(doc, *client);

    if (error) {
      LOG_ERROR("JSON parseado fallido: " + String(error.c_str()));
      http.end();
      estacion->habilitar_interrupcion_viento();
      estacion->habilitar_interrupcion_lluvia();
      return;
    }

    int version = doc["version"];
    if (version == version_json) {
      LOG_JSON("La version de las variables es la misma: " + String(version));
      http.end();
      estacion->habilitar_interrupcion_viento();
      estacion->habilitar_interrupcion_lluvia();
      return;
    }

    version_json = version;

    tiempo_envio_s = doc["variables"]["tiempo_envio_s"];
    tiempo_sincronizar_utc = doc["variables"]["tiempo_sincronizar_utc"];

    JsonArray urls = doc["post_urls"];

    direcciones.clear();
    banderas_envio.clear();

    for (int i = 0; i < urls.size(); i++) {
      direcciones.push_back(urls[i]);
      banderas_envio.push_back(false);
    }

    LOG_JSON("Se encontraron " + String(urls.size()) + " direcciones");
  }
  else {
    bandera_variables = false;
  }
  http.end();

  estacion->habilitar_interrupcion_viento();
  estacion->habilitar_interrupcion_lluvia();
}

void chequear_variables() {
  unsigned long tiempo_transcurrido_utc = millis() - tiempo_base_utc;

  if ((tiempo_transcurrido_utc >= tiempo_sincronizar_utc * VALOR_S) || estacion->obtener_bandera_utc()) {
    tiempo_base_utc = millis();
    estacion->definir_bandera_utc(false);
    estacion->pedir_utc();
  }

  if ((tiempo_transcurrido_utc >= tiempo_sincronizar_utc * VALOR_S) || bandera_variables) {
    bandera_variables = false;
    pedir_variables();
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

    for (int i = 0; i < banderas_envio.size(); i++) {
      if (banderas_envio.at(i)) {
        banderas_envio[i] = estacion->enviar_medidas(direcciones.at(i));
        delay(100);
      }
    }
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

  if ((WiFi.status() == WL_CONNECTED && estacion->obtener_bandera_tiempo_correcto()) && (bandera_envio || tiempo_transcurrido_envio >= tiempo_envio_s * VALOR_S || (estacion->obtener_minuto_actual() % 10 == 0 && bandera_tiempo_envio))) {
    bandera_envio = false;
    bandera_tiempo_envio = false;
    estacion->definir_bandera_tiempo_correcto(false);
    tiempo_base_envio = millis();
    for (int i = 0; i < direcciones.size(); i++) {
      banderas_envio[i] = estacion->enviar_medidas(direcciones.at(i));
      delay(100);
    }
  }
}

void recibo_arduino() {
  char delimitadores[] = "/";
  if(banderaARDRX) {
    Serial1.println("K/0/X");
    Serial.println(ARDString);

    contadorFRAMEARDRX = 0;

    ptr = strtok(ARDString, "F");
    ptr = strtok(ARDString, "/");

    while(ptr != NULL) {
      switch(contadorFRAMEARDRX) {
        case 1: estacion->obtener_medidas()["rainh1"] = atof(ptr); break;
        case 2: estacion->obtener_medidas()["rainh2"] = atof(ptr); break;
        case 3: estacion->obtener_medidas()["peso_malla1"] = atof(ptr); break;
        case 4: estacion->obtener_medidas()["peso_malla2"] = atof(ptr); break;
        case 5: estacion->obtener_medidas()["extin_visual"] = atof(ptr); break;
      }
      ptr = strtok(NULL, delimitadores);
      contadorFRAMEARDRX++;
    }
    estacion->obtener_contador()["arduino"]++;
    banderaARDRX = false;
  }
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, RX_1, TX_1);
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

  banderas_envio.push_back(false);
  banderas_envio.push_back(false);
  banderas_envio.push_back(false);
  banderas_envio.push_back(false);
  banderas_envio.push_back(false);

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

    recibo_arduino();

    delay(100);
  }
}
