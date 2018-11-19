#ifndef _STATS_H_
#define _STATS_H_

namespace Stats
{
  short Min(short * data, int len);
}
class MinBuffer
{
private:
  const static int Size = 16;
  short _data[Size];
  bool _ready;
  int _pos;
public:
  MinBuffer();
  bool Add(short value);
  short Min();
  bool IsReady();
};

class LayeredMinBuffer
{
private:
  const static int Size = 3;  
  MinBuffer _buffers[Size];
public:
  bool Add(short value);
  bool IsReady();
  short Min();
};


#endif
