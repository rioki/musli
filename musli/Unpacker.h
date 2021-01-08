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

#ifndef _MUSLI_UNPACKER_H_
#define _MUSLI_UNPACKER_H_

#include "config.h"

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
    /**
     * Unpacker
     *
     * The unpacker is the core object for deserialisation. It contains the
     * underlying algorithm for decoding data.
     *
     * The usage and interface is very similar to std::istream. You can
     * either unpack simple types or write >> operators that unpack your complex
     * types.
     **/
    class MUSLI_EXPORT Unpacker
    {
    public:
        /**
         * Constructor
         **/
        Unpacker();

        /**
         * Destructor
         **/
        ~Unpacker();

        /**
         * Unpack a bool.
         **/
        Unpacker& operator >> (bool& value);

        /**
         * Unpack a char.
         **/
        Unpacker& operator >> (char& value);

        /**
         * Unpack an unsinged char.
         **/
        Unpacker& operator >> (unsigned char& value);

        /**
         * Unpack a short.
         **/
        Unpacker& operator >> (short& value);

        /**
         * Unpack an unsigned short.
         **/
        Unpacker& operator >> (unsigned short& value);

        /**
         * Unpack a int.
         **/
        Unpacker& operator >> (int& value);

        /**
         * Unpack an unsigned int.
         **/
        Unpacker& operator >> (unsigned int& value);

        /**
         * Unpack a long.
         **/
        Unpacker& operator >> (long& value);

        /**
         * Unpack a unsigned long.
         **/
        Unpacker& operator >> (unsigned long& value);

        /**
         * Unpack a long long.
         **/
        Unpacker& operator >> (long long& value);

        /**
         * Unpack an unsigned long long.
         **/
        Unpacker& operator >> (unsigned long long& value);

        /**
         * Unpack a float.
         **/
        Unpacker& operator >> (float& value);

        /**
         * Unpack a double.
         **/
        Unpacker& operator >> (double& value);

        /**
         * Unpack a string.
         **/
        Unpacker& operator >> (std::string& value);

        /**
         * Unpack a pointer,
         *
         * @note To unpack polymorphic types you need to register them with
         * the help of a Factorlet.
         *
         * @see Factorlet
         **/
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

        /**
         * Read from the "physical" medium.
         *
         * This method does the actual reading. Each unpacker needs only
         * to implement this method.
         **/
        virtual void read(char* data, unsigned int size) = 0;

    private:
        Factory& factory;
        std::vector<void*> pointer_map;

        Unpacker(const Unpacker&);
        const Unpacker& operator = (const Unpacker&);
    };

    /**
     * Functor used to unpack single objects when unpacking STL containers.
     **/
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

    /**
     * Unpack a std::pair.
     **/
    template <typename Type1, typename Type2>
    Unpacker& operator >> (Unpacker& unpacker, std::pair<Type1, Type2>& value)
    {
        unpacker >> value.first >> value.second;
        return unpacker;
    }

    /**
     * Unpack a std::vector.
     **/
    template <typename Type>
    Unpacker& operator >> (Unpacker& unpacker, std::vector<Type>& values)
    {
        unsigned int size;
        unpacker >> size;
        values.resize(size);
        std::for_each(values.begin(), values.end(), unpack_single(unpacker));
        return unpacker;
    }

    /**
     * Unpack a std::list.
     **/
    template <typename Type>
    Unpacker& operator >> (Unpacker& unpacker, std::list<Type>& values)
    {
        unsigned int size;
        unpacker >> size;
        values.resize(size);
        std::for_each(values.begin(), values.end(), unpack_single(unpacker));
        return unpacker;
    }

    /**
     * Unpack a std::deque.
     **/
    template <typename Type>
    Unpacker& operator >> (Unpacker& unpacker, std::deque<Type>& values)
    {
        unsigned int size;
        unpacker >> size;
        values.resize(size);
        std::for_each(values.begin(), values.end(), unpack_single(unpacker));
        return unpacker;
    }

    /**
     * Unpack std::set.
     **/
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

    /**
     * Unpack a std::map.
     **/
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
