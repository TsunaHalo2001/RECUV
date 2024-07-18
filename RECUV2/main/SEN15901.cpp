#include "SEN15901.h"

// Inicialización del equipo SEN15901
SEN15901::SEN15901(uint8_t pinViento, uint8_t pinLluvia, uint8_t pinVientoDir) : pinViento(pinViento), pinLluvia(pinLluvia), pinVientoDir(pinVientoDir){
  pinMode(pinViento, INPUT_PULLUP); //Inicialización del pin para Anemometro
  pinMode(pinLluvia, INPUT_PULLUP); //Inicialización del pin para Pluviometro
  windCont = 0;
  rainCont = 0;
  timeWindSpeed = 5;

  //La veleta tiene 8 switches, pero solo dos pueden cerrarse al mismo tiempo, así que 
  //es posible tener 16 posiciones. Cada posición tiene una resistencia diferente,
  //resultando en diferentes valores ADC. Los valores ADC esperados son definidos
  //de manera experimental dependiendo de las conexiones, la plataforma y quizas el uso de un Divisor de voltaje.
  /*DirADCValues[WMK_ANGLE_0_0] = SFE_WMK_ADC_ANGLE_0_0;
  DirADCValues[WMK_ANGLE_22_5] = SFE_WMK_ADC_ANGLE_22_5;
  DirADCValues[WMK_ANGLE_45_0] = SFE_WMK_ADC_ANGLE_45_0;
  DirADCValues[WMK_ANGLE_67_5] = SFE_WMK_ADC_ANGLE_67_5;
  DirADCValues[WMK_ANGLE_90_0] = SFE_WMK_ADC_ANGLE_90_0;
  DirADCValues[WMK_ANGLE_112_5] = SFE_WMK_ADC_ANGLE_112_5;
  DirADCValues[WMK_ANGLE_135_0] = SFE_WMK_ADC_ANGLE_135_0;
  DirADCValues[WMK_ANGLE_157_5] = SFE_WMK_ADC_ANGLE_157_5;
  DirADCValues[WMK_ANGLE_180_0] = SFE_WMK_ADC_ANGLE_180_0;
  DirADCValues[WMK_ANGLE_202_5] = SFE_WMK_ADC_ANGLE_202_5;
  DirADCValues[WMK_ANGLE_225_0] = SFE_WMK_ADC_ANGLE_225_0;
  DirADCValues[WMK_ANGLE_247_5] = SFE_WMK_ADC_ANGLE_247_5;
  DirADCValues[WMK_ANGLE_270_0] = SFE_WMK_ADC_ANGLE_270_0;
  DirADCValues[WMK_ANGLE_292_5] = SFE_WMK_ADC_ANGLE_292_5;
  DirADCValues[WMK_ANGLE_315_0] = SFE_WMK_ADC_ANGLE_315_0;
  DirADCValues[WMK_ANGLE_337_5] = SFE_WMK_ADC_ANGLE_337_5;*/
}

SEN15901::~SEN15901() {
}

//Precipitación
float SEN15901::getPrecipitacion() {
  double preci_temp = rainCont * 0.2794; // Conversión para precipitación
  return preci_temp;
}

//Velocidad del viento
float SEN15901::getVelViento() {
  float windSpeed = windCont * 2.4 / timeWindSpeed;  // Conversión para velocidad del viento
  return windSpeed;
}

float SEN15901::getDirViento() {
  int adc_value = analogRead(pinVientoDir);

  float v_dir = adc_value * 0.0048876;

  if (v_dir >= (V_ANGLE_0_0 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 0;
  if (v_dir >= (V_ANGLE_22_5 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 22.5;
  if (v_dir >= (V_ANGLE_45_0 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 45;
  if (v_dir >= (V_ANGLE_67_5 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 67.5;
  if (v_dir >= (V_ANGLE_90_0 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 90;
  if (v_dir >= (V_ANGLE_112_5 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 112.5;
  if (v_dir >= (V_ANGLE_135_0 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 135;
  if (v_dir >= (V_ANGLE_157_5 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 157.5;
  if (v_dir >= (V_ANGLE_180_0 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 180;
  if (v_dir >= (V_ANGLE_202_5 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 202.5;
  if (v_dir >= (V_ANGLE_225_0 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 225;
  if (v_dir >= (V_ANGLE_247_5 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 247.5;
  if (v_dir >= (V_ANGLE_270_0 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 270;
  if (v_dir >= (V_ANGLE_292_5 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 292.5;
  if (v_dir >= (V_ANGLE_315_0 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 315;
  if (v_dir >= (V_ANGLE_337_5 - V_RESOLUTION) && v_dir < (V_ANGLE_0_0 + V_RESOLUTION)) return 337.5;
}
/**
#define V_ANGLE_0_0 3.8
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
**/

//////////////Dirección del viento//////////////
///Ajusta el valor de ADC esperado para la veletea según la resolución ADC. 
///resolutionBits se refiere a la resolución de los bits del ADC.
/*void SEN15901::setADCResolutionBits(uint8_t resolutionBits)
{
    for(uint8_t i = 0; i < WMK_NUM_ANGLES; i++)
    {
        int8_t bitShift = (SFE_WMK_ADC_RESOLUTION) - resolutionBits;

        if(bitShift > 0)
        {
            DirADCValues[i] >>= bitShift;
        }
        else if(bitShift < 0)
        {
            DirADCValues[i] <<= -bitShift;
        }
    }
}

float SEN15901::getDirViento()
{
    // Medida de la salida del divisor de tensión
    uint16_t rawADC = analogRead(_windDirectionPin);

    //Utiliza el bucle for para comparar el dato del pin con todas las direcciones posibles y encontrar la que esté más cercana
    // para las medidas, se hace una simple busqueda lineal. closestDifference es
    // inicializada al valor máximo asignado de 16 bits (2^15 - 1 = 32,767)
    int16_t closestDifference = 32767;
    uint8_t closestIndex = 0;
    for (uint8_t i = 0; i < WMK_NUM_ANGLES; i++)
    {
        // Calcular la diferencia entre el valor del ADC para esta dirección menos el valor que medimos con el divisor de tensión
        int16_t adcDifference = DirADCValues[i] - rawADC;

        // Sólo nos importa la magnitud de la diferencia
        adcDifference = abs(adcDifference);

        // Revisar si la diferencia es menor a la medida máxima poaible del ADC de 16 bits
        if (adcDifference < closestDifference)
        {
            // Entonces esta resistencia es la más cercana, así que actualice el dato en ClosestDifference y en i(index del bucle for) 
            closestDifference = adcDifference;
            closestIndex = i;
        }
    }
}*/