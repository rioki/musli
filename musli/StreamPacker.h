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
        
        virtual void pack(bool value);
        
        virtual void pack(char value);
        
        virtual void pack(unsigned char value);
        
        virtual void pack(short value);
        
        virtual void pack(unsigned short value);
        
        virtual void pack(int value);
                
        virtual void pack(unsigned int value);
        
        virtual void pack(long value);
        
        virtual void pack(unsigned long value);
        
        virtual void pack(long long value);
        
        virtual void pack(unsigned long long value);
        
        virtual void pack(float value);
        
        virtual void pack(double value);
        
        virtual void pack(const std::string& value);
        
    private:
        std::ostream& stream;
    };
}

#endif
