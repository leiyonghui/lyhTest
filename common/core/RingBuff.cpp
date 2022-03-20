#include "RingBuff.h"
#include <string.h>
#include <assert.h>

using uint32 = unsigned int;

RingBuff::RingBuff(uint32 capacity) :_capacity(capacity), _front(0), _end(0), _size(0),_buff(new char[_capacity]) {
    
}

RingBuff::~RingBuff()
{
    delete[] _buff;
}

void RingBuff::write(char* buff, uint32 len)
{
    assert(len > 0);
    ensure(_size + len);

    if (_end >= _front /*|| (_end == _front && !_size)*/) //ensure保证有空间
    {
        uint32 count = _capacity - _end;
        if (len <= count) 
        {
            memcpy(_buff + _end, buff, len);
            _end += len;
        }
        else
        {
            uint32 remain = len - count;
            memcpy(_buff + _end, buff, count);
            memcpy(_buff, buff + count, remain);
            _end = remain;
        }
    }
    else
    {
        memcpy(_buff + _end, buff, len);
        _end += len;
    }
    _size += len;
}

void RingBuff::read(char* buff, uint32 len)
{
    assert(_size >= len && len);

    if (_end > _front)
    {
#ifdef _DEBUG
        assert(_end - _front >= len);
#endif // DEBUG
        memcpy(buff, _buff + _front, len);
        _front += len;
    }
    else
    {
        uint32 count = _capacity - _front;
        if (count >= len) 
        {
            memcpy(buff, _buff + _front, len);
            _front += len;
        }
        else
        {
            uint32 remain = len - count;
            memcpy(buff, _buff + _front, count);
            memcpy(buff + count, _buff, remain);
            _front = remain;
        }
    }
    _size -= len;
}

char* RingBuff::back()
{
    if (_end > _front || (_end == _front && !_size))
    {
        return _end == _capacity ? nullptr : _buff + _end;
    }
}

char* RingBuff::front()
{
    return nullptr;
}

uint32 RingBuff::backBytes()
{
    return uint32();
}

uint32 RingBuff::frontBytes()
{
    return uint32();
}

void RingBuff::ensure(uint32 capacity)
{
    if (_capacity >= capacity)
        return;

    uint32 newcapacity = _capacity;
    while (newcapacity < capacity)
        newcapacity = (newcapacity << 1) + 1;

    char* tembuff = new char[newcapacity];
    if (_end <= _front && _size) 
    {
        auto len = _capacity - _front;
#ifdef _DEBUG
        assert(_size == len + _end);
#endif // DEBUG

        memcpy(tembuff, _buff + _front, len);
        memcpy(tembuff + len, _buff, _end);
    }
    else
    {
#ifdef _DEBUG
        assert(_size == _end - _front);
#endif // DEBUG
        memcpy(tembuff, _buff + _front, _size);
    }
    delete[] _buff;
    _buff = tembuff;
    _capacity = newcapacity;
    _front = 0;
    _end = _size;
}
