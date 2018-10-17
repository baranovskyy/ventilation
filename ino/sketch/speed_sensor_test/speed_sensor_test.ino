int speed_sensor_pin = 5;

int threshold1 = 330;
int threshold2 = 550;
int threshold3 = 770;

void setup()
{
   Serial.begin(57600);
}

int convert_speed(int rawValue)
{
  if(rawValue < threshold1)
    return 0;
  if(rawValue < threshold2)
    return 1;
  if(rawValue < threshold3)
    return 2;
  return 3;
}

void loop() 
{
  int val = analogRead(speed_sensor_pin);

  int fan_speed = convert_speed(val);
  
  Serial.print(val);
  Serial.print("->");
  Serial.println(fan_speed);
  delay(300);
}

