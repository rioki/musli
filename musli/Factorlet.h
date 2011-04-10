// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#ifndef _MUSLI_FACTORLET_H_
#define _MUSLI_FACTORLET_H_

#include <typeinfo>

namespace musli
{
    class BaseFactorlet
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
    
    template <typename Type>
    class Factorlet : public BaseFactorlet
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
