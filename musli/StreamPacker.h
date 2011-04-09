// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#ifndef _MUSLI_STREAM_PACKER_H_
#define _MUSLI_STREAM_PACKER_H_

#include "Packer.h"

#include <iosfwd>

namespace musli
{
    class StreamPacker : public Packer
    {
    public:
        StreamPacker(std::ostream& stream);
        
        ~StreamPacker();
    
    protected:
        
        virtual void write(const char* data, unsigned int size);
        
    private:
        std::ostream& stream;
    };
}

#endif
