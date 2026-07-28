#ifndef DS18B20_H
#define DS18B20_H

#include <OneWire.h>
#include <DallasTemperature.h>
#include <cstring>

class DS18B20 {
  protected:
    int pin;
    OneWire one_wire;
    DallasTemperature ds18b20;
    DeviceAddress direccion;
    bool bandera_exito;

  public:
    DS18B20(int);
    ~DS18B20();

    int obtener_pin() const;
    OneWire obtener_one_wire() const;
    DallasTemperature obtener_ds18b20() const;
    const DeviceAddress& obtener_direccion() const;
    bool obtener_bandera_exito() const;

    void definir_pin(const int);
    void definir_one_wire(const OneWire);
    void definir_ds18b20(const DallasTemperature);
    void definir_direccion(const DeviceAddress);
    void definir_bandera_exito(const bool);

    float pedir_temperatura();
};

#endif