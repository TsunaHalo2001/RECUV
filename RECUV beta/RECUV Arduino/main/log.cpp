#include "log.h"

void mensaje_log(const String& etiqueta, const String& mensaje) {
  Serial.println("[ " + etiqueta + " ] [ " + mensaje + " ]");
}