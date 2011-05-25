// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#ifndef _MUSLI_MEMORY_PACKER_H_
#define _MUSLI_MEMORY_PACKER_H_

#include "Packer.h"

#include <vector>

namespace musli
{
    /**
     * Implementation of a Packer that packs to memory.
     **/
    class MemoryPacker : public Packer
    {
    public:
        /**
         * Constructor
         *
         * @param buffer the buffer to pack to
         **/
        MemoryPacker(std::vector<char>& buffer);
        
        /**
         * Destructor
         **/
        ~MemoryPacker();
    
    protected:
        
        virtual void write(const char* data, unsigned int size);
        
    private:
        std::vector<char>& buffer;
    };
}

#endif
