// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#include "StreamPacker.h"
#include "StreamUnpacker.h"

#include <sstream>
#include <vector>
#include <list>
#include <cstdlib>
#include <algorithm>
#include <UnitTest++/UnitTest++.h>

SUITE(StreamPackerTest)
{
//------------------------------------------------------------------------------    
    TEST(pack_vector)
    {
        std::vector<unsigned int> orig(25);
        std::generate(orig.begin(), orig.end(), std::rand);
        
        std::stringstream stream;
        musli::StreamPacker packer(stream);
                
        packer << orig;
        
        musli::StreamUnpacker unpacker(stream);
        std::vector<unsigned int> copy;
        unpacker >> copy;
        
        CHECK(orig == copy);
    }
    
//------------------------------------------------------------------------------    
    TEST(pack_list)
    {
        std::list<unsigned int> orig(25);
        std::generate(orig.begin(), orig.end(), std::rand);
        
        std::stringstream stream;
        musli::StreamPacker packer(stream);
                
        packer << orig;
        
        musli::StreamUnpacker unpacker(stream);
        std::list<unsigned int> copy;
        unpacker >> copy;
        
        CHECK(orig == copy);
    }
    
//------------------------------------------------------------------------------    
    TEST(pack_deque)
    {
        std::deque<unsigned int> orig(25);
        std::generate(orig.begin(), orig.end(), std::rand);
        
        std::stringstream stream;
        musli::StreamPacker packer(stream);
                
        packer << orig;
        
        musli::StreamUnpacker unpacker(stream);
        std::deque<unsigned int> copy;
        unpacker >> copy;
        
        CHECK(orig == copy);
    }
}
