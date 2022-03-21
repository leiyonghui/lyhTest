#pragma once
#include <algorithm>
#include <vector>

struct SWritev
{
	char* buff;
	int len;

	SWritev() :buff(nullptr), len(0) {}

	void clear() { buff = nullptr, len = 0; }
};

class RingBuff
{
    using uint32 = unsigned int;

    RingBuff(const RingBuff&) = delete;
    RingBuff& operator=(const RingBuff&) = delete;

public:

    explicit RingBuff(uint32 capacity);

    ~RingBuff();

    void write(char* buff, uint32 len);

    void read(char* buff, uint32 len);

	SWritev* writerv();

    bool empty() { return _size > 0; }

    uint32 writableBytes() { return _capacity - _size; };

    uint32 readableBytes() { return _size; }

    uint32 size() { return _size; }

    uint32 capacity() { return _capacity; }

private:
    void ensure(uint32 capacity);

    uint32 _capacity;
    uint32 _front;
    uint32 _end;
    uint32 _size;
    char* _buff;
	SWritev* _writerv;
};