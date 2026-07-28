#ifndef LOG_H
#define LOG_H

#include <Arduino.h>;

void mensaje_log(const String& etiqueta, const String& mensaje);

#define LOG_HTTP(mensaje)     mensaje_log("HTTP", mensaje)
#define LOG_WIFI(mensaje)     mensaje_log("WIFI", mensaje)
#define LOG_ERROR(mensaje)    mensaje_log("ERROR", mensaje)
#define LOG_ADVER(mensaje)  mensaje_log("ADVER", mensaje)
#define LOG_INFO(mensaje)     mensaje_log("INFO", mensaje)
#define LOG_JSON(mensaje) mensaje_log("JSON", mensaje)

#endif