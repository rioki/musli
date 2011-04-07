// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#ifndef _MUSLI_PACKER_H_
#define _MUSLI_PACKER_H_

#include <string>

namespace musli
{
    class Packer
    {
    public:
        Packer();
        
        ~Packer();
        
        virtual void pack(bool value) = 0;
        
        virtual void pack(char value) = 0;
        
        virtual void pack(unsigned char value) = 0;
        
        virtual void pack(short value) = 0;
        
        virtual void pack(unsigned short value) = 0;
        
        virtual void pack(int value) = 0;
                
        virtual void pack(unsigned int value) = 0;
        
        virtual void pack(long value) = 0;
        
        virtual void pack(unsigned long value) = 0;
        
        virtual void pack(long long value) = 0;
        
        virtual void pack(unsigned long long value) = 0;
        
        virtual void pack(float value) = 0;
        
        virtual void pack(double value) = 0;
        
        virtual void pack(const std::string& value) = 0;
        
    private:
        Packer(const Packer&);
        const Packer& operator = (const Packer&);
    };

    template <typename Type>
    Packer& operator << (Packer& packer, Type value)
    {
        packer.pack(value);
        return packer;
    }    
}

#endif
