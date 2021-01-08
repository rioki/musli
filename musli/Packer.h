// musli - simple serialisation library
// Copyright (c) 2011-2021 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef _MUSLI_PACKER_H_
#define _MUSLI_PACKER_H_

#include "config.h"

#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <typeinfo>

#include "Factory.h"

namespace musli
{
    /**
     * Packer
     *
     * The packer is the core object for serialisation. It contains the
     * underlying algorithm for encoding data.
     *
     * The usage and interface is very similar to std::ostream. You can
     * either pack simple types or write << operators that pack your complex
     * types.
     **/
    class MUSLI_EXPORT Packer
    {
    public:
        /**
         * Constructor
         **/
        Packer();

        /**
         * Destructor
         **/
        ~Packer();

        /**
         * Pack a bool.
         **/
        Packer& operator << (bool value);

        /**
         * Pack a char.
         **/
        Packer& operator << (char value);

        /**
         * Pack an unsigned char.
         **/
        Packer& operator << (unsigned char value);

        /**
         * Pack a short.
         **/
        Packer& operator << (short value);

        /**
         * Pack an unsigned short
         **/
        Packer& operator << (unsigned short value);

        /**
         * Pack an int.
         **/
        Packer& operator << (int value);

        /**
         * Pack an unsigned int.
         **/
        Packer& operator << (unsigned int  value);

        /**
         * Pack a long.
         **/
        Packer& operator << (long value);

        /**
         * Pack an unsigned long.
         **/
        Packer& operator << (unsigned long value);

        /**
         * Pack a long long.
         **/
        Packer& operator << (long long value);

        /**
         * Pack an unsigned long long.
         **/
        Packer& operator << (unsigned long long value);

        /**
         * Pack a float.
         **/
        Packer& operator << (float value);

        /**
         * Pack a double.
         **/
        Packer& operator << (double value);

        /**
         * Pack a string.
         **/
        Packer& operator << (const std::string& value);

        /**
         * Pack a pointer.
         *
         * @warning Cyclic pointers only work for pointers to heap objects!
         **/
        template <typename Type>
        Packer& operator << (Type* value)
        {
            std::map<void*, unsigned int>::iterator iter;
            iter = pointer_map.find(value);
            if (iter != pointer_map.end())
            {
                *this << iter->second;
            }
            else
            {
                unsigned int id = last_pointer_id;
                unsigned int type_id = factory.get_type_id(typeid(*value));
                pointer_map[value] = id;
                last_pointer_id++;
                *this << id << type_id << *value;
            }
            return *this;
        }

    protected:

        /**
         * Write to the "physical" medium.
         *
         * This method does the actual writing. Each packer needs only
         * to implement this method.
         **/
        virtual void write(const char* data, unsigned int size) = 0;

    private:
        Factory& factory;
        std::map<void*, unsigned int> pointer_map;
        unsigned int last_pointer_id;

        Packer(const Packer&);
        const Packer& operator = (const Packer&);
    };

    /**
     * Functor used to pack single objects when packing STL containers.
     **/
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

    /**
     * Pack a std::pair.
     **/
    template <typename Type1, typename Type2>
    Packer& operator << (Packer& packer, const std::pair<Type1, Type2>& value)
    {
        packer << value.first << value.second;
       return packer;
    }

    /**
     * Pack a std::vector
     **/
    template <typename Type>
    Packer& operator << (Packer& packer, const std::vector<Type>& values)
    {
        unsigned int size = values.size();
        packer << size;
        std::for_each(values.begin(), values.end(), pack_single(packer));
        return packer;
    }

    /**
     * Pack a std::list.
     **/
    template <typename Type>
    Packer& operator << (Packer& packer, const std::list<Type>& values)
    {
        unsigned int size = values.size();
        packer << size;
        std::for_each(values.begin(), values.end(), pack_single(packer));
        return packer;
    }

    /**
     * Pack a std::deque
     **/
    template <typename Type>
    Packer& operator << (Packer& packer, const std::deque<Type>& values)
    {
        unsigned int size = values.size();
        packer << size;
        std::for_each(values.begin(), values.end(), pack_single(packer));
        return packer;
    }

    /**
     * Pack a std::set
     **/
    template <typename Type>
    Packer& operator << (Packer& packer, const std::set<Type>& values)
    {
        unsigned int size = values.size();
        packer << size;
        std::for_each(values.begin(), values.end(), pack_single(packer));
        return packer;
    }

    /**
     * Pack a std::map
     **/
    template <typename KeyType, typename ValueType>
    Packer& operator << (Packer& packer, const std::map<KeyType, ValueType>& values)
    {
        unsigned int size = values.size();
        packer << size;
        std::for_each(values.begin(), values.end(), pack_single(packer));
        return packer;
    }
}

#endif

