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
#include <memory>
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
    //! Unpacker
    //!
    //! The unpacker is the core object for deserialisation. It contains the
    //! underlying algorithm for decoding data.
    //!
    //! The usage and interface is very similar to std::istream. You can
    //! either unpack simple types or write >> operators that unpack your complex
    //! types.
    class MUSLI_EXPORT Unpacker
    {
    public:
        //! Constructor
        Unpacker();

        //! Unpack a simple value
        //!
        //! @param value
        //! @{
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
        //! @}

        //! Unpack a pointer,
        //!
        //! @note To unpack polymorphic types you need to register them with
        //! the help of a Factorlet.
        //!
        //! @see Factorlet
        template <typename Type>
        Unpacker& operator >> (Type*& value)
        {
            unsigned int id = 0;
            *this >> id;
            if (id == 0u)
            {
                value = nullptr;
            }
            else
            {
                id -= 1;
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
            }
            return *this;
        }

        //! Unpack a shared pointer,
        //!
        //! @note To unpack polymorphic types you need to register them with
        //! the help of a Factorlet.
        //!
        //! @see Factorlet
        template <typename Type>
        Unpacker& operator >> (std::shared_ptr<Type>& value)
        {
            Type* ptr = nullptr;
            *this >> ptr;

            auto i = find_if(begin(shared_pointers), end(shared_pointers), [&] (auto& sptr) { return sptr.get() == ptr; });
            if (i != end(shared_pointers))
            {
                value = std::reinterpret_pointer_cast<Type>(*i);
            }
            else
            {
                value = std::shared_ptr<Type>(ptr);
                shared_pointers.push_back(value);
            }
            return *this;
        }

    protected:

        //! Read from the "physical" medium.
        //!
        //! This method does the actual reading. Each unpacker needs only
        //! to implement this method.
        virtual void read(char* data, unsigned int size) = 0;

    private:
        Factory& factory;
        std::vector<void*> pointer_map;
        std::list<std::shared_ptr<void>> shared_pointers;

        Unpacker(const Unpacker&);
        const Unpacker& operator = (const Unpacker&);
    };

    //! Unpack STD containers and objects
    //!
    //! @{
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
        for (auto& value : values)
        {
            unpacker >> value;
        }
        return unpacker;
    }

    template <typename Type>
    Unpacker& operator >> (Unpacker& unpacker, std::list<Type>& values)
    {
        unsigned int size;
        unpacker >> size;
        values.resize(size);
        for (auto& value : values)
        {
            unpacker >> value;
        }
        return unpacker;
    }

    template <typename Type>
    Unpacker& operator >> (Unpacker& unpacker, std::deque<Type>& values)
    {
        unsigned int size;
        unpacker >> size;
        values.resize(size);
        for (auto& value : values)
        {
            unpacker >> value;
        }
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

    template <typename Type>
    Unpacker& operator >> (Unpacker& unpacker, std::weak_ptr<Type>& value)
    {
        std::shared_ptr<Type> ptr;
        unpacker >> ptr;
        value = ptr;
        return unpacker;
    }

    template <typename Type>
    Unpacker& operator >> (Unpacker& unpacker, std::unique_ptr<Type>& value)
    {
        // NOTE:
        // Although we know this pointer is unique, we don't know if the pointer
        // may be use as a non authoritative reference somewhere else.
        // Thus we need to assume it is shared and can't create the object with make_unique.
        Type* ptr = nullptr;
        unpacker >> ptr;
        value = std::unique_ptr<Type>(ptr);
        return unpacker;
    }
    //! @}
}

#endif
