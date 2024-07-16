#include "Ambiental.h"

Ambiental::Ambiental(DHT dht, DAVIS6450 davis6450, FC28 fc28, DallasTemperature ds18b20, SFE_BMP180 bmp180, SEN15901 sen15901) : dht(dht), davis6450(davis6450), fc28(fc28), ds18b20(ds18b20), bmp180(bmp180), sen15901(sen15901) {
  cont_prom = 0;

  //Humedad del aire
  h = 0.0;
  t = 0.0;
  h_prom = 0.0;
  t_prom = 0.0;

  //Anemometro
  wind_Speed = 0.0;
  wind_Speed_Temp = 0.0;
  wind_Speed_Prom = 0.0;
  windTime = 0;

  //Pluviometro
  preci_actual = 0;
  preci_min = 0;
  rainTime = 0;

  //Radiacion solar
  radiacion_valor = 0.0;
  radiacion_valor_prom = 0.0;

  //Humedad del suelo
  humedad_valor = 0.0;
  humedad_valor_prom = 0.0;

  //Temperatura del suelo
  temp_suelo = 0.0;
  temp_suelo_prom = 0.0;

  //Presion atmosferica
  T = 0;
  P = 0;
  T_prom = 0.0;
  P_prom = 0.0;
}

Ambiental::~Ambiental() {
}

void Ambiental::actualizarHumAire() {
  h = dht.readHumidity();
  if (isnan(h)) h = 0;
  h_prom += h;

  t = dht.readTemperature();
  if (isnan(t)) t = 0;
  t_prom += t;
}

void Ambiental::actualizarVelViento() {

  wind_Speed = sen15901.getVelViento();
  wind_Speed_Temp += wind_Speed;
  Serial.println("WST"+String(wind_Speed_Temp));
  sen15901.windCont = 0;
}

void Ambiental::actualizarPreci() {
  preci_actual = sen15901.getPrecipitacion();
  Serial.println("PRECI_ACT"+String(preci_actual));
  sen15901.rainCont = 0;
}

void Ambiental::actualizarRad() {
  radiacion_valor = davis6450.getRadiacion();
  radiacion_valor_prom += radiacion_valor;
  Serial.print("RAD: "+String(radiacion_valor));
}

void Ambiental::actualizarHumSuelo() {
  humedad_valor = fc28.getHum();
  humedad_valor_prom += humedad_valor;
}

void Ambiental::actualizarTempSuelo() {
  ds18b20.requestTemperatures();

  temp_suelo = ds18b20.getTempCByIndex(0);
  temp_suelo_prom += temp_suelo;
}

void Ambiental::actualizarPres() {
  char status;

  status = bmp180.startTemperature();//Inicio de lectura de temperatura

  if (status != 0)
  {
    delay(status); //Pausa para que finalice la lectura
    status = bmp180.getTemperature(T); //Obtener la temperatura
    T_prom += T;
    if (status != 0)
    {
      status = bmp180.startPressure(3); //Inicio lectura de presión
      if (status != 0)
      {
        delay(status);//Pausa para que finalice la lectura
        status = bmp180.getPressure(P, T); //Obtenemos la presión
        P_prom += (float)(P);
        if (status != 0)
        {
        }
      }
    }
  }
}

void Ambiental::actualizarAmbiental() {
  actualizarHumAire();
  actualizarVelViento();
  actualizarPreci();
  actualizarRad();
  actualizarHumSuelo();
  actualizarTempSuelo();
  actualizarPres();
  cont_prom++;
  Serial.println(cont_prom);
}

//150 es banda
void Ambiental::rainCounterInterrupt() {
  if (millis() - rainTime > 150) {
    sen15901.rainCont++;
    rainTime = millis();
    Serial.println(rainTime);
  }
}

void Ambiental::windCounterInterrupt() {
  if (millis() - windTime > 150) {
    sen15901.windCont++;
    windTime = millis();
    Serial.println(windTime);
  }
}