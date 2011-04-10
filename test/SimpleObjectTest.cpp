// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#include "MemoryPacker.h"
#include "MemoryUnpacker.h"

#include <vector>
#include <string>
#include <UnitTest++/UnitTest++.h>

SUITE(SimpleObjectTest)
{
//------------------------------------------------------------------------------
    struct MyObject
    {
        std::string value1;
        unsigned int value2;
        bool value3;
    };

//------------------------------------------------------------------------------
    musli::Packer& operator << (musli::Packer& packer, const MyObject& obj)
    {
        packer << obj.value1 << obj.value2 << obj.value3;
        return packer;
    }
    
//------------------------------------------------------------------------------
    musli::Unpacker& operator >> (musli::Unpacker& unpacker, MyObject& obj)
    {
        unpacker >> obj.value1 >> obj.value2 >> obj.value3;
        return unpacker;
    }
    
//------------------------------------------------------------------------------
    bool operator == (const MyObject& a, const MyObject& b)
    {
        return a.value1 == b.value1 && 
               a.value2 == b.value2 &&
               a.value3 == b.value3;
    }
    
    
//------------------------------------------------------------------------------
    TEST(pack_object)
    {
        MyObject orig = {"Hello", 1337, true};
        
        std::vector<char> buffer;
        musli::MemoryPacker packer(buffer); 
        packer << orig;
        
        MyObject copy;
        musli::MemoryUnpacker unpacker(buffer);
        unpacker >> copy;
        
        CHECK(orig == copy);
    }

//------------------------------------------------------------------------------
    TEST(pack_pinter_to_object)
    {
        MyObject* orig = new MyObject;
        orig->value1 = "Hello";
        orig->value2 = 1337;
        orig->value3 = true;
        
        std::vector<char> buffer;
        musli::MemoryPacker packer(buffer); 
        packer << orig;
        
        MyObject* copy;
        musli::MemoryUnpacker unpacker(buffer);
        unpacker >> copy;
        
        CHECK(orig != copy);
        CHECK(*orig == *copy);
        
        delete orig;
        delete copy;
    }
}