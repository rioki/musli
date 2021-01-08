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

#ifndef _MUSLI_MEMORY_UNPACKER_H_
#define _MUSLI_MEMORY_UNPACKER_H_

#include "config.h"

#include "Unpacker.h"

#include <vector>

namespace musli
{
    //! Implementation of a Unpacker that unpacks from memory.
    class MUSLI_EXPORT MemoryUnpacker : public Unpacker
    {
    public:
        //! Constructor
        //!
        //! @param buffer the buffer to unpack from.
        MemoryUnpacker(const std::vector<char>& buffer);

    protected:

        virtual void read(char* data, unsigned int size);

    private:
        const std::vector<char>& buffer;

        std::vector<char>::const_iterator read_pos;
    };
}

#endif
