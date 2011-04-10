// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#ifndef _MUSLI_PACKER_H_
#define _MUSLI_PACKER_H_

#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>

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
        
    struct pack_single
    {
        Packer& packer;
        
        pack_single(Packer& p)
        : packer(p) {}
        
        template <typename Type>
        void operator () (Type type)
        {
            packer << type;
        }
    };
    
    template <typename Type1, typename Type2>
    Packer& operator << (Packer& packer, const std::pair<Type1, Type2>& value)
    {
        packer << value.first << value.second;
        return packer;
    }
    
    template <typename Type>
    Packer& operator << (Packer& packer, const std::vector<Type>& values)
    {
        unsigned int size = values.size();
        packer << size;
        std::for_each(values.begin(), values.end(), pack_single(packer));
        return packer;
    }
    
    template <typename Type>
    Packer& operator << (Packer& packer, const std::list<Type>& values)
    {
        unsigned int size = values.size();
        packer << size;
        std::for_each(values.begin(), values.end(), pack_single(packer));  
        return packer;
    }
    
    template <typename Type>
    Packer& operator << (Packer& packer, const std::deque<Type>& values)
    {
        unsigned int size = values.size();
        packer << size;
        std::for_each(values.begin(), values.end(), pack_single(packer)); 
        return packer;
    }
    
    template <typename Type>
    Packer& operator << (Packer& packer, const std::set<Type>& values)
    {
        unsigned int size = values.size();
        packer << size;
        std::for_each(values.begin(), values.end(), pack_single(packer));
        return packer;
    }
    
    template <typename KeyType, typename ValueType>
    Packer& operator << (Packer& packer, const std::map<KeyType, ValueType>& values)
    {
        unsigned int size = values.size();
        packer << size;
        std::for_each(values.begin(), values.end(), pack_single(packer));
        return packer;
    }
    
    template <typename Type>
    Packer& operator << (Packer& packer, Type* value)
    {
        packer << *value;
        return packer;
    }
}

#endif
