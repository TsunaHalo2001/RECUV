import machine

class SensorACS712:
  def __init__(self, pin):
    self.pin = pin

  def obtener_corriente(self):
    return None