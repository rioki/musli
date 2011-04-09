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
    Unpacker& Unpacker::operator >> (bool& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(bool));
        return *this;
    }

//------------------------------------------------------------------------------
    Unpacker& Unpacker::operator >> (char& value)    
    {
        read(reinterpret_cast<char*>(&value), sizeof(char));
        return *this;
    }
    
//------------------------------------------------------------------------------
    Unpacker& Unpacker::operator >> (unsigned char& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(unsigned char));
        return *this;
    }

//------------------------------------------------------------------------------
    Unpacker& Unpacker::operator >> (short& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(short));
        return *this;
    }

//------------------------------------------------------------------------------
    Unpacker& Unpacker::operator >> (unsigned short& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(unsigned short));
        return *this;
    }

//------------------------------------------------------------------------------
    Unpacker& Unpacker::operator >> (int& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(int));
        return *this;
    }

//------------------------------------------------------------------------------
    Unpacker& Unpacker::operator >> (unsigned int& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(unsigned int));
        return *this;
    }

//------------------------------------------------------------------------------
    Unpacker& Unpacker::operator >> (long& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(long));
        return *this;
    }

//------------------------------------------------------------------------------
    Unpacker& Unpacker::operator >> (unsigned long& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(unsigned long));
        return *this;
    }

//------------------------------------------------------------------------------
    Unpacker& Unpacker::operator >> (long long& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(long long));
        return *this;
    }

//------------------------------------------------------------------------------
    Unpacker& Unpacker::operator >> (unsigned long long& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(unsigned long long));
        return *this;
    }

//------------------------------------------------------------------------------
    Unpacker& Unpacker::operator >> (float& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(float));
        return *this;
    }

//------------------------------------------------------------------------------
    Unpacker& Unpacker::operator >> (double& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(double));
        return *this;
    }

//------------------------------------------------------------------------------
    Unpacker& Unpacker::operator >> (std::string& value)
    {
        unsigned int size = 0;
        read(reinterpret_cast<char*>(&size), sizeof(unsigned int));
        if (size != 0)
        {
            value = std::string(size, '\0');
            read(&value[0], size * sizeof(char));
        }
        else
        {
            value = std::string();
        }
    }
}

