#include "DHT.h"
 
#define DHT1PIN 8     // what pin we're connected to
#define DHT2PIN 9     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

DHT dht1(DHT1PIN, DHTTYPE);
DHT dht2(DHT2PIN, DHTTYPE);
 
void setup() {
  Serial.begin(57600); 
  dht1.begin();
  dht2.begin();
}
 
void loop() {
  // Wait a few seconds between measurements.
  delay(2000);
 
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h1 = dht1.readHumidity();
  // Read temperature as Celsius
  float t1 = dht1.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h1) || isnan(t1)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h2 = dht2.readHumidity();
  // Read temperature as Celsius
  float t2 = dht2.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h2) || isnan(t2)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
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
