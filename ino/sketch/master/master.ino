#include <DHT.h>

#include "pins.h"
#include "Stats.h"
#include "SpeedSwitch.h"

const int PresenceSensorThreshold = 870;
const int DHTTYPE = DHT22;   

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

  dht1.begin();
  dht2.begin();
  
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

struct DhtSample
{
  // relative humidity in 0.1 percent
  // value of 1000 corresponds to 100%
  int Humidity;
  // relative humidity in 0.1 degrees
  // value of 200 corresponds to 20 degrees
  int Temperature;
};

void loop() 
{
  SetFanSpeed(0);

  // Wait a few seconds between measurements.
  delay(1000);

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

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

  float h2 = dht2.readHumidity();
  // Read temperature as Celsius
  float t2 = dht2.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h2) || isnan(t2)) 
  {
    Serial.println("Failed to read from DHT sensor 2");
    h2 = 0;
    t2 = 0;
  }

  Serial.print(h1, 1);
  Serial.print("%");
  Serial.print(t1, 1);
  Serial.print("   ");
  Serial.print(h2, 1);
  Serial.print("%");
  Serial.print(t2, 1);
  Serial.println();
}
