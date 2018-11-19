class SpeedSwitch
{
private:
   int _lastValue;
   unsigned long _lastTime;
   int GetThresholdForSpeed(int value);
   int ReadSpeedSwitch();
public:
   int Value();
   bool Poll();
};
   
