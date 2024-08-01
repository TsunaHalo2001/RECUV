# Escribe tu código aquí :-)
from system_communication import *
from machine import *
import json
from time import *
import network
from bmp180 import BMP180

i2c = SoftI2C(scl=Pin(22), sda=Pin(21), freq = 100000)
i2c.scan()

bmp180 = BMP180(i2c)
bmp180.oversample_sett = 3
bmp180.baseline = 101325

wdt = WDT(timeout=60000)

import urequests as requests
import ujson

TIAMPO_SONDEO_CONST = 10*60   # CANT_MINUTOS  * 60 SEG

global CONNECTION_MODE, SSID, PASSWORD
global modemwifi


CONNECTION_MODE  = "WIFI"

#SSID     = "univalle"
#PASSWORD = "Univalle"

SSID     = "GISMODEL02"
PASSWORD = "GISMODEL24"

global tramaRx, sensor_values, gprs, modemwifi, bandera_muestreo
global textoCompuerta,textoLamina, textoMuestreo, textoHora, t_envio, contador_envio
global banderaConsumo, banderaNivel, banderaAmb
global consumoIF, nivelIF, ambIF
global tiempoSONDEOWEB
global trama



textoCompuerta =" "
textoLamina    =" "
textoMuestreo  =" "
textoHora      =" "


uart = UART(1, 9600)

#------------------------------------------------------------------#
#                        VARIABLES DE CONSUMO                      #
#------------------------------------------------------------------#

#CREAMOS UN DICCIONARIO DONDE GUARDAREMOS LAS VARIABLES DE CONSUMO

sensor_values = {
    "fecha":"2022-05-25 10:00:00",
    "hora":"2022-05-25 10:00:00",
    "fecha_servidor":"2022-05-25 10:00:00",
    "voltaje":"26.8",
    "corriente":"5.5",
    "temperatura_ambiente":"45",
    "rain":"30",
    "presion_atmos":"55",
    "humedad_ambiente":"40",
    "rad_solar":"35",
    "dir_viento":"70",
    "vel_viento":"50",
    "temperatura_suelo":"60",
    "humedad_suelo":"65",
    "extin_visual":"75",
    "peso_malla1":"80",
    "peso_malla2":"85",
    "rainh1":"90",
    "rainh2":"95"
}

