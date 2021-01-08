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
#include <musli/Factorlet.h>

#include <vector>
#include <string>
#include <gtest/gtest.h>

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


musli::Packer& operator << (musli::Packer& packer, const Base& obj)
{
    obj.pack(packer);
    return packer;
}


musli::Unpacker& operator >> (musli::Unpacker& unpacker, Base& obj)
{
    obj.unpack(unpacker);
    return unpacker;
}


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

TEST(PolymorphicObjectTest, pack_objects)
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

    EXPECT_EQ(4, copies.size());

    Base* base = copies[0];
    EXPECT_EQ(1, base->base_value);

    DerivedA* a = dynamic_cast<DerivedA*>(copies[1]);
    EXPECT_TRUE(a != nullptr);
    EXPECT_EQ(2, a->base_value);
    EXPECT_EQ(3, a->a_value);

    DerivedAA* aa = dynamic_cast<DerivedAA*>(copies[2]);
    EXPECT_TRUE(aa != nullptr);
    EXPECT_EQ(4, aa->base_value);
    EXPECT_EQ(5, aa->a_value);
    EXPECT_EQ(6, aa->aa_value);

    DerivedB* b = dynamic_cast<DerivedB*>(copies[3]);
    EXPECT_TRUE(b != nullptr);
    EXPECT_EQ(7, b->base_value);
    EXPECT_EQ(8, b->b_value);

    std::for_each(origs.begin(), origs.end(), [] (auto& obj) { delete obj; });
    std::for_each(copies.begin(), copies.end(), [] (auto& obj) { delete obj; });
}


TEST(PolymorphicObjectTest, pack_unique_objects)
{
    std::vector<std::unique_ptr<Base>> origs;
    {
        auto base = std::make_unique<Base>();
        base->base_value = 1;
        origs.push_back(std::move(base));

        auto a = std::make_unique<DerivedA>();
        a->base_value = 2;
        a->a_value = 3;
        origs.push_back(std::move(a));

        auto aa = std::make_unique<DerivedAA>();
        aa->base_value = 4;
        aa->a_value = 5;
        aa->aa_value = 6;
        origs.push_back(std::move(aa));

        auto b = std::make_unique<DerivedB>();
        b->base_value = 7;
        b->b_value = 8;
        origs.push_back(std::move(b));
    }

    std::vector<char> buffer;
    musli::MemoryPacker packer(buffer);
    packer << origs;

    std::vector<std::unique_ptr<Base>> copies;
    musli::MemoryUnpacker unpacker(buffer);
    unpacker >> copies;

    EXPECT_EQ(4, copies.size());

    auto base = copies[0].get();
    EXPECT_EQ(1, base->base_value);

    auto a = dynamic_cast<DerivedA*>(copies[1].get());
    EXPECT_TRUE(a != nullptr);
    EXPECT_EQ(2, a->base_value);
    EXPECT_EQ(3, a->a_value);

    auto aa = dynamic_cast<DerivedAA*>(copies[2].get());
    EXPECT_TRUE(aa != nullptr);
    EXPECT_EQ(4, aa->base_value);
    EXPECT_EQ(5, aa->a_value);
    EXPECT_EQ(6, aa->aa_value);

    auto b = dynamic_cast<DerivedB*>(copies[3].get());
    EXPECT_TRUE(b != nullptr);
    EXPECT_EQ(7, b->base_value);
    EXPECT_EQ(8, b->b_value);
}
