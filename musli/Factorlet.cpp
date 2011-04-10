// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#include "Factorlet.h"

#include "Factory.h"

namespace musli
{
//------------------------------------------------------------------------------    
    BaseFactorlet::BaseFactorlet() 
    : id(0)
    {
        Factory& factory = Factory::get_instance();
        factory.register_factorlet(this);
    }
    
//------------------------------------------------------------------------------    
    BaseFactorlet::~BaseFactorlet() {}

//------------------------------------------------------------------------------
    unsigned int BaseFactorlet::get_id() const
    {
        return id;
    }
}
    