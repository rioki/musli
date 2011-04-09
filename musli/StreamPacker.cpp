// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#include "StreamPacker.h"

#include <iostream>

namespace musli
{
//------------------------------------------------------------------------------
    StreamPacker::StreamPacker(std::ostream& s)
    : stream(s) {}

//------------------------------------------------------------------------------
    StreamPacker::~StreamPacker() {}

//------------------------------------------------------------------------------
    void StreamPacker::write(const char* data, unsigned int size)
    {
        stream.write(data, size);
    }
}
