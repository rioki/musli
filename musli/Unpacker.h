// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#ifndef _MUSLI_UNPACKER_H_
#define _MUSLI_UNPACKER_H_

#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <deque>

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
    
    struct unpack_single
    {
        Unpacker& unpacker;
        
        unpack_single(Unpacker& u)
        : unpacker(u) {}
        
        template <typename Type>
        void operator () (Type& type)
        {
            unpacker >> type;
        }
    };
    
    template <typename Type>
    Unpacker& operator >> (Unpacker& unpacker, std::vector<Type>& values)
    {
        unsigned int size;
        unpacker >> size;
        values.resize(size);
        std::for_each(values.begin(), values.end(), unpack_single(unpacker));
    }
    
    template <typename Type>
    Unpacker& operator >> (Unpacker& unpacker, std::list<Type>& values)
    {
        unsigned int size;
        unpacker >> size;
        values.resize(size);
        std::for_each(values.begin(), values.end(), unpack_single(unpacker));
    }
    
    template <typename Type>
    Unpacker& operator >> (Unpacker& unpacker, std::deque<Type>& values)
    {
        unsigned int size;
        unpacker >> size;
        values.resize(size);
        std::for_each(values.begin(), values.end(), unpack_single(unpacker));
    }
}

#endif
