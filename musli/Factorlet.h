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

#ifndef _MUSLI_FACTORLET_H_
#define _MUSLI_FACTORLET_H_

#include "config.h"

#include <typeinfo>

namespace musli
{
    class MUSLI_EXPORT BaseFactorlet
    {
    public:
        BaseFactorlet();

        virtual ~BaseFactorlet();

        unsigned int get_id() const;

        virtual const std::type_info& get_type() const = 0;

        virtual void* create() const = 0;

    private:
        unsigned int id;

    friend class Factory;
    };

    /**
     * Factorlet used to register polymorphic types for musli.
     *
     * Use the factorlet to register all types that need to be created from
     * a pointer to the base class.
     *
     * For example in your MyType.cpp file you can write:
     * @code
     * Factorlet<MyType> my_type_factorlet;
     * @endcode
     * The factorlet will then be automatically registered at mulsi's
     * factory.
     *
     * @see Unpacker
     **/
    template <typename Type>
    class MUSLI_EXPORT Factorlet : public BaseFactorlet
    {
    public:

        virtual const std::type_info& get_type() const
        {
            return typeid(Type);
        }

        virtual void* create() const
        {
            return new Type;
        }
    };
}

#endif
