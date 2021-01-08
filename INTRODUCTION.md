# Introduction

The musli library borrows heavily from the iostream library. As a result using 
the musli library should be very simple to adapt for experienced C++ developers. 

## Basic Concepts

Serialization in musli is done with the help of so called Packers. These packers 
wrap a so called box; though boxes are not explicitly modeled. There are 
currently two box types sported, memory (vector<char>) and iosteams. The 
respective packers are SteamPacker and MemoryPacker. Each Packer has a 
respective Unpacker, which is used for unserializing data.

## Simple Objects

Simple objects, such as POD type, string and containers of POD types can 
easily serialized and unserialized. 

If you have to following values:

    unsigned int intvalue;
    float floatvalue; 
    std::vector<std::string> string_list;

You can pack them with the following code:
    
    std::vector<char> buff;
    musli::MemoryPacker packer(buff);
    packer << intvalue << floatvalue << string_list;

The data is not contained within ``buff`` in a compact binary form. To unpack 
the data you need to do the same thing in reverse:

    std::vector<char> buff;
    musli::MemoryUnpacker unpacker(buff);
    unpacker >> intvalue >> floatvalue >> string_list;

## Adding Packing to Custom Objects

Adding packing to your objects or third party objects is really simple, you 
just need to define the ``<<`` and ``>>`` operators:

    class MyClass
    {
    public:
        float get_value1() const;
        
        void set_value1(float vlaue);
        
        float get_value2() const;
        
        void set_value2(float vlaue);
    };
    
    musli::Packer& operator << (musli::Packer& packer, const MyClass& object)
    {
        packer << object.get_value1() << object.get_value2();
        return packer;
    }
    
    musli::Unpacker& operator >> (musli::Unpacker& unpacker, MyClass& object)
    {
        float value1, value2;
        unpacker >> value1 >> value2;
        
        object.set_value1(value1);
        object.set_value1(value2);
        
        return unpacker;
    }

The object of type MyClass can then easily be passed to a packer, like so:

    MyClass object;    
    packer << object;

Obviously you can use all other common techniques, such as a friend function or 
member method taking a packer.

## Pointers

One of the most powerful features of musli is that it can serialize and 
desrialize pointers. No matter what complicated structure you have, it will 
be reproduced. The only requirement here is that the memory is to the heap, 
to the head of the allocated chunk and be only one element. 
This captures about 95% of all pointer use. 

So basically the following code works without any special attention:

    MyObject* object = new MyObject;
    packer << object;
    
    unpacker >> object;
    
Array are special, since there is no way how musli can know the size of the 
array and in many cases even if it is an array. But there is a workaround,
you just need to pass each object to musli separately.

    unsigned int object_count = 5;
    MyObject* objects = new MyObject[object_count];
    
    packer << object_count;
    for (unsigned int i = 0; i < object_count; i++)
    {
        packer << objects[i];
    }
    
Unpacking basically works symmetrically:

    unsigned int object_count;
    unpacker >> object_count;
    
    MyObject* objects = new MyObject[object_count];
    for (unsigned int i = 0; i < object_count; i++)
    {
        unpacker >> objects[i];
    }

Non heap pointers are more difficult to handle, it depends on your scenario. 
You can still serialize the object the pointer points to. But how to regenerate
the pointer is up to you. Once you have the pointer you can deserialize the 
object again.

Polymorphic Objects
-------------------

As you can see most cases are relatively simple and require no special 
interaction. It you have polymorphic objects, this becomes somewhat more
difficult. There are few inherent issues with polymorphic objects, that
make it rather difficult for musli to handle. As a result a few provisions
need to be done. 

The first issue is basically related to how you implement the ``<<`` and ``>>``
operator. Like with iostreams, you need to implement the stream operators 
differently when you want to steam the object while holding a reference to the
base class.

A simple solution is to implement a virtual function that does the actual packing
and have the operators on the base class, like so:  

    class Base
    {
    public:
    
        virtual void pack(musli::Packer& packer) const;
        
        virtual void unpack(musli::Unpacker& unpacker) const;
    };
    
    musli::Packer& operator << (musli::Packer& packer, const Base& object)
    {
        object.pack(packer);   
        return packer;
    }
    
    musli::Unpacker& operator >> (musli::Unpacker& unpacker, Base& object)
    {
        object.unpack(unpacker);   
        return unpacker;
    }

Each derived class not only needs to implement the pack and unpack methods.

The second issue are pointers to polymorphic objects. Here musli must know what
type it needs to create. This is done by defining a factorlet for each derived
type in your cpp file. (Each type you can allocate with new.)

    musli::Factorlet<DerivedTypeA> derived_type_a_factorlet; 
    musli::Factorlet<DerivedTypeB> derived_type_b_factorlet;

**Note:** On windows you need to build musli as a DLL or else the registration
process does not work.
