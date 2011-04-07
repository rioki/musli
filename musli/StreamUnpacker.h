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
        
        virtual void unpack(bool& value);
        
        virtual void unpack(char& value);
        
        virtual void unpack(unsigned char& value);
        
        virtual void unpack(short& value);
        
        virtual void unpack(unsigned short& value);
        
        virtual void unpack(int& value);
                
        virtual void unpack(unsigned int& value);
        
        virtual void unpack(long& value);
        
        virtual void unpack(unsigned long& value);
        
        virtual void unpack(long long& value);
        
        virtual void unpack(unsigned long long& value);
        
        virtual void unpack(float& value);
        
        virtual void unpack(double& value);
        
        virtual void unpack(std::string& value);
        
    private:
        std::istream& stream;
    };
}

#endif
