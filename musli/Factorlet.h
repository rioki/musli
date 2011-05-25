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
