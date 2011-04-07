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
        
        virtual bool unpack_bool();
        
        virtual char unpack_char();
        
        virtual unsigned char unpack_unsigned_char();
        
        virtual short unpack_short();
        
        virtual unsigned short unpack_unsigned_short();
        
        virtual int unpack_int();
        
        virtual unsigned int unpack_unsigned_int();
        
        virtual long unpack_long();
        
        virtual unsigned long unpack_unsigned_long();
        
        virtual long long unpack_long_long();
        
        virtual unsigned long long unpack_unsigned_long_long();
                
        virtual float unpack_float();
        
        virtual double unpack_double();
        
    private:
        std::istream& stream;
    };
}

#endif
