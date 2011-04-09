// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#ifndef _MUSLI_STREAM_UNPACKER_H_
#define _MUSLI_STREAM_UNPACKER_H_

#include "Unpacker.h"

#include <iosfwd>

namespace musli
{
    class StreamUnpacker : public Unpacker
    {
    public:
        StreamUnpacker(std::istream& stream);
        
        ~StreamUnpacker();
        
    protected:
    
        virtual void read(char* data, unsigned int size);
        
    private:
        std::istream& stream;
    };
}

#endif
