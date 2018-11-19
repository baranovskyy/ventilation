#ifndef _PINS_H_
#define _PINS_H_

namespace Pin
{
   const int MotionLED = 12;
   const int HumidityLED = 13;
   const int Fan1LED = 2;
   const int Fan2LED = 4; // lol
   const int Fan3LED = 3;

   const int RelayTrickle = 5;
   const int RelayNormal = 6;
   const int RelayBoost = 7;

   // Analog
   const int PresenceSensor = 0;
   const int SpeedSwitch = 1;
   
   const int DHT1 = 10;
   const int DHT2 = 11;
}

#endif
