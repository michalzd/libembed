/* 
 * File:   String.h
 *         String class for embedded systems  
 *         wzorzec klasy definiujący bufor o podanej wielkości  dla stringu
 *         
 * Author: mimi
 * Created on luty 2019
 * 
 * License: GNU General Public License v3.0 
 *          <https://www.gnu.org/licenses/lgpl.html>
 */

#ifndef STATICSTRING_H
#define STATICSTRING_H

#include <stddef.h>
#include <stdint.h>
#include "String/String.h"

#include <iostream>

namespace emm 
{
    /*
     */
    template < size_t __size > 
    class StringBuffer : public emm::String
    {
      
      protected:
        char buffer[__size];
        
      public:
        StringBuffer ()                   : String(buffer, __size)  { };
        StringBuffer (const char * cstr)  : String(buffer, __size)   { init(cstr);  };
        StringBuffer (const String& orig) : String(buffer, __size)   { init(orig.c_str()); };
      
      public:
        // operators
        String&   operator= (char c)                { return assign(1, c); }
        String&   operator= (const char * cstr)     { return assign(cstr); }
        String&   operator= (const String & string) { return assign(string.c_str()); }
          
       // String&   operator+= (char c)               { return append(c); }
       // String&   operator+= (const char * cstr)    { return append(cstr); }
       // String&   operator+= (const String & string){ return append(string); }       
        
    };  
} // namespace mm


#endif /* STATICSTRING_H */

