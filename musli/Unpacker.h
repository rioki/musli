// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#ifndef _MUSLI_UNPACKER_H_
#define _MUSLI_UNPACKER_H_

#include <string>

namespace musli
{
    class Unpacker
    {
    public:
        Unpacker();
        
        ~Unpacker();
        
        virtual void unpack(bool& value) = 0;
        
        virtual void unpack(char& value) = 0;
        
        virtual void unpack(unsigned char& value) = 0;
        
        virtual void unpack(short& value) = 0;
        
        virtual void unpack(unsigned short& value) = 0;
        
        virtual void unpack(int& value) = 0;
                
        virtual void unpack(unsigned int& value) = 0;
        
        virtual void unpack(long& value) = 0;
        
        virtual void unpack(unsigned long& value) = 0;
        
        virtual void unpack(long long& value) = 0;
        
        virtual void unpack(unsigned long long& value) = 0;
        
        virtual void unpack(float& value) = 0;
        
        virtual void unpack(double& value) = 0;
        
        virtual void unpack(std::string& value) = 0;
        
    private:
        Unpacker(const Unpacker&);
        const Unpacker& operator = (const Unpacker&);
    };
    
    template <typename Type>
    Unpacker& operator >> (Unpacker& unpacker, Type& value)
    {
        unpacker.unpack(value);
        return unpacker;
    } 
}

#endif
