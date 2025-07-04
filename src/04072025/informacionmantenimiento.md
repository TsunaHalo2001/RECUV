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

##### Paso 1, revision de el modulo BMP180

Si, al desconectar y conectar al computador la `ESP32` todo el sistema funciona con normalidad (El envio se realiza cada 10 minutos aproximadamente), en la consola de `Thonny IDE` se vera si el `BMP180` se conecto correctamente (o no) pero se vera si el programa continua, al cabo de 10 minutos en la consola de `Thonny IDE` se vera la informacion enviada por el `Arduino Mega 2560` y su proceso de envio al servidor. El problema se debe al `Arduino Mega 2560`.

##### Paso 2, revision del proceso de recepcion de datos

Si, al cabo de 10 minutos en la consola de `Thonny IDE` se vera la informacion enviada por el `Arduino Mega 2560` y su proceso de recepcion por parte de la `ESP32`, si durante la recepcion no hubo un error fatal, o a pesar del error, al final se recibio la informacion correctamente. Se debe esperar al proceso de envio al servidor.