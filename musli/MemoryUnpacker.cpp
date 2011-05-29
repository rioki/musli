// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#include "MemoryUnpacker.h"

#include <algorithm>
#include <iterator>

namespace musli
{
//------------------------------------------------------------------------------
    MemoryUnpacker::MemoryUnpacker(const std::vector<char>& b)
    : buffer(b) 
    {
        read_pos = buffer.begin();
    }

//------------------------------------------------------------------------------
    MemoryUnpacker::~MemoryUnpacker() {}

//------------------------------------------------------------------------------
    void MemoryUnpacker::read(char* data, unsigned int size)
    {
        std::vector<char>::const_iterator start = read_pos;
        std::vector<char>::const_iterator end = read_pos + size;
        std::copy(start, end, data);
        read_pos = end;
    }
}
