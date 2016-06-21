#include <Task.h>

class WittyCloudLDRTask : public Task
{
public:
  typedef void(*action)();
  WittyCloudLDRTask(action function, uint8_t ldrPin, int * ldrValue, uint32_t timeInterval) :
    Task(timeInterval),
    ldrValue(ldrValue),
    ldrPin(ldrPin),
    _callback(function)
  {
  };

private:
  // put member variables here that are scoped to this object
  // const means can't change other than in constructor
  const action _callback;
  const uint8_t ldrPin;
  int * ldrValue;

  virtual bool OnStart()
  {
    // Assign the Pins properly
    pinMode(ldrPin, INPUT);
    return true;
  }

  virtual void OnUpdate(uint32_t deltaTime)
  {
    *ldrValue = analogRead(ldrPin);
    _callback();
  }
};
