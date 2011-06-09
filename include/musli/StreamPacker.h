// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#ifndef _MUSLI_STREAM_PACKER_H_
#define _MUSLI_STREAM_PACKER_H_

#include "Packer.h"

#include <iosfwd>

namespace musli
{
    /**
     * Implementation of a Packer that packs to std::ostream.
     **/
    class StreamPacker : public Packer
    {
    public:
        /**
         * Constructor
         *
         * @param stream the stream to pack to
         **/
        StreamPacker(std::ostream& stream);
        
        /**
         * Destructor
         **/
        ~StreamPacker();
    
    protected:
        
        virtual void write(const char* data, unsigned int size);
        
    private:
        std::ostream& stream;
    };
}

#endif
