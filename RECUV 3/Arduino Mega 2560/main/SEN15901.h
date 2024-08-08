#ifndef SEN15901_H
#define SEN15901_H
#include <Arduino.h>
#include <stdint.h>

///////Basado en la librería de Sparkfun: https://github.com/sparkfun/SparkFun_Weather_Meter_Kit_Arduino_Library.git

// Enumeración que define las posiciones posibles de la veleta
enum DirPosValues
{
    ANGLE_0_0 = 0,
    ANGLE_22_5,
    ANGLE_45_0,
    ANGLE_67_5,
    ANGLE_90_0,
    ANGLE_112_5,
    ANGLE_135_0,
    ANGLE_157_5,
    ANGLE_180_0,
    ANGLE_202_5,
    ANGLE_225_0,
    ANGLE_247_5,
    ANGLE_270_0,
    ANGLE_292_5,
    ANGLE_315_0,
    ANGLE_337_5,
    WMK_NUM_ANGLES //Esto es 360° y tambien 0°(para usar WMK_ANGLE_0_0 = 0 solamente como dato de inicialización)
};
// Angulo entre la posición de la veleta de viento (360 / 16 = 22.5)
#define SFE_WIND_VANE_DEGREES_PER_INDEX (360.0 / WMK_NUM_ANGLES) //DegPerIndex
//Definición de los datos esperado en el ADC y su resolución según la posición de la veleta
#define V_ANGLE_0_0 3.45
#define V_ANGLE_22_5 2
#define V_ANGLE_45_0 2.3
#define V_ANGLE_67_5 0.4
#define V_ANGLE_90_0 0.5
#define V_ANGLE_112_5 0.3
#define V_ANGLE_135_0 0.9
#define V_ANGLE_157_5 0.6
#define V_ANGLE_180_0 1.4
#define V_ANGLE_202_5 1.2
#define V_ANGLE_225_0 3.1
#define V_ANGLE_247_5 2.9
#define V_ANGLE_270_0 4.6
#define V_ANGLE_292_5 4.0
#define V_ANGLE_315_0 4.3
#define V_ANGLE_337_5 3.4
#define V_RESOLUTION 0.05 //10

class SEN15901 {
  public:
    uint8_t pinViento;
    uint8_t pinLluvia;
    uint8_t pinVientoDir;
    //uint16_t DirADCValues[WMK_NUM_ANGLES];     //Valores ADC de la veleta, arreglo de 16 posiciones
    volatile int windCont;
    volatile int rainCont;
    float timeWindSpeed;

    //static void setADCResolutionBits(uint8_t resolutionBits);// Escalado de resolución ADC
    
    SEN15901(uint8_t, uint8_t, uint8_t);//Inicialización
    
    ~SEN15901(); //LLamador de funciones de colección

    //Data collection
    float getPrecipitacion();
    float getVelViento();
    float getDirViento();
};

#endif // SEN15901_H