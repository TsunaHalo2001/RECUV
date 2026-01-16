import machine

class SensorFC28:
  def __init__(self, pin):
    self.pin = pin

  def obtener_humedad(self):
    return None