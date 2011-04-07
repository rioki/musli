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
    inline void unpack_pod(std::istream& is, Type& value)
    {
        is.read(reinterpret_cast<char*>(&value), sizeof(Type));
    }
        
//------------------------------------------------------------------------------
    void StreamUnpacker::unpack(bool& value)
    {
        unpack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamUnpacker::unpack(char& value)
    {
        unpack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamUnpacker::unpack(unsigned char& value)
    {
        unpack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamUnpacker::unpack(short& value)
    {
        unpack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamUnpacker::unpack(unsigned short& value)
    {
        unpack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamUnpacker::unpack(int& value)
    {
        unpack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamUnpacker::unpack(unsigned int& value)
    {
        unpack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamUnpacker::unpack(long& value)
    {
        unpack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamUnpacker::unpack(unsigned long& value)
    {
        unpack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamUnpacker::unpack(long long& value)
    {
        unpack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamUnpacker::unpack(unsigned long long& value)
    {
        unpack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamUnpacker::unpack(float& value)
    {
        unpack_pod(stream, value);
    }
    
//------------------------------------------------------------------------------
    void StreamUnpacker::unpack(double& value)
    {
        unpack_pod(stream, value);
    }

//------------------------------------------------------------------------------
    void StreamUnpacker::unpack(std::string&  value)
    {
        unsigned int size = 0;
        unpack(size);
        if (size != 0)
        {
            char buff[size];
            stream.read(buff, size);
            value = std::string(buff, size);
        }
        else
        {
            value = std::string();
        }
    }
}
