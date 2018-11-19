#include "pins.h"
#include "Stats.h"
#include "SpeedSwitch.h"
#include <DHT.h>

const int PresenceSensorThreshold = 870;

// Two DHT 22 (AM2302) sensors 
DHT dht1(Pin::DHT1, DHT22);
DHT dht2(Pin::DHT2, DHT22);

void initRelay()
{
  pinMode(Pin::RelayTrickle, OUTPUT);
  pinMode(Pin::RelayNormal, OUTPUT);
  pinMode(Pin::RelayBoost, OUTPUT);  
  // make sure it's switched off
  digitalWrite(Pin::RelayTrickle, HIGH);
  digitalWrite(Pin::RelayNormal, HIGH);
  digitalWrite(Pin::RelayBoost, HIGH);      
}

void writeToAllLeds(byte val)
{
  digitalWrite(Pin::HumidityLED, val);
  digitalWrite(Pin::MotionLED, val);
  digitalWrite(Pin::Fan1LED, val);  
  digitalWrite(Pin::Fan2LED, val);
  digitalWrite(Pin::Fan3LED, val);  
}

void setup() 
{
  Serial.begin(57600); // needs to be done before LED init as it uses same leds...
  
  pinMode(Pin::MotionLED, OUTPUT);
  pinMode(Pin::HumidityLED, OUTPUT);
  pinMode(Pin::Fan1LED, OUTPUT);
  pinMode(Pin::Fan2LED, OUTPUT);
  pinMode(Pin::Fan3LED, OUTPUT);

  // LED blink
  writeToAllLeds(HIGH);

  initRelay();

  
  delay(500);
  writeToAllLeds(LOW);
}

// 0 off 1-3 speed
void SetFanSpeed(int speed) 
{
  Serial.print("SetFanSpeed");
  Serial.println(speed);
  
  digitalWrite(Pin::Fan1LED, speed > 0 ? HIGH : LOW);
  digitalWrite(Pin::Fan2LED, speed > 1 ? HIGH : LOW);
  digitalWrite(Pin::Fan3LED, speed > 2 ? HIGH : LOW);
  // relay output is inverted
  digitalWrite(Pin::RelayTrickle, speed == 1 ? LOW : HIGH);
  digitalWrite(Pin::RelayNormal,  speed == 2 ? LOW : HIGH);
  digitalWrite(Pin::RelayBoost,   speed == 3 ? LOW : HIGH);      
}

LayeredMinBuffer buffer_h1;

void loop() 
{
  float h1 = dht1.readHumidity();
  // Read temperature as Celsius
  float t1 = dht1.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h1) || isnan(t1)) 
  {
    Serial.println("Failed to read from DHT sensor 1");
    h1 = 0;
    t1 = 0;
  }

  if(h1 > 0)
  {
    short value = h1*10 + 0.5;
    Serial.print(value);
    
    // update rolling minimum

    if(buffer_h1.Add(value))
    {
      Serial.print(" | Buffer1 is ready: Min=");
      Serial.println(buffer_h1.Min());
    }
    else
    {
      Serial.println(" | Buffer1 is not ready");
    }
  }
  delay(2500);
}
