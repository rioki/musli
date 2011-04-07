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
    void StreamPacker::pack(bool value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack(char value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack(unsigned char value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack(short value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack(unsigned short value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack(int value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack(unsigned int value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack(long value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack(unsigned long value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack(long long value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack(unsigned long long value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack(float value)
    {
        pack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamPacker::pack(double value)
    {
        pack_pod(stream, value);
    }

//------------------------------------------------------------------------------
    void StreamPacker::pack(const std::string&  value)
    {
        unsigned int size = value.size();
        pack(size);
        if (size != 0)
        {
            stream.write(&value[0], size);
        }
    }
}
