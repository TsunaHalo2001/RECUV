#include <Arduino.h>
#include <stdint.h>

class Potencia {
  public:
    uint8_t pinVoltaje;
    uint8_t pinCorriente;

    float m;
    float b;
    float sensibilidad;

    Potencia(uint8_t, uint8_t);
    ~Potencia();
    float getConsumoV();
    float getConsumoC();
};