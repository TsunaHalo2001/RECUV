#ifndef CONFIG_H
#define CONFIG_H

//Constantes para conversion de unidades de tiempo
#define VALOR_S   1000
#define VALOR_10S 10
#define VALOR_M   60

//Valores de version y URL de JSON
#define VERSION_JSON 1
#define VARIABLES_API "https://raw.githubusercontent.com/TsunaHalo2001/RECUV/refs/heads/main/src/json/farallones/variables.json"

//Constantes de pines para el puerto serial
#define RX_1 3
#define TX_1 9

//Constantes de pines para I2C
#define SDA_1 36
#define SCL_1 37

//Constantes de tiempo para las tareas del sistema (en segundos)
#define TIEMPO_ENVIO_S         600
#define TIEMPO_ESPERA_WIFI     5
#define TIEMPO_SINCRONIZAR_UTC 1800
#define TIEMPO_MUESTRA         10

//Constantes de pines para SEN15901 y DAVIS6450
#define PIN_VIENTO          4
#define PIN_PRECIPITACION   6
#define PIN_VELETA          5
#define PIN_RADIACION_SOLAR 16

//Constantes para la sincronizacion de tiempo UTC
#define DESFASE_RTC      0
#define UTC_Bogota       18000
#define UTC_API          "http://worldtimeapi.org/api/timezone/America/Bogota"
#define UTC_HEADER_NAME  "User-Agent"
#define UTC_HEADER_VALUE "ESP32S3-Device/1.0"

//Constantes de calibracion SEN15901
#define SEN15901_MS_FACTOR_VIENTO 0.666667
#define SEN15901_MS_FACTOR_LLUVIA 0.2794
#define SEN15901_ADC_FACTOR       0.000805861

//Curvas de viento SEN15901
#define V_0_0_TOP   2.55
#define V_0_0       2.48
#define V_0_0_BOT   2.34

#define V_22_5_TOP  1.33
#define V_22_5      1.24
#define V_22_5_BOT  1.05

#define V_45_0_TOP  1.64
#define V_45_0      1.42
#define V_45_0_BOT  V_22_5_TOP

#define V_67_5_TOP  0.26
#define V_67_5      0.25
#define V_67_5_BOT  0.22

#define V_90_0_TOP  0.33
#define V_90_0      0.28
#define V_90_0_BOT  V_67_5_TOP

#define V_112_5_TOP V_67_5_BOT
#define V_112_5     0.2
#define V_112_5_BOT 0

#define V_135_0_TOP 0.64
#define V_135_0     0.55
#define V_135_0_BOT 0.46

#define V_157_5_TOP V_135_0_BOT
#define V_157_5     0.38
#define V_157_5_BOT V_90_0_TOP

#define V_180_0_TOP 1.05
#define V_180_0     0.87
#define V_180_0_BOT 0.8

#define V_202_5_TOP V_180_0_BOT
#define V_202_5     0.74
#define V_202_5_BOT V_135_0_TOP

#define V_225_0_TOP 2.08
#define V_225_0     1.96
#define V_225_0_BOT 1.91

#define V_247_5_TOP V_225_0_BOT
#define V_247_5     1.86
#define V_247_5_BOT V_45_0_TOP

#define V_270_0_TOP 3.3
#define V_270_0     3.03
#define V_270_0_BOT 2.93

#define V_292_5_TOP 2.72
#define V_292_5     2.62
#define V_292_5_BOT V_0_0_TOP

#define V_315_0_TOP V_270_0_BOT
#define V_315_0     2.83
#define V_315_0_BOT V_292_5_TOP

#define V_337_5_TOP V_0_0_BOT
#define V_337_5     2.2
#define V_337_5_BOT V_225_0_TOP

//Constantes de calibracion DAVIS6450
#define DAVIS6450_ADC_FACTOR 2.93255132

//Constantes de funcionamiento DHT11
#define PIN_DHT  17
#define TIPO_DHT DHT11

//Constantes de funcionamiento DS18B20
#define PIN_DS18B20 15

//Constantes de funcionamiento FC-28
#define PIN_FC28    7
#define FC28_FACTOR -0.02442002442002

//Constantes de funcionamiento ACS712
#define PIN_ACS712 1
#define ACS712_ADC_FACTOR SEN15901_ADC_FACTOR
#define ACS712_CORRIENTE 5
#define ACS712_SENSIBILIDAD 0.185
#define ACS712_VCC 3.3

//Constantes de funcionamiento HX711
#define PIN_LLUVIA_1 18
#define PIN_LLUVIA_2 8
#define PIN_DATO_PESO_1 9
#define PIN_DATO_PESO_2 11
#define PIN_RELOJ_PESO_1 3
#define PIN_RELOJ_PESO_2 10
#define PESO_1_OFFSET 0
#define PESO_2_OFFSET 0
#define PESO_1_SCALE 1
#define PESO_2_SCALE 1

#endif