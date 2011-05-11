// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#include "MemoryPacker.h"
#include "MemoryUnpacker.h"
#include "Factorlet.h"

#include <vector>
#include <string>
#include <UnitTest++/UnitTest++.h>

SUITE(PolymorphicObjectTest)
{
//------------------------------------------------------------------------------
    struct Base
    {        
        unsigned int base_value;     
        
        virtual ~Base() {}
        
        virtual void pack(musli::Packer& packer) const
        {
            packer << base_value;
        }
        
        virtual void unpack(musli::Unpacker& unpacker)
        {
            unpacker >> base_value;
        }
    };
    
//------------------------------------------------------------------------------
    musli::Packer& operator << (musli::Packer& packer, const Base& obj)
    {
        obj.pack(packer);
        return packer;
    }
    
//------------------------------------------------------------------------------
    musli::Unpacker& operator >> (musli::Unpacker& unpacker, Base& obj)
    {
        obj.unpack(unpacker);
        return unpacker;
    }

//------------------------------------------------------------------------------
    struct DerivedA : public Base
    {
        unsigned int a_value;
        
        virtual void pack(musli::Packer& packer) const
        {
            Base::pack(packer);
            packer << a_value;
        }
        
        virtual void unpack(musli::Unpacker& unpacker)
        {
            Base::unpack(unpacker);
            unpacker >> a_value;
        }        
    };
    
    musli::Factorlet<DerivedA>  deriveda_factorlet;   

//------------------------------------------------------------------------------
    struct DerivedAA : public DerivedA
    {
        unsigned int aa_value;
        
        virtual void pack(musli::Packer& packer) const
        {
            DerivedA::pack(packer);
            packer << aa_value;
        }
        
        virtual void unpack(musli::Unpacker& unpacker)
        {
            DerivedA::unpack(unpacker);
            unpacker >> aa_value;
        }
    };
    
    musli::Factorlet<DerivedAA>  derivedaa_factorlet;

//------------------------------------------------------------------------------
    struct DerivedB : public Base
    {
        unsigned int b_value;
        
        virtual void pack(musli::Packer& packer) const
        {
            Base::pack(packer);
            packer << b_value;
        }
        
        virtual void unpack(musli::Unpacker& unpacker)
        {
            Base::unpack(unpacker);
            unpacker >> b_value;
        }  
    };
    
    musli::Factorlet<DerivedB>  derivedb_factorlet;

//------------------------------------------------------------------------------
    void delete_base(Base* obj)
    {
        delete obj;
    }
    
//------------------------------------------------------------------------------
    TEST(pack_objects)
    {
        std::vector<Base*> origs;
        {
            Base* base = new Base;
            base->base_value = 1;
            origs.push_back(base);
            
            DerivedA* a = new DerivedA;
            a->base_value = 2;
            a->a_value = 3;
            origs.push_back(a);
            
            DerivedAA* aa = new DerivedAA;
            aa->base_value = 4;
            aa->a_value = 5;
            aa->aa_value = 6;
            origs.push_back(aa);
            
            DerivedB* b = new DerivedB;
            b->base_value = 7;
            b->b_value = 8;
            origs.push_back(b);
        }
        
        std::vector<char> buffer;
        musli::MemoryPacker packer(buffer); 
        packer << origs;
        
        std::vector<Base*> copies;
        musli::MemoryUnpacker unpacker(buffer); 
        unpacker >> copies;
        
        CHECK_EQUAL(4, copies.size());
        
        Base* base = copies[0];
        CHECK_EQUAL(1, base->base_value);
        
        DerivedA* a = dynamic_cast<DerivedA*>(copies[1]);
        CHECK(a != NULL);
        CHECK_EQUAL(2, a->base_value);
        CHECK_EQUAL(3, a->a_value);
        
        DerivedAA* aa = dynamic_cast<DerivedAA*>(copies[2]);
        CHECK(aa != NULL);
        CHECK_EQUAL(4, aa->base_value);
        CHECK_EQUAL(5, aa->a_value);
        CHECK_EQUAL(6, aa->aa_value);
        
        DerivedB* b = dynamic_cast<DerivedB*>(copies[3]);
        CHECK(b != NULL);
        CHECK_EQUAL(7, b->base_value);
        CHECK_EQUAL(8, b->b_value);
        
        std::for_each(origs.begin(), origs.end(), delete_base);
        std::for_each(copies.begin(), copies.end(), delete_base);
    }
}