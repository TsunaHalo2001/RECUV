import machine

class SensorDS18B20:
  def __init__(self, pin):
    self.pin = pin

  def obtener_temperatura(self):
    return None