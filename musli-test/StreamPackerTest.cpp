// musli - simple serialisation library
// Copyright (c) 2011-2021 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include <musli/StreamPacker.h>
#include <musli/StreamUnpacker.h>

#include <sstream>
#include <string>
#include <gtest/gtest.h>

TEST(StreamPackerTest, pack_int)
{
    std::stringstream stream;
    musli::StreamPacker packer(stream);

    int orig = -13;
    packer << orig;

    musli::StreamUnpacker unpacker(stream);
    int copy = 0;
    unpacker >> copy;

    EXPECT_EQ(orig, copy);
}


TEST(StreamPackerTest, pack_pod)
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

    EXPECT_EQ(bool_orig, bool_copy);
    EXPECT_EQ(char_orig, char_copy);
    EXPECT_EQ(uchar_orig, uchar_copy);
    EXPECT_EQ(int_orig, int_copy);
    EXPECT_EQ(uint_orig, uint_copy);
    EXPECT_EQ(short_orig, short_copy);
    EXPECT_EQ(ushort_orig, ushort_copy);
    EXPECT_EQ(long_orig, long_copy);
    EXPECT_EQ(ulong_orig, ulong_copy);
    EXPECT_EQ(llong_orig, llong_copy);
    EXPECT_EQ(ullong_orig, ullong_copy);
    EXPECT_EQ(float_orig, float_copy);
    EXPECT_EQ(double_orig, double_copy);
}


TEST(StreamPackerTest, pack_string)
{
    std::stringstream stream;
    musli::StreamPacker packer(stream);

    std::string orig = "Make mine a Murphy's!";
    packer << orig;

    musli::StreamUnpacker unpacker(stream);
    std::string copy;
    unpacker >> copy;

    EXPECT_EQ(orig, copy);
}
