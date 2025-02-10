from SIM800LMANUAL import Modem
from time import *
import json
import network
import socket
from time import sleep
import os

import urequests as requests
import ujson


NUEVO_SERVER   = 'http://3.234.78.150:80/sigla/php/post.php'
SERVER_THOMASA = 'http://45.5.164.43:80/2022/sigla/php/post.php'
THOMASA2 = 'http://45.5.164.26:80/2022/sigla/php/post.php'
CLIMATE = 'http://climate.gismodel.click/sigla/php/post.php'


URL_GET_COMPUERTAS = 'http://44.207.50.4/sigla/PHP/controlCompuertas.php'
URL_GET_LAMINA     = 'http://44.207.50.4/sigla/php/controlLamina.php'
URL_GET_MUESTREO   = 'http://44.207.50.4/sigla/PHP/controlMuestreo.php' 
URL_GET_HORA       = 'http://44.207.50.4/sigla/php/controlHora.php'




class system_wifi():

    def __init__(self,SSID,PASSWORD):
        self.sta_if = network.WLAN(network.STA_IF)     # instancia el objeto -sta_if- para controlar la interfaz STA
        self.URL_POST=" "
        self.config(SSID,PASSWORD)
        self.sp_adm=0
        self.sp_eva=0
        self.modo = "auto"
        self.value=""
           
            
    def config(self,SSID,PASSWORD):
        time_out = 10
        if not self.sta_if.isconnected():              # si no existe conexión...
            self.sta_if.active(True)                       # activa el interfaz STA del ESP32
            self.sta_if.connect(SSID, PASSWORD)            # inicia la conexión con el AP
            print('Conectando a la red', SSID +"...")
            
            while not self.sta_if.isconnected():           # ...si no se ha establecido la conexión...
                print("Esperando: "+str(time_out))
                time_out=time_out-1
                sleep(1)
        print("")
        print("")
        print('Configuración de red (IP/netmask/gw/DNS):', self.sta_if.ifconfig())
        print('\r\nSistema inicializado por wifi...')
        
    def post_var_ambientales(self, value_data, server):  
        
        if server=='AWS':
            self.URL_POST=NUEVO_SERVER
        elif server=='THOMASA1':
            self.URL_POST=SERVER_THOMASA
        elif server=='THOMASA2':
            self.URL_POST=THOMASA2
        elif server=='CLIMATE':
            self.URL_POST=CLIMATE
            
        print(" ")
        print("Se enviaran datos al servidor: ")
        print(self.URL_POST)
        print("")
               
        data = json.dumps(value_data)
        r = requests.post(self.URL_POST, data=data)
        print(" ");
        print (r.text)
        print("Codigo Respuesta: "+ str(r.status_code))


    def post_var_consumo(self, value_data, server):
        if server=='AWS':
            self.URL_POST=NUEVO_SERVER
        elif server=='THOMASA1':
            self.URL_POST=SERVER_THOMASA
        elif server=='THOMASA2':
            self.URL_POST=THOMASA2
        elif server=='CLIMATE':
            self.URL_POST=CLIMATE
            
        print(" ")
        print("Se enviaran datos al servidor: ")
        print(self.URL_POST)
        print("")
               
        data = json.dumps(value_data)
        r = requests.post(self.URL_POST, data=data)
        print(" ");
        print (r.text)
        print("Codigo Respuesta: "+ str(r.status_code))
        
        
    def post_var_nivel(self, value_data, server):
        if server=='AWS':
            self.URL_POST=NUEVO_SERVER
        elif server=='THOMASA':
            self.URL_POST=SERVER_THOMASA
            
        print(" ")
        print("Se enviaran datos al servidor: ")
        print(self.URL_POST)
        print("")
               
        data = json.dumps(value_data)
        r = requests.post(self.URL_POST, data=data)
        print(" ");
        print (r.text)
        print("Codigo Respuesta: "+ str(r.status_code))
        
    def get_web(self, frame):
        
        if frame=='COMPUERTA':
            self.URL_POST= URL_GET_COMPUERTAS
        elif frame=='LAMINA':
            self.URL_POST= URL_GET_LAMINA
        elif frame=='MUESTREO':
            self.URL_POST= URL_GET_MUESTREO
        elif frame=='HORA':
            self.URL_POST= URL_GET_HORA

            
        print(" ")
        print("OBTENIENDO DATOS DEL SERVIDOR: ")
        print(self.URL_POST)
        print("")
               
        r = requests.get(self.URL_POST)
        print("Codigo Respuesta: "+ str(r.status_code))
        
        return r.text

