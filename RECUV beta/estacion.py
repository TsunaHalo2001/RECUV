import sensores.reloj       as reloj
import sensores.voltaje     as voltaje
import sensores.acs712      as acs712
import sensores.dht22       as dht22
import sensores.pluviometro as pluviometro
import sensores.bmp180      as bmp180
import sensores.davis6450   as davis6450
import sensores.veleta      as veleta
import sensores.anemometro  as anemometro
import sensores.ds18b20     as ds18b20
import sensores.fc28        as fc28

import machine
import network
import socket
import time

class EstacionMeteorologica:
  def __init__(self,
    voltaje_pin,
    acs712_pin,
    dht22_pin,
    pluviometro_pin,
    davis6450_pin,
    veleta_pin,
    anemometro_pin,
    ds18b20_pin,
    fc28_pin,
  ):
    self.tiempo_envio_s = 10

    self.sensor_reloj       = reloj.SensorReloj()
    self.sensor_voltaje     = voltaje.SensorVoltaje        (pin = voltaje_pin)
    self.sensor_acs712      = acs712.SensorACS712          (pin = acs712_pin)
    self.sensor_dht22       = dht22.SensorDHT22            (pin = dht22_pin) 
    self.sensor_pluviometro = pluviometro.SensorPluviometro(pin = pluviometro_pin)
    self.sensor_bmp180      = bmp180.SensorBMP180()
    self.sensor_davis6450   = davis6450.SensorDAVIS6450    (pin = davis6450_pin)
    self.sensor_veleta      = veleta.SensorVeleta          (pin = veleta_pin)
    self.sensor_anemometro  = anemometro.SensorAnemometro  (pin = anemometro_pin)
    self.sensor_ds18b20     = ds18b20.SensorDS18B20        (pin = ds18b20_pin)
    self.sensor_fc28        = fc28.SensorFC28              (pin = fc28_pin)

    self.medidas = {
      'fecha'                : self.sensor_reloj.obtener_tiempo(),
      'hora'                 : self.sensor_reloj.obtener_tiempo(),
      'fecha_servidor'       : self.sensor_reloj.obtener_tiempo(),
      'voltaje'              : None,
      'corriente'            : None,
      'temperatura_ambiente' : None,
      'rain'                 : None,
      'presion_atmos'        : None,
      'humedad_ambiente'     : None,
      'rad_solar'            : None,
      'dir_viento'           : None,
      'vel_viento'           : None,
      'temperatura_suelo'    : None,
      'humedad_suelo'        : None,
    }

    self.internet = [
      {'SSID' : "Tsuna's Infinix Note 40 Pro", 'PASSWORD' : 'joanisa21'},
      {'SSID' : 'Univalle',                    'PASSWORD' : 'Univalle'},
      {'SSID' : 'univalle',                    'PASSWORD' : 'Univalle'},
    ]

    self.wlan = network.WLAN()
    self.inicializar_wifi()

  def obtener_tiempo(self):
    self.medidas['fecha']                = self.sensor_reloj.obtener_tiempo()
    self.medidas['hora']                 = self.sensor_reloj.obtener_tiempo()
    self.medidas['fecha_servidor']       = self.sensor_reloj.obtener_tiempo()

  def obtener_voltaje(self):
    self.medidas['voltaje']              = self.sensor_voltaje.obtener_voltaje()

  def obtener_corriente(self):
    self.medidas['corriente']            = self.sensor_acs712.obtener_corriente()

  def obtener_temperatura_ambiente(self):
    self.medidas['temperatura_ambiente'] = self.sensor_dht22.obtener_temperatura()

  def obtener_precipitacion(self):
    self.medidas['rain']                 = self.sensor_pluviometro.obtener_precipitacion()

  def obtener_presion_atmosferica(self):
    self.medidas['presion_atmos']        = self.sensor_bmp180.obtener_presion_atmosferica()

  def obtener_humedad_ambiente(self):
    self.medidas['humedad_ambiente']     = self.sensor_dht22.obtener_humedad()

  def obtener_radiacion_solar(self):
    self.medidas['rad_solar']            = self.sensor_davis6450.obtener_radiacion_solar()

  def obtener_direccion_viento(self):
    self.medidas['dir_viento']           = self.sensor_veleta.obtener_direccion()

  def obtener_velocidad_viento(self):
    self.medidas['vel_viento']           = self.sensor_anemometro.obtener_velocidad()

  def obtener_temperatura_suelo(self):
    self.medidas['temperatura_suelo']    = self.sensor_ds18b20.obtener_temperatura()

  def obtener_humedad_suelo(self):
    self.medidas['humedad_suelo']        = self.sensor_fc28.obtener_humedad()

  def obtener_medidas(self):
    self.obtener_tiempo()
    self.obtener_voltaje()
    self.obtener_corriente()
    self.obtener_temperatura_ambiente()
    self.obtener_precipitacion()
    self.obtener_presion_atmosferica()
    self.obtener_humedad_ambiente()
    self.obtener_radiacion_solar()
    self.obtener_direccion_viento()
    self.obtener_velocidad_viento()
    self.obtener_temperatura_suelo()
    self.obtener_humedad_suelo()

  def enviar_medidas(self):
    print(self.medidas)

  def inicializar_wifi(self):
    bandera_wifi = True
    self.wlan.active(True)
    if not self.wlan.isconnected():
      for conexion in self.internet:
        print('Intentando: ', conexion['SSID'])
        try:
          self.wlan.connect(conexion['SSID'], conexion['PASSWORD'])
        except Exception as e:
          print(e)
          bandera_wifi = False
        
        while not self.wlan.isconnected():
          machine.idle()

        if self.wlan.isconnected():
          break

    if bandera_wifi:
        print('Conexión WiFi establecida:', self.wlan.ifconfig(), self.wlan.status())
        try:
          s = socket.socket()
          s.connect(("8.8.", 53))
          s.close()
        except:
          while True:
            time.sleep_ms(100)
