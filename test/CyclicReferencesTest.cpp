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
    struct Node
    {
        Node()
        : id(0xDEADBEEF) {}
        
        Node(unsigned int i)
        : id(i) {}
        
        unsigned int id;
        Node* ref;
    };

//------------------------------------------------------------------------------
    musli::Packer& operator << (musli::Packer& packer, const Node& obj)
    {
        packer << obj.id << obj.ref;
        return packer;
    }
    
//------------------------------------------------------------------------------
    musli::Unpacker& operator >> (musli::Unpacker& unpacker, Node& obj)
    {
        unpacker >> obj.id >> obj.ref;
        return unpacker;
    }
    
//------------------------------------------------------------------------------
    TEST(pack_objects)
    {
        Node* root = new Node(0);
        root->ref = new Node(1);
        root->ref->ref = root;
        
        std::vector<char> buffer;
        musli::MemoryPacker packer(buffer); 
        packer << root;
        
        Node* copy;
        musli::MemoryUnpacker unpacker(buffer);
        unpacker >> copy;
        
        CHECK(root->id == copy->id);
        CHECK(root->ref->id == copy->ref->id);
        CHECK(copy == copy->ref->ref);
        
        delete root->ref;
        delete root;
        delete copy->ref;
        delete copy;        
    }
}