#include "Stats.h"

int Stats::Min(int * data, int len)
{
   int m = 9999;
   for(int i = 0; i<len; ++i)
      if(data[i] < m)
         m = data[i];
   return m;
}

MinBuffer::MinBuffer()
{
  _pos = 0;
  _ready = false;
}

bool MinBuffer::Add(int value)
{
  _data[_pos++] = value;
  if(_pos < Size)
    return false;
  _pos = 0;
  _ready = true;
  return true;
}

int MinBuffer::Min()
{
  return Stats::Min(_data, Size);
}

bool MinBuffer::IsReady()
{
  return _ready;
}

void LayeredMinBuffer::Add(int value)
{
  for(int i=0; i<Size; ++i)
  {
    if(!_buffers[i].Add(value))
       return;
    value = _buffers[i].Min();
  }
}

bool LayeredMinBuffer::IsReady()
{
  for(int i=0; i<Size; ++i)
     if(_buffers[i].IsReady())
        return true;
  return false;
}

int LayeredMinBuffer::Min()
{
  for(int i=Size-1; i>0; --i)
     if(_buffers[i].IsReady())
        return _buffers[i].Min();
  return 0;
}    
