from machine import Pin
import time
import estacion

estacion = estacion.EstacionMeteorologica(
  acs712_pin = 1,
  voltaje_pin = 2,
  anemometro_pin = 4,
  veleta_pin = 5,
  pluviometro_pin = 6,
  fc28_pin = 7,
  ds18b20_pin = 15,
  davis6450_pin = 16,
  dht22_pin = 17,
)

def main():
  tiempo_inicio = time.ticks_ms()

  while True:
    chequear_conexion()

    estacion.obtener_medidas()

    tiempo_transcurrido = time.ticks_diff(time.ticks_ms(), tiempo_inicio)

    if tiempo_transcurrido >= estacion.tiempo_envio_s * 1000:
      tiempo_inicio = time.ticks_ms()
      estacion.enviar_medidas()

    time.sleep_ms(100)

def chequear_conexion():
  if not estacion.wlan.isconnected():
    estacion.inicializar_wifi()

if __name__ == "__main__":
  main()