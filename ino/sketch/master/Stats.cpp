#include "Stats.h"

short Stats::Min(short * data, int len)
{
   short m = 9999;
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

bool MinBuffer::Add(short value)
{
  _data[_pos] = value;
  if(++_pos < Size)
    return false;
  _pos = 0;
  _ready = true;
  return true;
}

short MinBuffer::Min()
{
  return Stats::Min(_data, Size);
}

bool MinBuffer::IsReady()
{
  return _ready;
}

bool LayeredMinBuffer::Add(short value)
{
  for(int i=0; i<Size; ++i)
  {
    if(!_buffers[i].Add(value))
       break;
    value = _buffers[i].Min();
  }
  return IsReady();
}

bool LayeredMinBuffer::IsReady()
{
  for(int i=0; i<Size; ++i)
     if(_buffers[i].IsReady())
        return true;
  return false;
}

short LayeredMinBuffer::Min()
{
  for(int i=Size-1; i>=0; --i)
     if(_buffers[i].IsReady())
        return _buffers[i].Min();
  return 0;
}    
