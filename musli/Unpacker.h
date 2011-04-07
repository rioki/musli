// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#ifndef _MUSLI_UNPACKER_H_
#define _MUSLI_UNPACKER_H_

namespace musli
{
    class Unpacker
    {
    public:
        Unpacker();
        
        ~Unpacker();
        
        virtual bool unpack_bool() = 0;
        
        virtual char unpack_char() = 0;
        
        virtual unsigned char unpack_unsigned_char() = 0;
        
        virtual short unpack_short() = 0;
        
        virtual unsigned short unpack_unsigned_short() = 0;
        
        virtual int unpack_int() = 0;
        
        virtual unsigned int unpack_unsigned_int() = 0;
        
        virtual long unpack_long() = 0;
        
        virtual unsigned long unpack_unsigned_long() = 0;
        
        virtual long long unpack_long_long() = 0;
        
        virtual unsigned long long unpack_unsigned_long_long() = 0;
                
        virtual float unpack_float() = 0;
        
        virtual double unpack_double() = 0;
        
    private:
        Unpacker(const Unpacker&);
        const Unpacker& operator = (const Unpacker&);
    };
    
    Unpacker& operator >> (Unpacker& unpacker, bool& value);
    
    Unpacker& operator >> (Unpacker& unpacker, char& value);
    
    Unpacker& operator >> (Unpacker& unpacker, unsigned char& value);
    
    Unpacker& operator >> (Unpacker& unpacker, short& value);
    
    Unpacker& operator >> (Unpacker& unpacker, unsigned short& value);
    
    Unpacker& operator >> (Unpacker& unpacker, int& value);
    
    Unpacker& operator >> (Unpacker& unpacker, unsigned int& value);
    
    Unpacker& operator >> (Unpacker& unpacker, long& value);
    
    Unpacker& operator >> (Unpacker& unpacker, unsigned long& value);
    
    Unpacker& operator >> (Unpacker& unpacker, long long& value);
    
    Unpacker& operator >> (Unpacker& unpacker, unsigned long long& value);
    
    Unpacker& operator >> (Unpacker& unpacker, float& value);
    
    Unpacker& operator >> (Unpacker& unpacker, double& value);
}

#endif
