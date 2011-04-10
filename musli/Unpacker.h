// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#ifndef _MUSLI_UNPACKER_H_
#define _MUSLI_UNPACKER_H_

#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <stdexcept>

#include "Factory.h"

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
        
        template <typename Type>
        Unpacker& operator >> (Type*& value)
        {
            unsigned int id = 0;
            *this >> id;
            if (id < pointer_map.size())
            {
                value = static_cast<Type*>(pointer_map[id]);
            }
            else
            {
                unsigned int type_id = 0;
                *this >> type_id;
                
                if (type_id == 0)
                {
                    value = new Type;                
                }
                else
                {
                    value = reinterpret_cast<Type*>(factory.create(type_id));
                }
                
                if (id != pointer_map.size())
                {
                    throw std::logic_error("Invalid pointer id.");
                }
                
                pointer_map.push_back(value);
                
                *this >> *value;
            }
            return *this;
        }
        
    protected: 
        
        virtual void read(char* data, unsigned int size) = 0;

    private:
        Factory& factory;
        std::vector<void*> pointer_map;
    
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
    
    template <typename Type1, typename Type2>
    Unpacker& operator >> (Unpacker& unpacker, std::pair<Type1, Type2>& value)
    {
        unpacker >> value.first >> value.second;
        return unpacker;
    }
    
    template <typename Type>
    Unpacker& operator >> (Unpacker& unpacker, std::vector<Type>& values)
    {
        unsigned int size;
        unpacker >> size;
        values.resize(size);
        std::for_each(values.begin(), values.end(), unpack_single(unpacker));
        return unpacker;
    }
    
    template <typename Type>
    Unpacker& operator >> (Unpacker& unpacker, std::list<Type>& values)
    {
        unsigned int size;
        unpacker >> size;
        values.resize(size);
        std::for_each(values.begin(), values.end(), unpack_single(unpacker));
        return unpacker;
    }
    
    template <typename Type>
    Unpacker& operator >> (Unpacker& unpacker, std::deque<Type>& values)
    {
        unsigned int size;
        unpacker >> size;
        values.resize(size);
        std::for_each(values.begin(), values.end(), unpack_single(unpacker));
        return unpacker;
    }
    
    template <typename Type>
    Unpacker& operator >> (Unpacker& unpacker, std::set<Type>& values)
    {
        unsigned int size;
        unpacker >> size;
        
        values.clear();
        for (unsigned int i = 0; i < size; i++)
        {
            Type value;
            unpacker >> value;
            values.insert(value);
        }
        return unpacker;
    }
    
    template <typename KeyType, typename ValueType>
    Unpacker& operator >> (Unpacker& unpacker, std::map<KeyType, ValueType>& values)
    {
        unsigned int size;
        unpacker >> size;
        
        values.clear();
        for (unsigned int i = 0; i < size; i++)
        {
            std::pair<KeyType, ValueType> value;
            unpacker >> value;
            values.insert(value);
        }
        return unpacker;
    }
}

#endif
