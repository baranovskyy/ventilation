#include "DHT.h"


const int MotionLED = 0;
const int HumidityLED = 1;

const int Fan1LED = 2;
const int Fan2LED = 4; // lol
const int Fan3LED = 3;

const int Fan1Relay = 5;
const int Fan2Relay = 6;
const int Fan3Relay = 7;

const int PresenceSensorPin = 0;
const int PresenceSensorThreshold = 870;

const int SpeedSwitchPin = 1;
 
const int DHT1PIN = 10;
const int DHT2PIN = 11;
const int DHTTYPE = DHT22;   // DHT 22  (AM2302)

const int SpeedSwitchThreshold1 = 330;
const int SpeedSwitchThreshold2 = 550;
const int SpeedSwitchThreshold3 = 770;

DHT dht1(DHT1PIN, DHTTYPE);
DHT dht2(DHT2PIN, DHTTYPE);
 
void setup() 
{
  pinMode(MotionLED, OUTPUT);
  pinMode(HumidityLED, OUTPUT);
  pinMode(Fan1LED, OUTPUT);
  pinMode(Fan2LED, OUTPUT);
  pinMode(Fan3LED, OUTPUT);

  pinMode(Fan1Relay, OUTPUT);
  pinMode(Fan2Relay, OUTPUT);
  pinMode(Fan3Relay, OUTPUT);  

  digitalWrite(Fan1Relay, HIGH);
  digitalWrite(Fan2Relay, HIGH);
  digitalWrite(Fan3Relay, HIGH);      

  digitalWrite(HumidityLED, LOW);
  digitalWrite(MotionLED, LOW);
  digitalWrite(Fan1LED, LOW);  
  digitalWrite(Fan2LED, LOW);  
  digitalWrite(Fan3LED, LOW);  

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
  digitalWrite(Fan1LED, LOW);  
  digitalWrite(Fan2LED, LOW);  
  digitalWrite(Fan3LED, LOW);
  
  digitalWrite(Fan1Relay, HIGH);
  digitalWrite(Fan2Relay, HIGH);
  digitalWrite(Fan3Relay, HIGH);      
}

void SetFanSpeed1()
{
  digitalWrite(Fan1LED, HIGH);  
  digitalWrite(Fan2LED, LOW);  
  digitalWrite(Fan3LED, LOW);
  
  digitalWrite(Fan1Relay, LOW);
  digitalWrite(Fan2Relay, HIGH);
  digitalWrite(Fan3Relay, HIGH);      
}

void SetFanSpeed2()
{
  digitalWrite(Fan1LED, HIGH);  
  digitalWrite(Fan2LED, HIGH);  
  digitalWrite(Fan3LED, LOW);
  
  digitalWrite(Fan1Relay, HIGH);
  digitalWrite(Fan2Relay, LOW);
  digitalWrite(Fan3Relay, HIGH);      
}


void SetFanSpeed3()
{
  digitalWrite(Fan1LED, HIGH);  
  digitalWrite(Fan2LED, HIGH);  
  digitalWrite(Fan3LED, HIGH);
  
  digitalWrite(Fan1Relay, HIGH);
  digitalWrite(Fan2Relay, HIGH);
  digitalWrite(Fan3Relay, LOW);      
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
