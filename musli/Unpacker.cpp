// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#include "Unpacker.h"

namespace musli
{
//------------------------------------------------------------------------------
    Unpacker::Unpacker() {}

//------------------------------------------------------------------------------
    Unpacker::~Unpacker() {}

//------------------------------------------------------------------------------
    Unpacker& operator >> (Unpacker& unpacker, bool& value)
    {
        value = unpacker.unpack_bool();
        return unpacker;
    }
    
//------------------------------------------------------------------------------
    Unpacker& operator >> (Unpacker& unpacker, char& value)
    {
        value = unpacker.unpack_char();
        return unpacker;
    }
    
//------------------------------------------------------------------------------
    Unpacker& operator >> (Unpacker& unpacker, unsigned char& value)
    {
        value = unpacker.unpack_unsigned_char();
        return unpacker;
    }
    
//------------------------------------------------------------------------------
    Unpacker& operator >> (Unpacker& unpacker, short& value)
    {
        value = unpacker.unpack_short();
        return unpacker;
    }
    
//------------------------------------------------------------------------------
    Unpacker& operator >> (Unpacker& unpacker, unsigned short& value)
    {
        value = unpacker.unpack_unsigned_short();
        return unpacker;
    }
    
//------------------------------------------------------------------------------
    Unpacker& operator >> (Unpacker& unpacker, int& value)
    {
        value = unpacker.unpack_int();
        return unpacker;
    }
    
//------------------------------------------------------------------------------
    Unpacker& operator >> (Unpacker& unpacker, unsigned int& value)
    {
        value = unpacker.unpack_unsigned_int();
        return unpacker;
    }
    
//------------------------------------------------------------------------------
    Unpacker& operator >> (Unpacker& unpacker, long& value)
    {
        value = unpacker.unpack_long();
        return unpacker;
    }
    
//------------------------------------------------------------------------------
    Unpacker& operator >> (Unpacker& unpacker, unsigned long& value)
    {
        value = unpacker.unpack_unsigned_long();
        return unpacker;
    }
    
    
//------------------------------------------------------------------------------
    Unpacker& operator >> (Unpacker& unpacker, long long& value)
    {
        value = unpacker.unpack_long_long();
        return unpacker;
    }
    

//------------------------------------------------------------------------------
    Unpacker& operator >> (Unpacker& unpacker, unsigned long long& value)
    {
        value = unpacker.unpack_unsigned_long_long();
        return unpacker;
    }
    
//------------------------------------------------------------------------------
    Unpacker& operator >> (Unpacker& unpacker, float& value)
    {
        value = unpacker.unpack_float();
        return unpacker;
    }
    
//------------------------------------------------------------------------------
    Unpacker& operator >> (Unpacker& unpacker, double& value)
    {
        value = unpacker.unpack_double();
        return unpacker;
    }
}

