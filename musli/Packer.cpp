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

#include "Packer.h"

namespace musli
{
    Packer::Packer()
    : factory(Factory::get_instance()), last_pointer_id(0) {}

    Packer& Packer::operator << (bool value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(bool));
        return *this;
    }

    Packer& Packer::operator << (char value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(char));
        return *this;
    }

    Packer& Packer::operator << (unsigned char value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(unsigned char));
        return *this;
    }

    Packer& Packer::operator << (short value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(short));
        return *this;
    }

    Packer& Packer::operator << (unsigned short value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(unsigned short));
        return *this;
    }

    Packer& Packer::operator << (int value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(int));
        return *this;
    }

    Packer& Packer::operator << (unsigned int  value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(unsigned int));
        return *this;
    }

    Packer& Packer::operator << (long value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(long));
        return *this;
    }

    Packer& Packer::operator << (unsigned long value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(unsigned long));
        return *this;
    }

    Packer& Packer::operator << (long long value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(long long));
        return *this;
    }

    Packer& Packer::operator << (unsigned long long value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(unsigned long long));
        return *this;
    }

    Packer& Packer::operator << (float value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(float));
        return *this;
    }

    Packer& Packer::operator << (double value)
    {
        write(reinterpret_cast<const char*>(&value), sizeof(double));
        return *this;
    }

    Packer& Packer::operator << (const std::string& value)
    {
        unsigned int size = value.size();
        write(reinterpret_cast<const char*>(&size), sizeof(unsigned int));
        if (size != 0)
        {
            write(&value[0], size * sizeof(char));
        }
        return *this;
    }
}

