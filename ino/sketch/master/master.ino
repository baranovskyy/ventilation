#include <DHT.h>

#include "pins.h"

const int PresenceSensorThreshold = 870;
const int DHTTYPE = DHT22;   // DHT 22  (AM2302)

const int SpeedSwitchThreshold1 = 330;
const int SpeedSwitchThreshold2 = 550;
const int SpeedSwitchThreshold3 = 770;

DHT dht1(Pin::DHT1, DHTTYPE);
DHT dht2(Pin::DHT2, DHTTYPE);
 
void setup() 
{
  pinMode(Pin::MotionLED, OUTPUT);
  pinMode(Pin::HumidityLED, OUTPUT);
  pinMode(Pin::Fan1LED, OUTPUT);
  pinMode(Pin::Fan2LED, OUTPUT);
  pinMode(Pin::Fan3LED, OUTPUT);

  pinMode(Pin::RelayTrickle, OUTPUT);
  pinMode(Pin::RelayNormal, OUTPUT);
  pinMode(Pin::RelayBoost, OUTPUT);  

  digitalWrite(Pin::RelayTrickle, HIGH);
  digitalWrite(Pin::RelayNormal, HIGH);
  digitalWrite(Pin::RelayBoost, HIGH);      

  digitalWrite(Pin::HumidityLED, LOW);
  digitalWrite(Pin::MotionLED, LOW);
  digitalWrite(Pin::Fan1LED, LOW);  
  digitalWrite(Pin::Fan2LED, LOW);  
  digitalWrite(Pin::Fan3LED, LOW);  

  Serial.begin(57600); 
  dht1.begin();
  dht2.begin();
}

int ConvertSwitchReading(int rawValue)
{
  if(rawValue < SpeedSwitchThreshold1)
    return 0;
  if(rawValue < SpeedSwitchThreshold2)
    return 1;
  if(rawValue < SpeedSwitchThreshold3)
    return 2;
  return 3;
}

void SetFanSpeed0()
{
  digitalWrite(Pin::Fan1LED, LOW);
  digitalWrite(Pin::Fan2LED, LOW);
  digitalWrite(Pin::Fan3LED, LOW);
  
  digitalWrite(Pin::RelayTrickle, HIGH);
  digitalWrite(Pin::RelayNormal, HIGH);
  digitalWrite(Pin::RelayBoost, HIGH);      
}

void SetFanSpeed1()
{
  digitalWrite(Pin::Fan1LED, HIGH);  
  digitalWrite(Pin::Fan2LED, LOW);  
  digitalWrite(Pin::Fan3LED, LOW);
  
  digitalWrite(Pin::RelayTrickle, LOW);
  digitalWrite(Pin::RelayNormal, HIGH);
  digitalWrite(Pin::RelayBoost, HIGH);      
}

void SetFanSpeed2()
{
  digitalWrite(Pin::Fan1LED, HIGH);  
  digitalWrite(Pin::Fan2LED, HIGH);  
  digitalWrite(Pin::Fan3LED, LOW);
  
  digitalWrite(Pin::RelayTrickle, HIGH);
  digitalWrite(Pin::RelayNormal, LOW);
  digitalWrite(Pin::RelayBoost, HIGH);      
}


void SetFanSpeed3()
{
  digitalWrite(Pin::Fan1LED, HIGH);  
  digitalWrite(Pin::Fan2LED, HIGH);  
  digitalWrite(Pin::Fan3LED, HIGH);
  
  digitalWrite(Pin::RelayTrickle, HIGH);
  digitalWrite(Pin::RelayNormal, HIGH);
  digitalWrite(Pin::RelayBoost, LOW);      
}

void SpeedSwitchChanged(int switchValue)
{
   switch(switchValue)
   {
    case 1:
       SetFanSpeed1();
       break;
    case 2:
       SetFanSpeed2();
       break;
    case 3:
       SetFanSpeed3();
       break;
    default:
       SetFanSpeed0();
       break;
   }
}
 
void loop() 
{
  // Wait a few seconds between measurements.
  delay(2000);
 
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h1 = dht1.readHumidity();
  // Read temperature as Celsius
  float t1 = dht1.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h1) || isnan(t1)) {
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
  if (isnan(h2) || isnan(t2)) {
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
