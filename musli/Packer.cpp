// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#include "Packer.h"

namespace musli
{
//------------------------------------------------------------------------------
    Packer::Packer() {}

//------------------------------------------------------------------------------
    Packer::~Packer() {}

//------------------------------------------------------------------------------
    Packer& operator << (Packer& packer, bool value)
    {
        packer.pack_bool(value);
        return packer;
    }
    
//------------------------------------------------------------------------------
    Packer& operator << (Packer& packer, char value)
    {
        packer.pack_char(value);
        return packer;
    }
    
//------------------------------------------------------------------------------
    Packer& operator << (Packer& packer, unsigned char value)
    {
        packer.pack_unsigned_char(value);
        return packer;
    }
    
//------------------------------------------------------------------------------
    Packer& operator << (Packer& packer, short value)
    {
        packer.pack_short(value);
        return packer;
    }
    
//------------------------------------------------------------------------------
    Packer& operator << (Packer& packer, unsigned short value)
    {
        packer.pack_unsigned_short(value);
        return packer;
    }
    
//------------------------------------------------------------------------------
    Packer& operator << (Packer& packer, int value)
    {
        packer.pack_int(value);
        return packer;
    }
    
//------------------------------------------------------------------------------
    Packer& operator << (Packer& packer, unsigned int value)
    {
        packer.pack_unsigned_int(value);
        return packer;
    }
    
//------------------------------------------------------------------------------
    Packer& operator << (Packer& packer, long value)
    {
        packer.pack_long(value);
        return packer;
    }
    
//------------------------------------------------------------------------------
    Packer& operator << (Packer& packer, unsigned long value)
    {
        packer.pack_unsigned_long(value);
        return packer;
    }
    
//------------------------------------------------------------------------------
    Packer& operator << (Packer& packer, long long value)
    {
        packer.pack_long_long(value);
        return packer;
    }
    
//------------------------------------------------------------------------------
    Packer& operator << (Packer& packer, unsigned long long value)
    {
        packer.pack_unsigned_long_long(value);
        return packer;
    }
    
//------------------------------------------------------------------------------
    Packer& operator << (Packer& packer, float value)
    {
        packer.pack_float(value);
        return packer;
    }
    
//------------------------------------------------------------------------------
    Packer& operator << (Packer& packer, double value)
    {
        packer.pack_double(value);
        return packer;
    }
}

