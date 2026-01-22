#include "config.h"

#include "Estacion.h"

SEN15901* sen15901 = nullptr;
DAVIS6450* davis6450 = nullptr;
DHT_Unified* dht = nullptr;
DS18B20* ds18b20 = nullptr;
Estacion* estacion = nullptr;

unsigned long tiempo_base_envio;
unsigned long tiempo_base_internet;
unsigned long tiempo_base_utc;
unsigned long tiempo_base_medida_s;
unsigned long tiempo_base_medida_10s;
unsigned long tiempo_base_medida_m;
unsigned long tiempo_base_muestra;
bool bandera_ip = true;
bool bandera_tiempo_envio = true;

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

void chequear_utc() {
  unsigned long tiempo_transcurrido_utc = millis() - tiempo_base_utc;

  if ((tiempo_transcurrido_utc >= TIEMPO_SINCRONIZAR_UTC * VALOR_S) || estacion->obtener_bandera_utc()) {
    tiempo_base_utc = millis();
    estacion->definir_bandera_utc(false);
    estacion->pedir_utc();
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  unsigned long tiempo_base = millis();
  tiempo_base_envio = tiempo_base;
  tiempo_base_internet = tiempo_base;
  tiempo_base_utc = tiempo_base;
  tiempo_base_medida_s = tiempo_base;
  tiempo_base_medida_10s = tiempo_base;
  tiempo_base_medida_m = tiempo_base;
  tiempo_base_muestra = tiempo_base;

  sen15901 = new SEN15901(PIN_VIENTO, PIN_PRECIPITACION, PIN_VELETA);
  davis6450 = new DAVIS6450(PIN_RADIACION_SOLAR);
  dht = new DHT_Unified(PIN_DHT, TIPO_DHT);
  ds18b20 = new DS18B20(PIN_DS18B20);
  estacion = new Estacion(
    *sen15901,
    *davis6450,
    *dht,
    *ds18b20
  );
}

void loop() {
  if (estacion) {
    chequear_conexion();
    chequear_utc();

    estacion->realizar_medidas_ms();

    unsigned long tiempo_transcurrido_medida_s = millis() - tiempo_base_medida_s;

    if (tiempo_transcurrido_medida_s >= VALOR_S) {
      tiempo_base_medida_s = millis();
      estacion->realizar_medidas_s();

      if((estacion->obtener_minuto_actual() - 9) % 10 == 0) {
        bandera_tiempo_envio = true;
        estacion->definir_bandera_tiempo_correcto(true);
      }
    }

    unsigned long tiempo_transcurrido_medida_10s = millis() - tiempo_base_medida_10s;

    if (tiempo_transcurrido_medida_10s >= VALOR_10S * VALOR_S) {
      tiempo_base_medida_10s = millis();
      estacion->realizar_medidas_10s();
    }

    unsigned long tiempo_transcurrido_medida_m = millis() - tiempo_base_medida_m;

    if (tiempo_transcurrido_medida_m >= VALOR_M * VALOR_S) {
      tiempo_base_medida_m = millis();
      estacion->realizar_medidas_m();
    }

    unsigned long tiempo_transcurrido_muestra = millis() - tiempo_base_muestra;

    if (tiempo_transcurrido_muestra >= TIEMPO_MUESTRA * VALOR_S) {
      tiempo_base_muestra = millis();
      estacion->enviar_muestra();
    }

    unsigned long tiempo_transcurrido_envio = millis() - tiempo_base_envio;

    if ((WiFi.status() == WL_CONNECTED && estacion->obtener_bandera_tiempo_correcto()) && (tiempo_transcurrido_envio >= TIEMPO_ENVIO_S * VALOR_S || (estacion->obtener_minuto_actual() % 10 == 0 && bandera_tiempo_envio))) {
      bandera_tiempo_envio = false;
      estacion->definir_bandera_tiempo_correcto(false);
      tiempo_base_envio = millis();
      estacion->enviar_medidas();
    }

    delay(100);
  }
}
