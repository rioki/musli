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

#ifndef _MUSLI_FACTORY_H_
#define _MUSLI_FACTORY_H_

#include "config.h"

#include <typeinfo>
#include <vector>

namespace musli
{
    class BaseFactorlet;

    /**
     * Type Factory
     *
     * The factory is used to create polymorphic pointer types. The types are
     * registered through the use of a factorlet.
     *
     * @see Factorlet
     **/
    class MUSLI_EXPORT Factory
    {
    public:

        static Factory& get_instance();

        unsigned int get_type_id(const std::type_info& type);

        void* create(unsigned int id) const;

    private:
        std::vector<BaseFactorlet*> factorlets;

        Factory();
        void register_factorlet(BaseFactorlet* factorlet);

        Factory(const Factory&);
        const Factory& operator = (const Factory&);

    friend class BaseFactorlet;
    };

}

#endif
