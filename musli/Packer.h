// musli - simple serialisation library
// Copyright (c) 2011 Sean Farrell

#ifndef _MUSLI_PACKER_H_
#define _MUSLI_PACKER_H_

namespace musli
{
    class Packer
    {
    public:
        Packer();
        
        ~Packer();
        
        virtual void pack_bool(bool value) = 0;
        
        virtual void pack_char(char value) = 0;
        
        virtual void pack_unsigned_char(unsigned char value) = 0;
        
        virtual void pack_short(short value) = 0;
        
        virtual void pack_unsigned_short(unsigned short value) = 0;
        
        virtual void pack_int(int value) = 0;
                
        virtual void pack_unsigned_int(unsigned int value) = 0;
        
        virtual void pack_long(long value) = 0;
        
        virtual void pack_unsigned_long(unsigned long value) = 0;
        
        virtual void pack_long_long(long long value) = 0;
        
        virtual void pack_unsigned_long_long(unsigned long long value) = 0;
        
        virtual void pack_float(float value) = 0;
        
        virtual void pack_double(double value) = 0;
        
    private:
        Packer(const Packer&);
        const Packer& operator = (const Packer&);
    };
    
    Packer& operator << (Packer& packer, bool value);
    
    Packer& operator << (Packer& packer, char value);
    
    Packer& operator << (Packer& packer, unsigned char value);
    
    Packer& operator << (Packer& packer, short value);
    
    Packer& operator << (Packer& packer, unsigned short value);
    
    Packer& operator << (Packer& packer, int value);
    
    Packer& operator << (Packer& packer, unsigned int value);
    
    Packer& operator << (Packer& packer, long value);
    
    Packer& operator << (Packer& packer, unsigned long value);
    
    Packer& operator << (Packer& packer, long long value);
    
    Packer& operator << (Packer& packer, unsigned long long value);
    
    Packer& operator << (Packer& packer, float value);
    
    Packer& operator << (Packer& packer, double value);
}

#endif
