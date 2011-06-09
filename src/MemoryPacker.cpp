// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#include "MemoryPacker.h"

#include <algorithm>
#include <iterator>

namespace musli
{
//------------------------------------------------------------------------------
    MemoryPacker::MemoryPacker(std::vector<char>& b)
    : buffer(b) {}

//------------------------------------------------------------------------------
    MemoryPacker::~MemoryPacker() {}

//------------------------------------------------------------------------------
    void MemoryPacker::write(const char* data, unsigned int size)
    {
        std::copy(data, data + size, std::back_inserter(buffer));
    }
}
