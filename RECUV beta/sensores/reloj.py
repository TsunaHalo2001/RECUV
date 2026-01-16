import machine

class SensorReloj:
  def __init__(self):
    try:
      self.rtc = machine.RTC()
    except Exception as e:
      self.rtc = None
      print(e)

  def obtener_tiempo(self):
    if self.rtc == None:
      return None
    else:
      return self.rtc.datetime()