#ifndef _STATS_H_
#define _STATS_H_

namespace Stats
{
  int Min(int * data, int len);
}
class MinBuffer
{
private:
  const static int Size = 32;
  int _data[Size];
  bool _ready;
  int _pos;
public:
  MinBuffer();
  bool Add(int value);
  int Min();
  bool IsReady();
};

class LayeredMinBuffer
{
private:
  const static int Size = 32;  
  MinBuffer _buffers[Size];
public:
  void Add(int value);
  bool IsReady();
  int Min();
};


#endif
