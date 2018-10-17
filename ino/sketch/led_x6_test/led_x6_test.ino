
int MotionLED = 0;
int HumidityLED = 1;

int Fan1LED = 2;
int Fan2LED = 4;
int Fan3LED = 3;

int Fan1Relay = 5;
int Fan2Relay = 6;
int Fan3Relay = 7;


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
}

// the loop function runs over and over again forever
void loop() {
  delay(10000);
  digitalWrite(MotionLED, HIGH);
  delay(delayMs);                     
  digitalWrite(MotionLED, LOW);
  digitalWrite(HumidityLED, HIGH);
  delay(delayMs);                     
  digitalWrite(HumidityLED, LOW);
  digitalWrite(Fan1LED, HIGH);
  digitalWrite(Fan1Relay, HIGH);
  delay(delayMs);                     
  digitalWrite(Fan2LED, HIGH);
  digitalWrite(Fan2Relay, HIGH);
  delay(delayMs);                     
  digitalWrite(Fan3LED, HIGH);
  digitalWrite(Fan3Relay, HIGH);
  delay(delayMs*2);        
  
  digitalWrite(Fan1LED, LOW);  
  digitalWrite(Fan1Relay, LOW);
  delay(delayMs);
  digitalWrite(Fan2LED, LOW);
  digitalWrite(Fan2Relay, LOW);
  delay(delayMs);      
  digitalWrite(Fan3LED, LOW);
  digitalWrite(Fan3Relay, LOW);
}
