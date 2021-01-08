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

#include "Factory.h"

#include <algorithm>
#include "Factorlet.h"

namespace musli
{
    Factory& Factory::get_instance()
    {
        static Factory factory;
        return factory;
    }

    struct type_equals
    {
        const std::type_info& type;

        type_equals(const std::type_info& t)
        : type(t) {}

        bool operator () (BaseFactorlet* factorlet)
        {
            return factorlet->get_type() == type;
        }
    };

    unsigned int Factory::get_type_id(const std::type_info& type)
    {
        std::vector<BaseFactorlet*>::iterator iter;
        iter = std::find_if(factorlets.begin(), factorlets.end(), type_equals(type));
        if (iter != factorlets.end())
        {
            return (*iter)->get_id();
        }
        else
        {
            return 0;
        }
    }

    struct id_equals
    {
        unsigned int id;

        id_equals(unsigned int i)
        : id(i) {}

        bool operator () (const BaseFactorlet* factorlet)
        {
            return factorlet->get_id() == id;
        }
    };

    void* Factory::create(unsigned int id) const
    {
        std::vector<BaseFactorlet*>::const_iterator iter;
        iter = std::find_if(factorlets.begin(), factorlets.end(), id_equals(id));
        if (iter != factorlets.end())
        {
            return (*iter)->create();
        }
        else
        {
            return 0;
        }
    }

    Factory::Factory() {}

    void Factory::register_factorlet(BaseFactorlet* factorlet)
    {
        // TODO explicit ids
        factorlet->id = factorlets.size() + 1;
        factorlets.push_back(factorlet);
    }

}
