# Información de Mantenimiento para recuperacion de las estaciones K18 y Tocota

## Requisitos

`Thonny IDE`

`Arduino IDE`

Drivers de conexion al modulo `CP2102` de Silicon Labs

## Contextualizacion

### Contenido del repositorio

#### `RECUV Niebla`

Explicacion del uso de `Serial2` para la comunicacion entre `RECUV Niebla` y `RECUV 2`

Explicacion de la estructura interna de `RECUV 2` adicional al contenido de `RECUV 1`

Explicacion de la trampa de niebla y su funcionamiento

Explicacion de montaje interno de la caja de `RECUV Niebla`

Explicacion de montaje y utilizacion del protocolo ISP

#### `RECUV 2`

Explicacion de problemas del `Arduino Mega 2560`

## Guia de Mantenimiento

##### Paso 1, revision del modulo BMP180 y conexion al modem

Justo al momento de conexion la `ESP32` muestra las caracteristicas de conexion al modem (direccion IP).
Si, al desconectar y conectar al computador la `ESP32` todo el sistema funciona con normalidad (El envio se realiza cada 10 minutos aproximadamente), en la consola de `Thonny IDE` se vera si el `BMP180` se conecto correctamente.

##### Paso 2, revision del proceso de recepcion de datos

Al cabo de 10 minutos en la consola de `Thonny IDE` se vera la informacion enviada por el `Arduino Mega 2560` y su proceso de recepcion por parte de la `ESP32`, si durante la recepcion no hubo un error fatal, o a pesar del error, al final se recibio la informacion correctamente. Se debe esperar al proceso de envio al servidor.

##### Paso 3, revision del envio de datos al servidor

Despues de la recepcion de datos, se debe esperar a que la `ESP32` envie los datos al servidor, si el envio se realiza correctamente, se vera en la consola de `Thonny IDE` el mensaje de confirmacion del envio, el codigo de envio exitoso es `200`, si el codigo es diferente, se debe revisar la conexion a internet de la `ESP32` y el servidor.

##### Paso 4, revision de la conexion a internet

Se debe probar la conexion Wi-Fi de la `ESP32`, si el modem tiene filtro MAC, debe agregar la MAC de su telefono a traves de la conexion del celular del profesor o comprobarlo con el celular de el, asegurese que la conexion no tenga conexion MAC aleatoria.

##### Comprobacion final

Si durante 10 minutos no hubo error y se retomo el proceso de comunicacion, la falla en el `Arduino Mega 2560` tiende a bloquearlo y se necesita el cambio por las placas.

Si el problema de conexion se presenta en el modem, hay que revisar la estabilidad de conexion ya sea por culpa de la SIM si tiene datos o no, o si el modem presenta el funcionamiento correcto.

Si alguno de los envios (deben ser 3) retorna un codigo de error diferente a `200`, hay problemas en el envio de los datos pero el codigo indica que el servidor se esta comunicando.

## Guia de adiciones de direcciones de envio de datos

Debido a que el profesor quiere agregar mas servidores para el envio, las direcciones estan en el archivo `system_communication.py` de la ESP32 en las siguientes lineas:

```python
NUEVO_SERVER   = 'http://3.234.78.150:80/sigla/php/post.php'
SERVER_THOMASA1 = 'http://45.5.164.43:80/2022/sigla/php/post_k18.php'
SERVER_THOMASA2 = 'http://45.5.164.43:80/2022/sigla/php/post_k18.php'
CLIMATE = 'http://climate.gismodel.click/2022/sigla/php/post_k18.php'
```

Para agregar un nuevo servidor, se debe agregar una nueva variable con el nombre del servidor y la direccion del servidor, por ejemplo:

```python
NUEVO_SERVIDOR = 'http://direccion_del_nuevo_servidor.com/ruta/del/archivo.php'
```

Usualmente la ruta del archivo es `/sigla/php/post_k18.php`, pero puede variar dependiendo del servidor, asi que se corrobora con el profesor.

Luego de agregar la linea con la direccion del servidor se debe implementar en las funciones de comunicacion, en el mismo archivo `system_communication.py`, en la clase `system_wifi` en la funcion `post_var_ambientales`(solo esa debido a que la trama de datos es unica):

```python
def post_var_ambientales(self, value_data, server):  
        
        if server=='AWS':
            self.URL_POST=NUEVO_SERVER
        elif server=='THOMASA1':
            self.URL_POST=SERVER_THOMASA1
        elif server=='THOMASA2':
            self.URL_POST=SERVER_THOMASA2
        elif server=='CLIMATE':
            self.URL_POST=CLIMATE
```

Se debe agregar una nueva condicion `elif` con el nombre del servidor y la variable que se creo anteriormente, por ejemplo:

```python
elif server=='NUEVO_SERVIDOR':
    self.URL_POST=NUEVO_SERVIDOR
```

Luego en el archivo `main.py` se debe agregar el uso de la nueva variable en la funcion `enviarWifi`:

```python
def enviarWifi():
    global gprs, bandera_muestreo, modemwifi, CONNECTION_MODE
    global banderaConsumo, banderaNivel, banderaAmb
    try:
        if banderaAmb == 1 and banderaConsumo == 1:
            modemwifi.post_var_ambientales(sensor_values,"THOMASA1")
            modemwifi.post_var_ambientales(sensor_values,"THOMASA2")
            modemwifi.post_var_ambientales(sensor_values,"CLIMATE")
```

Se debe agregar una nueva linea con el nombre del servidor y la variable que se creo anteriormente, por ejemplo:

```python
            modemwifi.post_var_ambientales(sensor_values,"NUEVO_SERVIDOR")
```