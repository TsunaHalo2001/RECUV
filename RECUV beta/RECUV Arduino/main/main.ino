#include "config.h"

#include "Estacion.h"

Estacion* estacion = nullptr;
unsigned long tiempo_base_envio;
unsigned long tiempo_base_internet;
bool bandera_ip = true;

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
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());

      bandera_ip = false;
    }
  }
}

void setup() {
  Serial.begin(115200);

  tiempo_base_envio = millis();
  tiempo_base_internet = millis();

  estacion = new Estacion();
}

void loop() {
  if (estacion) {
    chequear_conexion();

    estacion->realizar_medidas();

    unsigned long tiempo_transcurrido_envio = millis() - tiempo_base_envio;

    if (tiempo_transcurrido_envio >= TIEMPO_ENVIO_S * VALOR_S) {
      tiempo_base_envio = millis();
      estacion->enviar_medidas();
    }

    delay(100);
  }
}
