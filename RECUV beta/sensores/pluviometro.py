import machine

class SensorPluviometro:
  def __init__(self, pin):
    self.pin = pin

  def obtener_precipitacion(self):
    return None