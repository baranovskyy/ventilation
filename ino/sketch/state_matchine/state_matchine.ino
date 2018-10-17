const int ledPin = 13;   // select the pin for the LED
const int presencePin = 8;   // select the pin for the presence switch
const int potPin = 0;    // select the input pin for the potentiometer

int led_value = 0;

typedef enum
{
   WAIT_BEFORE_OFF,
   OFF,
   WAIT_BEFORE_TRICKLE,
   TRICKLE,
   WAIT_BEFORE_BOOST,
   BOOST,
   WAIT_AFTER_BOOST,
} State;

State _state;
unsigned long _cycle;
unsigned long _wait_timer;
unsigned long _boost_timer;
int  _humidity;
bool _presence;

const unsigned long cycle_ms = 500;
const unsigned long presence_confirmation_time_ms = 3 * 1000L ;
const unsigned long absence_confirmation_time_ms = 3 * 1000L;
const unsigned long humidity_confirmation_time_ms = 3 * 1000L;
const unsigned long min_boost_time_ms = 5 * 1000L;
const unsigned long max_boost_time_ms = 20 * 1000L;

const int high_humidity = 85;
const int low_humidity = 70;

void setup() 
{
  _cycle = 0;
  _state = State::OFF;
  _wait_timer = 0;
  _boost_timer = 0;
  _humidity = 0;
  _presence = false;
  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT
  pinMode(presencePin, INPUT);
  Serial.begin(115200);
}

void loop() 
{
   _humidity = read_humidity();
   _presence = read_presence();
   State new_state = evaluate_transition();
   Serial.println(all_to_string(new_state));
   
   if(new_state != _state)
      transit_to(new_state);
   else
      increment_timers(cycle_ms);
   delay(cycle_ms);
   _cycle++;
}

void transit_to(State new_state)
{
   if(is_wait(new_state))
      _wait_timer = 0;

   if(new_state == BOOST && _state == WAIT_BEFORE_BOOST)
      _boost_timer = 0;

   // TODO: perform relay actions
   switch(new_state)
   {
      case OFF:
         Serial.println("Speed=0");
         break;
      case TRICKLE:
         Serial.println("Speed=1");
         break;
      case BOOST:
         Serial.println("Speed=3");
         break;
   }
   
   _state = new_state;
}

void increment_timers(int ms)
{
   if(is_wait(_state))
      _wait_timer += ms;
   if(is_boost(_state))
      _boost_timer += ms;
}

bool is_wait(State state)
{
  switch(_state)
  {
     case WAIT_BEFORE_OFF:
     case WAIT_BEFORE_TRICKLE:
     case WAIT_BEFORE_BOOST:
     case WAIT_AFTER_BOOST:
      return true;
     default:
        return false;
  }
}

bool is_boost(State state)
{
  switch(state)
  {
     case BOOST:
     case WAIT_AFTER_BOOST:
      return true;
     default:
        return false;
  }
}

State evaluate_transition()
{
  switch(_state)
  {
     case WAIT_BEFORE_OFF:
        if(_humidity >= high_humidity)
           return WAIT_BEFORE_BOOST;
        if(_presence)
           return TRICKLE;
        if(_wait_timer >= absence_confirmation_time_ms)
           return OFF;
        break;
     case OFF:
        if(_humidity >= high_humidity)
           return WAIT_BEFORE_BOOST;
        if(_presence)
           return WAIT_BEFORE_TRICKLE;
        break;
     case WAIT_BEFORE_TRICKLE:
        if(_humidity >= high_humidity)
           return WAIT_BEFORE_BOOST;
        if(!_presence)
           return OFF;
       if(_wait_timer >= presence_confirmation_time_ms)
         return TRICKLE;
       break;
     case TRICKLE:
        if(_humidity >= high_humidity)
           return WAIT_BEFORE_BOOST;
        if(!_presence)
           return WAIT_BEFORE_OFF;
        break;    
     case WAIT_BEFORE_BOOST:
        if(_humidity <= low_humidity)
           return WAIT_BEFORE_OFF;
       if(_wait_timer >= humidity_confirmation_time_ms)
           return BOOST;
       break;
     case BOOST:
        if(_humidity <= low_humidity)
           return WAIT_AFTER_BOOST;
       if(_boost_timer >= max_boost_time_ms)
         return WAIT_BEFORE_OFF;
       break;
    case WAIT_AFTER_BOOST:
        if(_humidity >= high_humidity)
           return BOOST;
      if(_wait_timer >= min_boost_time_ms)
         return WAIT_BEFORE_OFF;
       if(_boost_timer >= max_boost_time_ms)
         return WAIT_BEFORE_OFF;
        break;
  }
  return _state;
}

String all_to_string(State new_state)
{
  String s = String(_cycle);
  s += " State:";
  s += state_to_string(_state);
  s += " Humidity:";
  s += _humidity;
  s += " Presence:";
  s += _presence;
  if(is_wait(_state))
  {
     s += " WaitTimer:";
     s += _wait_timer;
  }
  if(is_boost(_state))
  {
     s += " BoostTimer:";
     s += _boost_timer;
  }
  if(_state != new_state)
  {
     s += " NewState:";
     s += state_to_string(new_state);
  }
  return s;
}

const char * state_to_string(State state)
{
  switch(state)
  {
     case WAIT_BEFORE_OFF: 
        return "WAIT_BEFORE_OFF";
     case OFF:
        return "OFF";
     case WAIT_BEFORE_TRICKLE: 
        return "WAIT_BEFORE_TRICKLE";
     case TRICKLE: 
        return "TRICKLE";
     case WAIT_BEFORE_BOOST: 
        return "WAIT_BEFORE_BOOST";
     case BOOST: 
        return "BOOST";
     case WAIT_AFTER_BOOST: 
        return "WAIT_AFTER_BOOST";
     default: 
        return "#UNKNOWN#";
  }
}

int read_humidity()
{
  return 100l * analogRead(potPin) / 1023l;
}

bool read_presence()
{
  return digitalRead(presencePin) == HIGH;
}

