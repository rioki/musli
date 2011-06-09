// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#include "StreamUnpacker.h"

#include <iostream>

namespace musli
{
//------------------------------------------------------------------------------
    StreamUnpacker::StreamUnpacker(std::istream& s)
    : stream(s) {}

//------------------------------------------------------------------------------
    StreamUnpacker::~StreamUnpacker() {}

//------------------------------------------------------------------------------
    void StreamUnpacker::read(char* data, unsigned int size)
    {
        stream.read(data, size);
    }
}