def interpreta_trama(tramaRx):
    global gprs, bandera_muestreo, modemwifi, CONNECTION_MODE, sensor_values
    global banderaConsumo, banderaNivel, banderaAmb
    global trama
    try:
        if(tramaRx[0] == "b'T"):
           print("Llegaron variables Temporales")
           dia  = tramaRx[3]
           mes  = tramaRx[2]
           anio = tramaRx[1]
           hora = tramaRx[4]
           minn = tramaRx[5]
           seg  = tramaRx[6]

           dia  = int(dia)
           mes  = int(mes)
           hora = int(hora)
           minn = int(minn)
           seg  = int(seg)

           dia  = '{0:02d}'.format(dia)
           mes  = '{0:02d}'.format(mes)
           hora = '{0:02d}'.format(hora)
           minn = '{0:02d}'.format(minn)
           seg  = '{0:02d}'.format(seg)

           fechaTemporal = anio+'-'+mes+'-'+dia+' '+hora+':'+minn+':'+seg
            
           sensor_values['fecha']    = fechaTemporal
           sensor_values['hora']    = fechaTemporal
           sensor_values['fecha_servidor']    = fechaTemporal

        elif (tramaRx[0] == "b'A"):

            print("Llegaron variables Ambientales")
            rad_solar = tramaRx[1]
            fc28      = tramaRx[2]
            dht22_tmp = tramaRx[3]
            dht22_hum = tramaRx[4]
            ds18b     = tramaRx[5]
            anemo     = tramaRx[6]
            pluvi     = tramaRx[7]
            #bmp       = tramaRx[8]
            try:
                p = bmp180.pressure
            except:
                p = 0
            bmp = p / 100
            dirviento = tramaRx[9]
            extin_visual = tramaRx[14]
            peso_malla1 = tramaRx[12]
            peso_malla2 = tramaRx[13]
            rainh1      = tramaRx[10]
            rainh2      = tramaRx[11]

            rad_solar = float(rad_solar)
            fc28      = float(fc28)
            dht22_tmp = float(dht22_tmp)
            dht22_hum = float(dht22_hum)
            ds18b     = float(ds18b)
            anemo     = float(anemo)
            pluvi     = float(pluvi)
            bmp       = float(bmp)
            dirviento = float(dirviento)
            extin_visual = float(extin_visual)
            peso_malla1 = float(peso_malla1)
            peso_malla2 = float(peso_malla2)
            rainh1      = float(rainh1)
            rainh2      = float(rainh2)

            rad_solar = '{0:.2f}'.format(rad_solar)
            fc28      = '{0:.2f}'.format(fc28)
            dht22_tmp = '{0:.2f}'.format(dht22_tmp)
            dht22_hum = '{0:.2f}'.format(dht22_hum)
            ds18b     = '{0:.2f}'.format(ds18b)
            anemo     = '{0:.2f}'.format(anemo)
            pluvi     = '{0:.2f}'.format(pluvi)
            bmp       = '{0:.2f}'.format(bmp)
            dirviento = '{0:.2f}'.format(dirviento)
            extin_visual = '{0:.2f}'.format(extin_visual)
            peso_malla1 = '{0:.2f}'.format(peso_malla1)
            peso_malla2 = '{0:.2f}'.format(peso_malla2)
            rainh1      = '{0:.2f}'.format(rainh1)
            rainh2      = '{0:.2f}'.format(rainh2)

            sensor_values['rain']=str(pluvi)
            sensor_values['rad_solar']    =str(rad_solar)
            sensor_values['humedad_ambiente']     =str(dht22_hum)
            sensor_values['temperatura_ambiente']    =str(dht22_tmp)
            sensor_values['vel_viento']   =str(anemo)
            sensor_values['presion_atmos']     =str(bmp)
            sensor_values['temperatura_suelo']   =str(ds18b)
            sensor_values['humedad_suelo']    =str(fc28)
            sensor_values['dir_viento']    =str(dirviento)
            sensor_values['extin_visual'] =str(extin_visual)
            sensor_values['peso_malla1']  =str(peso_malla1)
            sensor_values['peso_malla2']  =str(peso_malla2)
            sensor_values['rainh1']       =str(rainh1)
            sensor_values['rainh2']       =str(rainh2)

            banderaAmb=1
        #             print(f'dht22_tmp: {dht22_tmp}')
        #             print(f'ds18b: {ds18b}')
        #             print(f'anemo: {anemo}')
        #             print(f'pluvi: {pluvi}')
        #             print(f'bmp: {bmp}')
        #             print("------------------------")
        #             print(" ")

        elif (tramaRx[0] == "b'C"):
            print("Llegaron variables de Consumo")
            Vcarga1   = tramaRx[1]
            Icarga1   = tramaRx[2]
            Carga1    = tramaRx[3]
            Iconsumo1 = tramaRx[4]
            Consumo1  = tramaRx[5]

            Vcarga1   = float(Vcarga1)
            Icarga1   = float(Icarga1)
            Carga1    = float(Carga1)
            Iconsumo1 = float(Iconsumo1)
            Consumo1  = float(Consumo1)

            Vcarga1   = '{0:.2f}'.format(Vcarga1)
            Icarga1   = '{0:.2f}'.format(Icarga1)
            Carga1    = '{0:.2f}'.format(Carga1)
            Iconsumo1 = '{0:.2f}'.format(Iconsumo1)
            Consumo1  = '{0:.2f}'.format(Consumo1)

            sensor_values['voltaje']   = Vcarga1
            sensor_values['corriente']   = Icarga1

            banderaConsumo=1
            
        elif(tramaRx[0] == "b'G"):
            print("Reenviando datos al ATMEGA2560")
            uart.write(trama)
    except:
        print("Error recibiendo trama de arduino")
        print("Se solicitan nuevamente datos")
        return 1
    
    if (tramaRx[0] == "b'E"):
        if CONNECTION_MODE == "WIFI":
            enviarWifi()
        elif CONNECTION_MODE == "GPRS":
            enviarGprs()

    tramaRx = " "
    bandera_muestreo = True
    return 0

