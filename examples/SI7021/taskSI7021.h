#include <Task.h>
#include <Wire.h>
#include <SI7021.h>

SI7021 si;
si7021_thc temphum;

class SI7021Task : public Task
{
public:
  typedef void(*action)();
  SI7021Task(action function, uint8_t pinSDA, uint8_t pinSCL, float * temperature, int * humidity, uint32_t timeInterval) :
    Task(timeInterval),
    temperature(temperature),
    humidity(humidity),
    si7021PinSDA(pinSDA),
    si7021PinSCL(pinSCL),
    _callback(function)
  {
  };

private:
  // put member variables here that are scoped to this object
  // const means can't change other than in constructor
  const action _callback;
  const uint8_t si7021PinSCL;
  const uint8_t si7021PinSDA;
  float * temperature;
  int * humidity;

  virtual bool OnStart()
  {
    si.begin(si7021PinSDA,si7021PinSCL);
    if(si.sensorExists()) {
      // This starts the task interval
      return true;
    } else {
      // This stops the task immediately
      return false;
    }
  }

  virtual void OnUpdate(uint32_t deltaTime)
  {
    if(si.sensorExists()) {
      temphum = si.getTempAndRH();
      *temperature = (float) temphum.celsiusHundredths / 100.0;
      *humidity = (int) temphum.humidityPercent;
      _callback();
    }
  }
};
