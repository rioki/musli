// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#ifndef _MUSLI_FACTORY_H_
#define _MUSLI_FACTORY_H_

#include <vector>

namespace musli
{
    class BaseFactorlet;
    
    class Factory
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
