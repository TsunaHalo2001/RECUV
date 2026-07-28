#include "DS18B20.h"

DS18B20::DS18B20 (int _pin) : pin(_pin), one_wire(_pin), ds18b20(&this->one_wire), bandera_exito(true) {
  this->ds18b20.begin();
  if (!this->ds18b20.getAddress(this->direccion, 0)) Serial.println("Unable to find address for Device 0");
  this->ds18b20.setResolution(this->direccion, 9);
}

DS18B20::~DS18B20() = default;

[[nodiscard]] int DS18B20::obtener_pin() const { return this->pin; }
[[nodiscard]] OneWire DS18B20::obtener_one_wire() const { return this->one_wire; }
[[nodiscard]] DallasTemperature DS18B20::obtener_ds18b20() const { return this->ds18b20; }
[[nodiscard]] const DeviceAddress& DS18B20::obtener_direccion() const { return this->direccion; }
[[nodiscard]] bool DS18B20::obtener_bandera_exito() const { return this->bandera_exito; }

void DS18B20::definir_pin(const int _pin) { this->pin = _pin; }
void DS18B20::definir_one_wire(const OneWire _one_wire) { this->one_wire = _one_wire; }
void DS18B20::definir_ds18b20(const DallasTemperature _ds18b20) { this->ds18b20 = _ds18b20; }
void DS18B20::definir_direccion(const DeviceAddress _direccion) { memcpy(this->direccion, _direccion, 8); }
void DS18B20::definir_bandera_exito(const bool _bandera_exito) { this->bandera_exito = _bandera_exito; }

float DS18B20::pedir_temperatura() {
  this->ds18b20.requestTemperatures();
  delay(100);
  float temperatura = this->ds18b20.getTempC(this->direccion);
  if (temperatura < -120) this->bandera_exito = false;
  else this->bandera_exito = true;
  return temperatura;
}