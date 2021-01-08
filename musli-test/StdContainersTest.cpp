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
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <gtest/gtest.h>

TEST(StreamPackerTest, pack_vector)
{
    std::vector<unsigned int> orig(25);
    std::generate(orig.begin(), orig.end(), std::rand);

    std::stringstream stream;
    musli::StreamPacker packer(stream);

    packer << orig;

    musli::StreamUnpacker unpacker(stream);
    std::vector<unsigned int> copy;
    unpacker >> copy;

    EXPECT_TRUE(orig == copy);
}


TEST(StreamPackerTest, pack_empty_vector)
{
    std::vector<unsigned int> orig;
    std::generate(orig.begin(), orig.end(), std::rand);

    std::stringstream stream;
    musli::StreamPacker packer(stream);

    packer << orig;

    musli::StreamUnpacker unpacker(stream);
    std::vector<unsigned int> copy;
    unpacker >> copy;

    EXPECT_TRUE(orig == copy);
}


TEST(StreamPackerTest, pack_list)
{
    std::list<unsigned int> orig(25);
    std::generate(orig.begin(), orig.end(), std::rand);

    std::stringstream stream;
    musli::StreamPacker packer(stream);

    packer << orig;

    musli::StreamUnpacker unpacker(stream);
    std::list<unsigned int> copy;
    unpacker >> copy;

    EXPECT_TRUE(orig == copy);
}


TEST(StreamPackerTest, pack_deque)
{
    std::deque<unsigned int> orig(25);
    std::generate(orig.begin(), orig.end(), std::rand);

    std::stringstream stream;
    musli::StreamPacker packer(stream);

    packer << orig;

    musli::StreamUnpacker unpacker(stream);
    std::deque<unsigned int> copy;
    unpacker >> copy;

    EXPECT_TRUE(orig == copy);
}


TEST(StreamPackerTest, pack_set)
{
    std::set<unsigned int> orig;
    for (unsigned int i = 0; i < 25; i++)
    {
        orig.insert(rand());
    }

    std::stringstream stream;
    musli::StreamPacker packer(stream);

    packer << orig;

    musli::StreamUnpacker unpacker(stream);
    std::set<unsigned int> copy;
    unpacker >> copy;

    EXPECT_TRUE(orig == copy);
}


TEST(StreamPackerTest, pack_map)
{
    std::map<unsigned int, unsigned int> orig;
    for (unsigned int i = 0; i < 25; i++)
    {
        orig[rand()] = rand();
    }

    std::stringstream stream;
    musli::StreamPacker packer(stream);

    packer << orig;

    musli::StreamUnpacker unpacker(stream);
    std::map<unsigned int, unsigned int> copy;
    unpacker >> copy;

    EXPECT_TRUE(orig == copy);
}
