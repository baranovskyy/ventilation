#include <Arduino.h>
#include "pins.h"
#include "SpeedSwitch.h"

int SpeedSwitch::Value()
{
   return _lastValue;
}

bool SpeedSwitch::Poll()
{
   int newValue = ReadSpeedSwitch();
   unsigned long newTime = millis();
   
   if(newValue == _lastValue)
   {
      if(GetThresholdForSpeed(newValue) <= newTime - _lastTime)
      {
         // emit event
         return true;
      }
   }
   else
   {  // value has changed, store it
      _lastValue = newValue;
      _lastTime = newTime;
   }
   return false;
}

int SpeedSwitch::GetThresholdForSpeed(int value)
{
   // as switch crosses zero when you move it, need to wait for longer
   if(value == 0) return 500; // half a second before switch off
   return 20;
}

int SpeedSwitch::ReadSpeedSwitch()
{
  static const int SpeedSwitchThreshold1 = 330;
  static const int SpeedSwitchThreshold2 = 550;
  static const int SpeedSwitchThreshold3 = 770;
   
  int rawValue = analogRead(Pin::SpeedSwitch);
  if(rawValue < SpeedSwitchThreshold1)
    return 0;
  if(rawValue < SpeedSwitchThreshold2)
    return 1;
  if(rawValue < SpeedSwitchThreshold3)
    return 2;
  return 3;
}
