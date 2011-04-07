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
        
        virtual void pack_bool(bool value);
        
        virtual void pack_char(char value);
        
        virtual void pack_unsigned_char(unsigned char value);
        
        virtual void pack_short(short value);
        
        virtual void pack_unsigned_short(unsigned short value);
        
        virtual void pack_int(int value);
                
        virtual void pack_unsigned_int(unsigned int value);
        
        virtual void pack_long(long value);
        
        virtual void pack_unsigned_long(unsigned long value);
        
        virtual void pack_long_long(long long value);
        
        virtual void pack_unsigned_long_long(unsigned long long value);
        
        virtual void pack_float(float value);
        
        virtual void pack_double(double value);
        
    private:
        std::ostream& stream;
    };
}

#endif
