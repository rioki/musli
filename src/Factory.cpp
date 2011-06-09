// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#include "Factory.h"

#include <algorithm>
#include "Factorlet.h"

namespace musli
{
//------------------------------------------------------------------------------    
    Factory& Factory::get_instance()
    {
        static Factory factory;
        return factory;
    }

//------------------------------------------------------------------------------
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
    
//------------------------------------------------------------------------------    
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
    
//------------------------------------------------------------------------------
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
    
//------------------------------------------------------------------------------    
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

//------------------------------------------------------------------------------
    Factory::Factory() {}

//------------------------------------------------------------------------------
    void Factory::register_factorlet(BaseFactorlet* factorlet)
    {
        // TODO explicit ids
        factorlet->id = factorlets.size() + 1;
        factorlets.push_back(factorlet);
    }
    
}
