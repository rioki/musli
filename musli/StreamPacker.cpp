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
    template <typename Type>
    inline void pack_pod(std::ostream& os, Type value)
    {
        os.write(reinterpret_cast<const char*>(&value), sizeof(Type));
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack_bool(bool value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack_char(char value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack_unsigned_char(unsigned char value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack_short(short value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack_unsigned_short(unsigned short value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack_int(int value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack_unsigned_int(unsigned int value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack_long(long value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack_unsigned_long(unsigned long value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack_long_long(long long value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack_unsigned_long_long(unsigned long long value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack_float(float value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack_double(double value)
    {
        pack_pod(stream, value);
    }
}
