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
    template <typename Type>
    inline Type unpack_pod(std::istream& is)
    {
        Type value;
        is.read(reinterpret_cast<char*>(&value), sizeof(Type));
        return value;
    }
        
//------------------------------------------------------------------------------
    bool StreamUnpacker::unpack_bool()
    {
        return unpack_pod<bool>(stream);
    }
    
//------------------------------------------------------------------------------
    char StreamUnpacker::unpack_char()
    {
        return unpack_pod<char>(stream);
    }
    
//------------------------------------------------------------------------------
    unsigned char StreamUnpacker::unpack_unsigned_char()
    {
        return unpack_pod<unsigned char>(stream);
    }
    
//------------------------------------------------------------------------------
    short StreamUnpacker::unpack_short()
    {
        return unpack_pod<short>(stream);
    }
    
//------------------------------------------------------------------------------
    unsigned short StreamUnpacker::unpack_unsigned_short()
    {
        return unpack_pod<unsigned short>(stream);
    }
    
//------------------------------------------------------------------------------
    int StreamUnpacker::unpack_int()
    {
        return unpack_pod<int>(stream);
    }
    
//------------------------------------------------------------------------------
    unsigned int StreamUnpacker::unpack_unsigned_int()
    {
        return unpack_pod<unsigned int>(stream);
    }
    
//------------------------------------------------------------------------------
    long StreamUnpacker::unpack_long()
    {
        return unpack_pod<long>(stream);
    }
    
//------------------------------------------------------------------------------
    unsigned long StreamUnpacker::unpack_unsigned_long()
    {
        return unpack_pod<unsigned long>(stream);
    }
    
//------------------------------------------------------------------------------
    long long StreamUnpacker::unpack_long_long()
    {
        return unpack_pod<long long>(stream);
    }
    
//------------------------------------------------------------------------------
    unsigned long long StreamUnpacker::unpack_unsigned_long_long()
    {
        return unpack_pod<unsigned long long>(stream);
    }
    
//------------------------------------------------------------------------------
    float StreamUnpacker::unpack_float()
    {
        return unpack_pod<float>(stream);
    }
    
//------------------------------------------------------------------------------
    double StreamUnpacker::unpack_double()
    {
        return unpack_pod<double>(stream);
    }
}
