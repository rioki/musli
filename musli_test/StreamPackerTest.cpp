// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#include "StreamPacker.h"
#include "StreamUnpacker.h"

#include <sstream>
#include <string>
#include <UnitTest++/UnitTest++.h>

SUITE(StreamPackerTest)
{
//------------------------------------------------------------------------------    
    TEST(pack_int)
    {
        std::stringstream stream;
        musli::StreamPacker packer(stream);
                
        int orig = -13;
        packer << orig;
        
        musli::StreamUnpacker unpacker(stream);
        int copy = 0;
        unpacker >> copy;
        
        CHECK_EQUAL(orig, copy);
    }

//------------------------------------------------------------------------------
    TEST(pack_pod)
    {
        std::stringstream stream;
        musli::StreamPacker packer(stream);
        
        bool bool_orig = true;
        char char_orig = 11;
        unsigned char uchar_orig = 12;        
        int int_orig = 13;
        unsigned int uint_orig = 14;
        short short_orig = 15;
        unsigned short ushort_orig = 16;
        long long_orig = 17;
        unsigned long ulong_orig = 18;
        long long llong_orig = 19;
        unsigned long ullong_orig = 20;
        float float_orig = 2.1;
        double double_orig = 2.2;
        
        packer << bool_orig;
        packer << char_orig;
        packer << uchar_orig;
        packer << int_orig;
        packer << uint_orig;
        packer << short_orig;
        packer << ushort_orig;
        packer << long_orig;
        packer << ulong_orig;
        packer << llong_orig;
        packer << ullong_orig;
        packer << float_orig;
        packer << double_orig;
        
        musli::StreamUnpacker unpacker(stream);
        
        bool bool_copy = false;
        char char_copy = 0;
        unsigned char uchar_copy = 0;        
        int int_copy = 0;
        unsigned int uint_copy = 0;
        short short_copy = 0;
        unsigned short ushort_copy = 0;
        long long_copy = 0;
        unsigned long ulong_copy = 0;
        long long llong_copy = 0;
        unsigned long ullong_copy = 0;
        float float_copy = 0.0;
        double double_copy = 0.0;
        
        unpacker >> bool_copy;
        unpacker >> char_copy;
        unpacker >> uchar_copy;
        unpacker >> int_copy;
        unpacker >> uint_copy;
        unpacker >> short_copy;
        unpacker >> ushort_copy;
        unpacker >> long_copy;
        unpacker >> ulong_copy;
        unpacker >> llong_copy;
        unpacker >> ullong_copy;
        unpacker >> float_copy;
        unpacker >> double_copy;     
        
        CHECK_EQUAL(bool_orig, bool_copy);
        CHECK_EQUAL(char_orig, char_copy);
        CHECK_EQUAL(uchar_orig, uchar_copy);
        CHECK_EQUAL(int_orig, int_copy);
        CHECK_EQUAL(uint_orig, uint_copy);
        CHECK_EQUAL(short_orig, short_copy);
        CHECK_EQUAL(ushort_orig, ushort_copy);
        CHECK_EQUAL(long_orig, long_copy);
        CHECK_EQUAL(ulong_orig, ulong_copy);
        CHECK_EQUAL(llong_orig, llong_copy);
        CHECK_EQUAL(ullong_orig, ullong_copy);
        CHECK_EQUAL(float_orig, float_copy);
        CHECK_EQUAL(double_orig, double_copy);
    }

//------------------------------------------------------------------------------
    TEST(pack_string)
    {
        std::stringstream stream;
        musli::StreamPacker packer(stream);        
        
        std::string orig = "Make mine a Murphy's!";
        packer << orig;
        
        musli::StreamUnpacker unpacker(stream);
        std::string copy;
        unpacker >> copy;
        
        CHECK_EQUAL(orig, copy);
    }
}