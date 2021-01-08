// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell
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

#include <musli/MemoryPacker.h>
#include <musli/MemoryUnpacker.h>

#include <vector>
#include <string>
#include <gtest/gtest.h>

struct MyObject
{
    std::string value1;
    unsigned int value2;
    bool value3;
};

musli::Packer& operator << (musli::Packer& packer, const MyObject& obj)
{
    packer << obj.value1 << obj.value2 << obj.value3;
    return packer;
}

musli::Unpacker& operator >> (musli::Unpacker& unpacker, MyObject& obj)
{
    unpacker >> obj.value1 >> obj.value2 >> obj.value3;
    return unpacker;
}

bool operator == (const MyObject& a, const MyObject& b)
{
    return a.value1 == b.value1 &&
            a.value2 == b.value2 &&
            a.value3 == b.value3;
}

TEST(SimpleObjectTest, pack_object)
{
    MyObject orig = {"Hello", 1337, true};

    std::vector<char> buffer;
    musli::MemoryPacker packer(buffer);
    packer << orig;

    MyObject copy;
    musli::MemoryUnpacker unpacker(buffer);
    unpacker >> copy;

    EXPECT_TRUE(orig == copy);
}

TEST(SimpleObjectTest, pack_pinter_to_object)
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

    EXPECT_TRUE(orig != copy);
    EXPECT_TRUE(*orig == *copy);

    delete orig;
    delete copy;
}
