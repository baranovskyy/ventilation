int ac_sensor_pin = 0;

int fan1_led_pin = 2;
int fan2_led_pin = 3;
int fan3_led_pin = 4;

int ac_sensor_threshold = 870; // out of smbd's ass

void setup()
{
  // put your setup code here, to run once:
   Serial.begin(57600);
   pinMode(fan1_led_pin, OUTPUT);
   pinMode(fan2_led_pin, OUTPUT);
   pinMode(fan3_led_pin, OUTPUT);
}

void loop() 
{
  int val = analogRead(ac_sensor_pin);
  if (val > ac_sensor_threshold)
  {
    digitalWrite(fan1_led_pin, LOW);
    digitalWrite(fan2_led_pin, LOW);
    digitalWrite(fan3_led_pin, LOW);
  }
  else
  {
    digitalWrite(fan1_led_pin, HIGH);
    digitalWrite(fan2_led_pin, HIGH);
    digitalWrite(fan3_led_pin, HIGH);
  }
  delay(100);
}

