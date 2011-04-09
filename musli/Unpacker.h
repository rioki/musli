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
        
        Unpacker& operator >> (bool& value);
        
        Unpacker& operator >> (char& value);
        
        Unpacker& operator >> (unsigned char& value);
        
        Unpacker& operator >> (short& value);
        
        Unpacker& operator >> (unsigned short& value);
        
        Unpacker& operator >> (int& value);
        
        Unpacker& operator >> (unsigned int& value);
        
        Unpacker& operator >> (long& value);
        
        Unpacker& operator >> (unsigned long& value);
        
        Unpacker& operator >> (long long& value);
        
        Unpacker& operator >> (unsigned long long& value);
        
        Unpacker& operator >> (float& value);
        
        Unpacker& operator >> (double& value);
        
        Unpacker& operator >> (std::string& value);
        
    protected: 
        
        virtual void read(char* data, unsigned int size) = 0;

    private:
        Unpacker(const Unpacker&);
        const Unpacker& operator = (const Unpacker&);
    };
}

#endif
