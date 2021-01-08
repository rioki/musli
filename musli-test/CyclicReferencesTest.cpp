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

#include <musli/MemoryPacker.h>
#include <musli/MemoryUnpacker.h>

#include <vector>
#include <string>
#include <gtest/gtest.h>

struct Node
{
    Node()
    : id(0xDEADBEEF) {}

    Node(unsigned int i)
    : id(i) {}

    unsigned int id;
    Node* ref;
};


musli::Packer& operator << (musli::Packer& packer, const Node& obj)
{
    packer << obj.id << obj.ref;
    return packer;
}


musli::Unpacker& operator >> (musli::Unpacker& unpacker, Node& obj)
{
    unpacker >> obj.id >> obj.ref;
    return unpacker;
}


TEST(CyclicReferencesTest, pack_objects)
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

    EXPECT_EQ(root->id, copy->id);
    EXPECT_EQ(root->ref->id, copy->ref->id);
    EXPECT_EQ(copy, copy->ref->ref);

    delete root->ref;
    delete root;
    delete copy->ref;
    delete copy;
}


struct SharedNode
{
    SharedNode()
    : id(0xDEADBEEF) {}

    SharedNode(unsigned int i)
    : id(i) {}

    unsigned int id;
    std::weak_ptr<SharedNode> parent;
    std::shared_ptr<SharedNode> child;
};


musli::Packer& operator << (musli::Packer& packer, const SharedNode& obj)
{
    packer << obj.id << obj.parent << obj.child;
    return packer;
}


musli::Unpacker& operator >> (musli::Unpacker& unpacker, SharedNode& obj)
{
    unpacker >> obj.id >> obj.parent >> obj.child;
    return unpacker;
}

TEST(CyclicReferencesTest, pack_shared_objects)
{
    auto root = std::make_shared<SharedNode>(0);
    root->child = std::make_shared<SharedNode>(1);
    root->child->parent = root;

    std::vector<char> buffer;
    musli::MemoryPacker packer(buffer);
    packer << root;

    std::shared_ptr<SharedNode> copy;
    musli::MemoryUnpacker unpacker(buffer);
    unpacker >> copy;

    EXPECT_EQ(root->id, copy->id);
    EXPECT_EQ(root->child->id, copy->child->id);
    EXPECT_EQ(copy, copy->child->parent.lock());
}

