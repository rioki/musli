// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#ifndef _MUSLI_MEMORY_UNPACKER_H_
#define _MUSLI_MEMORY_UNPACKER_H_

#include "Unpacker.h"

#include <vector>

namespace musli
{
    /**
     * Implementation of a Unpacker that unpacks from memory.
     **/
    class MemoryUnpacker : public Unpacker
    {
    public:
        /**
         * Constructor
         *
         * @param buffer the buffer to unpack from.
         **/
        MemoryUnpacker(std::vector<char>& buffer);
        
        /**
         * Destructor
         **/
        ~MemoryUnpacker();
        
    protected:
    
        virtual void read(char* data, unsigned int size);
        
    private:
        std::vector<char>& buffer;
        
        std::vector<char>::iterator read_pos;
    };
}

#endif
