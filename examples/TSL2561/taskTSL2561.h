#include <Wire.h>
#include <Task.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

/*************************************************/
/* Settings for Light Sensor TSL2561 Measurements*/
/*************************************************/
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

class TSL2561Task : public Task
{
public:
  typedef void(*action)();
  TSL2561Task(action function, uint8_t pinSDA, uint8_t pinSCL, int * lux, uint32_t timeInterval) :
    Task(timeInterval),
    lux(lux),
    tsl2561PinSDA(pinSDA),
    tsl2561PinSCL(pinSCL),
    _callback(function)
  {
  };

private:
  // put member variables here that are scoped to this object
  // const means can't change other than in constructor
  const action _callback;
  const uint8_t tsl2561PinSCL;
  const uint8_t tsl2561PinSDA;
  int * lux;

  virtual bool OnStart()
  {
    Wire.begin(tsl2561PinSDA, tsl2561PinSCL);

    tsl.begin();
    tsl.enableAutoRange(true);
    tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);
    return true;
  }

  virtual void OnUpdate(uint32_t deltaTime)
  {
    sensors_event_t event;
    tsl.getEvent(&event);
    if (event.light) {
      *lux = (int) event.light;
      _callback();
    }
  }
};
