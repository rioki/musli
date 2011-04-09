// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#ifndef _MUSLI_MEMORY_PACKER_H_
#define _MUSLI_MEMORY_PACKER_H_

#include "Packer.h"

#include <vector>

namespace musli
{
    class MemoryPacker : public Packer
    {
    public:
        MemoryPacker(std::vector<char>& buffer);
        
        ~MemoryPacker();
    
    protected:
        
        virtual void write(const char* data, unsigned int size);
        
    private:
        std::vector<char>& buffer;
    };
}

#endif