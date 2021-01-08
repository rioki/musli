// musli - simple serialisation library
// Copyright (c) 2011-2021 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "Unpacker.h"

namespace musli
{

    Unpacker::Unpacker()
    : factory(Factory::get_instance()){}

    Unpacker::~Unpacker() {}

    Unpacker& Unpacker::operator >> (bool& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(bool));
        return *this;
    }

    Unpacker& Unpacker::operator >> (char& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(char));
        return *this;
    }

    Unpacker& Unpacker::operator >> (unsigned char& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(unsigned char));
        return *this;
    }

    Unpacker& Unpacker::operator >> (short& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(short));
        return *this;
    }

    Unpacker& Unpacker::operator >> (unsigned short& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(unsigned short));
        return *this;
    }

    Unpacker& Unpacker::operator >> (int& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(int));
        return *this;
    }

    Unpacker& Unpacker::operator >> (unsigned int& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(unsigned int));
        return *this;
    }

    Unpacker& Unpacker::operator >> (long& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(long));
        return *this;
    }

    Unpacker& Unpacker::operator >> (unsigned long& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(unsigned long));
        return *this;
    }

    Unpacker& Unpacker::operator >> (long long& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(long long));
        return *this;
    }

    Unpacker& Unpacker::operator >> (unsigned long long& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(unsigned long long));
        return *this;
    }

    Unpacker& Unpacker::operator >> (float& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(float));
        return *this;
    }

    Unpacker& Unpacker::operator >> (double& value)
    {
        read(reinterpret_cast<char*>(&value), sizeof(double));
        return *this;
    }

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
        return *this;
    }
}

