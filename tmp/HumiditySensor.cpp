#include <DHT.h>


struct HumiditySample
{
  // relative humidity in 0.1 percent
  // value of 1000 corresponds to 100%
  int Humidity;
  // relative humidity in 0.1 degrees
  // value of 200 corresponds to 20 degrees
  int Temperature;
};

class HumiditySensor
{
   DHT & _dht;
   
   float _temp;
public:
   float Temperature()
   {
      return _temp;
   }

   HumiditySensor(DHT& dht)
   {
      // DHT 22 (AM2302) sensor
      _dht = dht;
   }

   void Begin()
   {
      _dht.begin();
   }
   
   // Warning - very slow operation
   bool Poll()
   {
      float humidity = _dht.readHumidity();
      // Read temperature as Celsius
      float temp = _dht.readTemperature();
      if (isnan(humidity) || isnan(temp))
      {
         return false;
      }
      
      _temp = temp;
     // relative humidity in 0.1 percent
     // value of 1000 corresponds to 100%
      _humidity = int(humidity * 10 + 0.5);
   }
}