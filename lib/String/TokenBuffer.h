/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TokenBuffer.h
 * Author: mimi
 *
 * Created on 3 lutego 2019, 11:27
 */

#ifndef TOKENBUFFER_H
#define TOKENBUFFER_H

#include <stddef.h>
#include <stdint.h>
#include "String/TokenString.h"

namespace emm 
{
    
    template < size_t __size >
    class TokenBuffer : public emm::TokenString
    {
    protected:
        char buffer[__size];
        
    public:
        TokenBuffer()                         : TokenString(buffer, __size)  { }; 
        TokenBuffer(const char * cstr)        : TokenString(buffer, __size)  { init(cstr);  };
        TokenBuffer(const TokenBuffer& orig)  : TokenString(buffer, __size)  { init(orig.c_str()); };
        
        void restore()  { restore (buffer, __size); }
        
        // operators
        String&   operator= (char c)                { return assign(1, c); }
        String&   operator= (const char * cstr)     { return assign(cstr); }
        String&   operator= (const String & string) { return assign(string.c_str()); }
        
    };

}

#endif /* TOKENBUFFER_H */