def enviarWifi():
    global gprs, bandera_muestreo, modemwifi, CONNECTION_MODE
    global banderaConsumo, banderaNivel, banderaAmb
    try:
        if banderaAmb == 1 and banderaConsumo == 1:
            modemwifi.post_var_ambientales(sensor_values,"THOMASA")
            #modemwifi.post_var_ambientales(sensor_amb_values,"AWS")
            #banderaAmb=0

        if banderaNivel == 1:
            modemwifi.post_var_nivel(sensor_nivel_values,"THOMASA")
            #modemwifi.post_var_nivel(sensor_nivel_values,"AWS")
            #banderaNivel=0
            
        if banderaAmb == 1:
            banderaAmb=0
            #modemwifi.post_var_ambientales(sensor_amb_values,"THOMASA")
            #modemwifi.post_var_ambientales(sensor_amb_values,"AWS")

        if banderaConsumo == 1:
            banderaConsumo=0
            #modemwifi.post_var_consumo(sensor_consumo_values,"THOMASA")
            #modemwifi.post_var_consumo(sensor_consumo_values,"AWS")

        if banderaNivel == 1:
            banderaNivel=0
            #modemwifi.post_var_nivel(sensor_nivel_values,"THOMASA")
            #modemwifi.post_var_nivel(sensor_nivel_values,"AWS")
    except:
        print('Error en la comunicacion enviar')
        return 1
    return 0


def sta_connection(connectionMode):
    global  SSID, PASSWORD
    global modemwifi, gprs

    if connectionMode == "WIFI":
        print("CONECTADO POR WIFI A LA RED ")
        print("SSID: "+SSID);
        condiciones_red = True

        while condiciones_red:
            intentos = 5
            try:
                modemwifi = system_wifi(SSID,PASSWORD)
                condiciones_red = False
            except:
                print("ERROR AL CONECTARSE A LA RED CON SSID: "+ SSID)

                condiciones_red = True
            if condiciones_red == True:
                for i in range(intentos,1,-1):
                    print("Esperando "+str(i)+" segundos para volver a intentar")
                    sleep(1)
                intentos = 5
        print("EL SISTEMA CONECTO CORRECTAMENTE A LA RED SSID: "+SSID)
        sleep(2)

def getDatosServer(server):
    global gprs, bandera_muestreo, modemwifi, CONNECTION_MODE

    if CONNECTION_MODE  == "WIFI":
        try:
            value = modemwifi.get_web(server)
        except:
            print("Error obteniendo datos del servidor "+server)
            return "error"
    else:
        try:
            code, value = gprs.get_web(server)
        except:
            print("Error obteniendo datos del servidor "+server)
            return "error"
        sleep(1)
    return value

def get_ServerVALUES():
    global trama
    global textoCompuerta,textoLamina, textoMuestreo, textoHora, t_envio, contador_envio
    global reiniciarGPRSIF
    print("Obteniendo Datos del servidor  ")

    textoCompuerta = getDatosServer("COMPUERTA")
    textoLamina    = getDatosServer("LAMINA")
    textoMuestreo  = getDatosServer("MUESTREO")
    textoHora      = getDatosServer("HORA")


    print('INFO COMPUERTA: '+ textoCompuerta)
    print('INFO LAMINA: '+textoLamina)
    print('INFO MUESTREO: '+textoMuestreo)
    print('INFO HORA: '+textoHora)
    
    condicion1 = "error" in textoCompuerta or "error" in textoLamina or "error" in textoMuestreo or "error" in textoHora
    condicion2 = textoCompuerta=='' or textoLamina=='' or textoMuestreo=='' or textoHora==''

    if  condicion1 or condicion2:
        reiniciarGPRSIF=1
        print("Error en la Recepcion de datos")
    else:
        #Guardamos en un arreglo los valoes que llegan del JSON del servidor
        arregloCompuerta = textoCompuerta.split(",")
        print(arregloCompuerta)
        print(arregloCompuerta[0])
        print(arregloCompuerta[1])
        print(arregloCompuerta[2])

        dic_compuerta_adm   = arregloCompuerta[0].split(":")
        dic_compuerta_sal   = arregloCompuerta[1].split(":")
        dic_estado_estacion = arregloCompuerta[2].split(":")

        compuerta_adm   = dic_compuerta_adm[1]
        compuerta_sal   = dic_compuerta_sal[1]
        estado_estacion = dic_estado_estacion[1]

        compuerta_adm   = compuerta_adm.replace('"',' ')
        compuerta_sal   = compuerta_sal.replace('"',' ')
        estado_estacion = estado_estacion.replace("}"," ")

        print("-------------------------------")
        print("Informacion Compuertas")
        print("-------------------------------")
        print(compuerta_adm)
        print("adm: "+compuerta_adm)
        print("-------------------------------")
        print("-------------------------------")
        print(compuerta_sal)
        print("adm: "+compuerta_sal)
        print("-------------------------------")
        print("-------------------------------")
        print(estado_estacion)
        print("adm: "+estado_estacion)
        print("-------------------------------")


        pos_admi = int(compuerta_adm)
        pos_sal  = int(compuerta_sal)
        
        print("prueba estado estacion: "+estado_estacion)
        
        if  "f" in estado_estacion:
            state   = '0'
        elif "t" in estado_estacion :
            state = '1'
        
        t_envio = int(textoMuestreo)

        fecha = textoHora[0:11]
        hora  = textoHora[12:20]

        hora = hora.replace(":","/")
        setPoint=textoLamina

        trama = "V/"+str(pos_admi)+"/"+str(pos_sal)+"/"+state+"/"+str(t_envio)+"/"+fecha+"/"+hora+"/"+setPoint+"/#"
        uart.write(trama)
        print(trama)
        print("Compuerta ADMIN:  "+ str(pos_admi))
        print("Compuerta SALIDA: "+ str(pos_sal))
        print("Estado Operativo: "+ state )

        print("SP LAMINA: " + setPoint)
        print("TIEMPO ENVIO: " + str(t_envio))
        print("FECHA SERVER : " + fecha)
        print("HORA SERVER : " + hora)

    

