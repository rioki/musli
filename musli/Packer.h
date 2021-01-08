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
#include <memory>
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
    //! Packer
    //!
    //! The packer is the core object for serialisation. It contains the
    //! underlying algorithm for encoding data.
    //!
    //! The usage and interface is very similar to std::ostream. You can
    //! either pack simple types or write << operators that pack your complex
    //! types.
    class MUSLI_EXPORT Packer
    {
    public:
        //! Constructor
        Packer();

        //! Pack a value
        //!
        //! @param value the value to pack
        //! @{
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
        //! @}

        //! Pack a pointer.
        //!
        //! @warning Cyclic pointers only work for pointers to heap objects!
        template <typename Type>
        Packer& operator << (Type* value)
        {
            if (value == nullptr)
            {
                *this << 0u;
            }
            else
            {
                auto iter = pointer_map.find(value);
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
            }
            return *this;
        }

    protected:

        //! Write to the "physical" medium.
        //!
        //! This method does the actual writing. Each packer needs only
        //! to implement this method.
        virtual void write(const char* data, unsigned int size) = 0;

    private:
        Factory& factory;
        std::map<void*, unsigned int> pointer_map;
        unsigned int last_pointer_id = 1;

        Packer(const Packer&) = delete;
        const Packer& operator = (const Packer&) = delete;
    };

    //! Pack STD containers and objects
    //!
    //! @{
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
        for (const auto& value : values)
        {
            packer << value;
        }
        return packer;
    }

    template <typename Type>
    Packer& operator << (Packer& packer, const std::list<Type>& values)
    {
        unsigned int size = values.size();
        packer << size;
        for (const auto& value : values)
        {
            packer << value;
        }
        return packer;
    }

    template <typename Type>
    Packer& operator << (Packer& packer, const std::deque<Type>& values)
    {
        unsigned int size = values.size();
        packer << size;
        for (const auto& value : values)
        {
            packer << value;
        }
        return packer;
    }

    template <typename Type>
    Packer& operator << (Packer& packer, const std::set<Type>& values)
    {
        unsigned int size = values.size();
        packer << size;
        for (const auto& value : values)
        {
            packer << value;
        }
        return packer;
    }

    template <typename KeyType, typename ValueType>
    Packer& operator << (Packer& packer, const std::map<KeyType, ValueType>& values)
    {
        unsigned int size = values.size();
        packer << size;
        for (const auto& value : values)
        {
            packer << value;
        }
        return packer;
    }

    template <typename Type>
    Packer& operator << (Packer& packer, const std::shared_ptr<Type>& value)
    {
        packer << value.get();
        return packer;
    }

    template <typename Type>
    Packer& operator << (Packer& packer, const std::weak_ptr<Type>& value)
    {
        packer << value.lock().get(); // this can be nullptr
        return packer;
    }

    template <typename Type>
    Packer& operator << (Packer& packer, const std::unique_ptr<Type>& value)
    {
        packer << value.get();
        return packer;
    }
    //! @}
}

#endif

