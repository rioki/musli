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
    Packer& Packer::operator << (bool value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(bool));
        return *this;
    }

//------------------------------------------------------------------------------
    Packer& Packer::operator << (char value)    
    {
        write(reinterpret_cast<const char*>(&value), sizeof(char));
        return *this;
    }
    
//------------------------------------------------------------------------------
    Packer& Packer::operator << (unsigned char value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(unsigned char));
        return *this;
    }

//------------------------------------------------------------------------------
    Packer& Packer::operator << (short value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(short));
        return *this;
    }

//------------------------------------------------------------------------------
    Packer& Packer::operator << (unsigned short value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(unsigned short));
        return *this;
    }

//------------------------------------------------------------------------------
    Packer& Packer::operator << (int value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(int));
        return *this;
    }

//------------------------------------------------------------------------------
    Packer& Packer::operator << (unsigned int  value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(unsigned int));
        return *this;
    }

//------------------------------------------------------------------------------
    Packer& Packer::operator << (long value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(long));
        return *this;
    }

//------------------------------------------------------------------------------
    Packer& Packer::operator << (unsigned long value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(unsigned long));
        return *this;
    }

//------------------------------------------------------------------------------
    Packer& Packer::operator << (long long value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(long long));
        return *this;
    }

//------------------------------------------------------------------------------
    Packer& Packer::operator << (unsigned long long value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(unsigned long long));
        return *this;
    }

//------------------------------------------------------------------------------
    Packer& Packer::operator << (float value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(float));
        return *this;
    }

//------------------------------------------------------------------------------
    Packer& Packer::operator << (double value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(double));
        return *this;
    }

//------------------------------------------------------------------------------
    Packer& Packer::operator << (const std::string& value)
    {
        unsigned int size = value.size();
        write(reinterpret_cast<const char*>(&size), sizeof(unsigned int));
        if (size != 0)
        {
            write(&value[0], size * sizeof(char));
        }
    }
}