class system_gprs():
    
    def __init__(self):
        self.modem    = ''
        self.APN      = 'internet.comcel.com.co'
        self.USER     = 'comcelweb'
        self.PASSWORD = 'comcelweb'
        self.URL_POST = NUEVO_SERVER
        #self.URL_GET  = 'http://3.84.72.198:80/sigla/php/nivdes_lamagua.php'
        self.URL_GET  = 'http://44.207.50.4/sigla/php/controlLamina.php'
    
    def config(self):
        #CREAMOS UN NUEVO OBJETO MODEM CON LOS SIGUIENTES PINES
        self.modem = Modem(MODEM_PWKEY_PIN    = 4,
                           MODEM_RST_PIN      = 5,
                           MODEM_POWER_ON_PIN = 23,
                           MODEM_TX_PIN       = 26,
                           MODEM_RX_PIN       = 27)
    
    def initialize(self):
        print('Inicializando...')

        # INICIAMOS EL MODEM
        self.modem.initialize()
        
        #DAMOS UN TIEMPO PRUDENTE PARA QUE EL MODEM INICIALICE
        sleep(10)
        
        # CONECTAMOS EL MODEM CON EL OPERADOR 
        self.modem.connect(apn=self.APN, user=self.USER, pwd=self.PASSWORD)
        print('\nModem IP address: "{}"'.format(self.modem.get_ip_addr()))
        
        self.modem.disconnect()
        
    def post_var_ambientales(self,sensor_amb,server):
        
        if server=='AWS':
            self.URL_POST=NUEVO_SERVER
        elif server=='THOMASA':
            self.URL_POST=SERVER_THOMASA
            
        print(self.URL_POST)
        
        self.modem.connect(apn=self.APN, user=self.USER, pwd=self.PASSWORD)
        print('METODO POST')
        
        data = json.dumps(sensor_amb)


        response = self.modem.http_request(self.URL_POST, 'POST', data, 'application/json')
        print('Response status code:', response.status_code)
        print('Response content:', response.content)
        self.modem.disconnect()
        
    def post_var_consumo(self,sensor_consumo,server):
        
        if server=='AWS':
            self.URL_POST=NUEVO_SERVER
        elif server=='THOMASA':
            self.URL_POST=SERVER_THOMASA
            
        print(self.URL_POST)
        
        self.modem.connect(apn=self.APN, user=self.USER, pwd=self.PASSWORD)
        print('METODO POST')
        
        data = json.dumps(sensor_consumo)


        response = self.modem.http_request(self.URL_POST, 'POST', data, 'application/json')
        print('Response status code:', response.status_code)
        print('Response content:', response.content)
        self.modem.disconnect()
        
        
    def post_var_nivel(self,sensor_nivel,server):
        
        if server=='AWS':
            self.URL_POST=NUEVO_SERVER
        elif server=='THOMASA':
            self.URL_POST=SERVER_THOMASA
            
        print(self.URL_POST)
        
        self.modem.connect(apn=self.APN, user=self.USER, pwd=self.PASSWORD)
        print('METODO POST')
        
        data = json.dumps(sensor_nivel)


        response = self.modem.http_request(self.URL_POST, 'POST', data, 'application/json')
        print('Response status code:', response.status_code)
        print('Response content:', response.content)
        self.modem.disconnect()
        
    def get_web(self, frame):
        
        APN        = self.APN
        USER       = self.USER
        PASSWORD   = self.PASSWORD
        URL_GET    = self.URL_GET
        modem      = self.modem
        
        if frame=='COMPUERTA':
            URL_GET= URL_GET_COMPUERTAS
        elif frame=='LAMINA':
            URL_GET= URL_GET_LAMINA
        elif frame=='MUESTREO':
            URL_GET= URL_GET_MUESTREO
        elif frame=='HORA':
            URL_GET= URL_GET_HORA
        
        modem.connect(apn=APN, user=USER, pwd=PASSWORD)
        print('\nModem IP address: "{}"'.format(modem.get_ip_addr()))
        
        # Example GET
        print('METODO GET')
        
        response = modem.http_request(URL_GET, 'GET')
        print('Response status code:', response.status_code)
        print('Response content:', response.content)
        modem.disconnect()
        return response.status_code, response.content
    def disconnect(self):
        APN        = self.APN
        USER       = self.USER
        PASSWORD   = self.PASSWORD
        URL_GET    = self.URL_GET
        modem      = self.modem
        modem.disconnect()
        
    def sendMSN(self, txt):
        
        modem = self.modem
        modem.writeATCMD('AT')
        modem.writeATCMD('AT+CMGF=1')
        modem.writeATCMD('AT+CMGS="+573007787444"')
        modem.writeATCMD(txt)
        modem.writeATCMD(26)
        
    def restartGPRS(self):
        self.modem.restartModem()
        
