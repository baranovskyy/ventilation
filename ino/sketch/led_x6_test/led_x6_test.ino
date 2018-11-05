
int MotionLED = 0;
int HumidityLED = 1;

int Fan1LED = 2;
int Fan2LED = 4;
int Fan3LED = 3;

int Fan1Relay = 5;
int Fan2Relay = 6;
int Fan3Relay = 7;

int SpeedSwitchPin = 1;

int SpeedSwitchThreshold1 = 330;
int SpeedSwitchThreshold2 = 550;
int SpeedSwitchThreshold3 = 770;

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

int delayMs = 3000;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
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
}

int SwitchValue = 0;
int SwitchValueT0 = 0; // most recent reading
int SwitchValueT1 = 0;
int SwitchValueT2 = 0;

// the loop function runs over and over again forever
void loop() 
{
  SwitchValueT2 = SwitchValueT1;
  SwitchValueT1 = SwitchValueT0;
  SwitchValueT0 = ConvertSwitchReading(analogRead(SpeedSwitchPin));
  if(SwitchValueT0 == SwitchValueT1 && SwitchValueT0 == SwitchValueT2)
  {
    int prevSwitchValue = SwitchValue;
    SwitchValue = SwitchValueT0;
     if(prevSwitchValue != SwitchValue) // change
        SpeedSwitchChanged(SwitchValue);
  }
  delay(30);
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
