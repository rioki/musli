# A Introduction to musli


musli is a serialisation library that aims to be simple to use. This document 
shows you how simple it is to use.

## Basic Concepts

The design of musli borrows basic concepts from the iostream library. But instead
of a stream you have a packer and instead of streaming objects you pack objects.
The most striking similarity with the iostream library is the use of the left 
shift operator `<<` for packing and the right shift operator `>>` for unpacking. 

Currently there are two sets of packers. The StreamPacker / StreamUnpack and 
the MemoryPacker / MemoryUnpacker. These pack and unpack respectively to a 
iostream or memory (std::vector<char>). By using or extending the stream packer 
you can basically pack to anywhere.

The term packing is used instead of serialisation because serialisation is a 
general term that describes many scenarios, including iostreams. By removing the
word specific predefined notions can be removed.

## Packing Simple Data

Packing simple data is completely trivial:

    std::vector<char> buffer;
    musli::MemoryPacker packer(buffer);
    
    int some_int = 1337;
    float some_float = 13.37f;
    std::string some_string = "Hello World!";
    std::map<std::string, std::vector<unsinged int> > some_large_container =
        create_some_large_container();
    
    packer << some_int << some_float << some_string << some_large_container;
    
Unpacking is as simple:

    int some_int;
    float some_float;
    std::string some_string;
    std::map<std::string, std::vector<unsinged int> > some_large_container;

    musli::MemoryUnpacker unpacker(buffer);
    unpacker >> some_int >> some_float >> some_string >> some_large_container;

## Packing Your Objects

If you noticed a similarity to the iostream library, now you will really see it.

If you have a object say:

    class MyObject
    {
    public:
        void set_a(unsigned int value);
        unsinged int get_a() const;
        
        void set_b(unsigned int value);
        unsigned int get_b() const;
    private:
        unsinged int a;
        unsigned int b;
    };

Adding packing is simple:

    musli::Packer& operator << (musli::Packer& packer, const MyObject& object)
    {
        packer << object.get_a() << object.get_b();
        return packer;
    }
    
And unpacking:

    musli::Unpacker& operator >> (musli::Unpacker& unpacker, MyObject& object)
    {
        unsigned int a, b;
        packer >> a >> b;
        object.set_a(a);
        object.set_b(b);
        return packer;
    }
    
Of course you can also use a friend declaration to access the private members,
just like the iostream library.

# Packing Pointers

Packing pointers to non polymorphic objects is as simple. You can have almost 
any object layout. This includes directed graphs, acyclic graphs and cyclic 
graphs. The only limitation there is, is that the pointer has to point into heap 
memory and point to the head of an object. (These restrictions might be removed
in the future.)

# Packing Polymorphic Objects

The only extra work you have to do is when you have polymorphic objects. That is
objects that contain virtual methods and may be handled by the base class. In 
these cases you need to expose your class the library by defining a factorlet.

Factorlets are small factory objects, that register themselves to the main musli
factory. This is done automatically, so you only have to define it somewhere in 
your code, like so:

    musli::Factorlet<MyType> my_type_factorlet;

## Caveats

There are a few minor caveats you need to consider. 

First and foremost, I must repeat the limitation to pointers. You must ensure that
that all pointers reference into the heap and to the head of an object. 

Second, you can't unpack constant objects, that is references and constant 
pointers. This limitation is inherent in the C++ language.

Third, there is a minor deficiency in MemoryPacker. As a result you can't create
the packer and unpacker at the same time for the same buffer. This was resolved
because this is not a real use case. See MemoryPackerTest.cpp for a workaround.