def run():
    global recibiendoDATOS, tiempoSONDEOWEB
    global tramaRx, sensor_amb_values, gprs, bandera_muestreo, sensor_consumo_values, sensor_nivel_values
    global CONNECTION_MODE
    global modemwifi
    global textoCompuerta,textoLamina, textoMuestreo, textoHora, t_envio, contador_envio
    global banderaConsumo, banderaNivel, banderaAmb
    global consumoIF, nivelIF, ambIF, reiniciarGPRSIF

    tiempoSONDEOWEB = TIAMPO_SONDEO_CONST
    recibiendoDATOS = True
    banderaConsumo, banderaNivel, banderaAmb, reiniciarGPRSIF = 0,0,0,0

    contador_envio = 10
    contador_reinicio = 1800

    bandera_muestreo = True
    uart.init(9600, bits=8, parity=None, stop=1, tx=18, rx=19)

    sta_connection(CONNECTION_MODE)

    consumoIF, nivelIF, ambIF, reiniciarGPRSIF = 0,0,0,0

    print('------------------------------------------------------')
    print('              PROGRAMA PRINCIPAL                      ')
    print('------------------------------------------------------')
    
#    get_ServerVALUES()

    while(True):

        if  not(recibiendoDATOS):
            tiempoSONDEOWEB -= 1
            if tiempoSONDEOWEB == 0:
                #pedir datos al servidor
                #get_ServerVALUES()
                tiempoSONDEOWEB = TIAMPO_SONDEO_CONST



        if reiniciarGPRSIF==1 and CONNECTION_MODE == "GPRS":
            print("Se reestablece la comunicacion GPRS")
            
            gprs.restartGPRS()
            sta_connection(CONNECTION_MODE)
            reiniciarGPRSIF = 0
            #Volver a solicitar datos al servidor
            contador_envio = 10

        if bandera_muestreo:
            print(sensor_values)
            #temp = bmp180.temperature
            #altitude = bmp180.altitude
            #print(temp, p, altitude)
            bandera_muestreo = False

        if ( uart.any() > 0 ):
            recibiendoDATOS = True
            aux = uart.readline()
            buffer = str(aux)
            tramaRx = buffer.split('/')
            print("----------------------------");
            print("      Trama Recibida        ");
            print(tramaRx)
            print("----------------------------");
            status_Rx = interpreta_trama(tramaRx)
            if status_Rx == 1:
                uart.write("S/1/#")
            
            recibiendoDATOS = False

            #Solicitar la informacion de los METODOS GEt
        '''
        status_gprs=gprs.get_StatusRed()
        
        if status_gprs == 1:
            sta_connection(CONNECTION_MODE)
        '''
        
        sleep(1)
        
        wdt.feed()


if __name__=='__main__':
    run()





