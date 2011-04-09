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
        
        Packer& operator << (bool value);
        
        Packer& operator << (char value);
        
        Packer& operator << (unsigned char value);
        
        Packer& operator << (short value);
        
        Packer& operator << (unsigned short value);
        
        Packer& operator << (int value);
        
        Packer& operator << (unsigned int  value);
        
        Packer& operator << (long value);
        
        Packer& operator << (unsigned long value);
        
        Packer& operator << (long long value);
        
        Packer& operator << (unsigned long long value);
        
        Packer& operator << (float value);
        
        Packer& operator << (double value);
        
        Packer& operator << (const std::string& value);
    
    protected:
        
        virtual void write(const char* data, unsigned int size) = 0;
    
    private:
        Packer(const Packer&);
        const Packer& operator = (const Packer&);
    };  
}

#endif
