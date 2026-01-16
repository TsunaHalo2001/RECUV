import machine

class SensorDAVIS6450:
  def __init__(self, pin):
    self.pin = pin

  def obtener_radiacion_solar(self):
    return None