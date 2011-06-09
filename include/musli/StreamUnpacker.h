// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#ifndef _MUSLI_STREAM_UNPACKER_H_
#define _MUSLI_STREAM_UNPACKER_H_

#include "Unpacker.h"

#include <iosfwd>

namespace musli
{
    /**
     * Implementation of a Unpacker that unpacks to std::istream.
     **/
    class StreamUnpacker : public Unpacker
    {
    public:
        /**
         * Constrcutor
         *
         * @param stream the stream to unpack from
         **/
        StreamUnpacker(std::istream& stream);
        
        /**
         * Destructor
         **/
        ~StreamUnpacker();
        
    protected:
    
        virtual void read(char* data, unsigned int size);
        
    private:
        std::istream& stream;
    };
}

#endif
