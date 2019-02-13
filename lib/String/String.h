/* 
 * File:   String.h
 *         String class for embedded systems  
 * Author: mimi
 * Created on luty 2019
 * 
 * License: GNU General Public License v3.0 
 *          <https://www.gnu.org/licenses/lgpl.html>
 */

#ifndef MM_STRING_BASE_CLASS_H
#define MM_STRING_BASE_CLASS_H

#include <stddef.h>
#include <stdint.h>

#include <iostream>

namespace emm
{

    class String {
          
    protected:
        char * ptr; 
        size_t buffer_size;
        size_t len;
        
        
    public:
        String(char * buf_ptr, size_t  buf_size); 
        String(const char * buf_ptr);
          
        //  Returns the size() of the largest possible %string.
        size_t  max_size() const  { return this->buffer_size; }
        size_t  capacity() const  { return this->buffer_size; }
        
        //  Returns the number of characters in the string, not including any
        //  null-termination.
        size_t  length();
        size_t  size()             { return this->len; }
        
        // Return const pointer to null-terminated contents.
        const char * c_str() const { return this->ptr; }
        char *       data()        { return this->ptr; }
        
        // Erases the string, making it empty.
        void    clear();
        String& erase(size_t at);
        
        // String operations:
        
        // Returns true if the string is empty.  
        bool    empty() const     { return (*ptr == 0); }
        // Returns first character in the string
        char    begin() const     { return (*ptr); }    
        
        // Returns first character in the string
        char    end() const       { return ( *(ptr + len) ); }    
        
        // Provides access to the data contained in the %string.
        // param __n The index of the character to access.
        char    at( size_t pos) const;
        
        // Set value to contents of a C string.
        String&   assign(const char* cstr);
        String&   assign(size_t pos, char c);
        
        // copy c string to char until
        // String&   assign(const char* cstr, char until);
        
        
        // Append a C substring.
        // @param cstr  The C string to append.
        // @param n     The number of characters to append.
        // @return  Reference to this string.
        String&   append(const char * cstr, size_t n);
        String&   append(const char * cstr);
        String&   append(char c);
        
        //  Append a string to this string.
        //  @param string  The string to append.
        //  @return        Reference to this string.
        String&   append(const String&  string)  { return append( string.c_str() ); }
        
        // remove specyfing chars
        void trimLeft( char c);
        void trimRight(char c); 
        
        // remove chars into position
        void trimLeftTo( size_t n);
        void trimRightFrom(size_t n)    { if(n) erase(--n);    }; 
        
        // remove space chars 
        void trimLeft()     { trimLeft(' ');  }
        void trimRight()    { trimRight(' '); }
        
        // replace char in string
        // @param  at  start at position
        // @param  f   replace first occurrence of this char
        // @param  pos replace char in this position
        // @param  c   replacement char
        String&  replace(size_t at, char f, char c);
        String&  replace(size_t pos, char c);
        
        
        // Find content in string
        // The first character is denoted by a value of 0 (not 1)
        size_t  find (const char* cstr, size_t pos = 0) const;
        size_t  find (char c, size_t pos = 0) const;
        
        // compare strings
        bool    compare(char  c, size_t pos = 0) const;
        bool    compare(const char* cstr, size_t pos = 0) const;
        bool    compare(const char* cstr, size_t pos, size_t n) const;
        
        // operators
        String&   operator= (char c)                { return assign(1, c); }
        String&   operator= (const char * cstr)     { return assign(cstr); }
        String&   operator= (const String & string) { return assign(string.c_str()); }
          
        String&   operator+= (char c)               { return append(c); }
        String&   operator+= (const char * cstr)    { return append(cstr); }
        String&   operator+= (const String & string){ return append(string); } 
        
        inline bool operator== (const char* cstr)    { return compare(cstr); }
        inline bool operator== (const String & rhs)  { return compare(rhs.c_str()); }
        
    protected:
        void    init(const char * cstr); 
        
        static void _copy_chars(char * desc, const char * src, size_t num);
        static void _copy_chars(char * desc, const char * src, char delimiter, size_t num);
        bool        _cmp_chars(const char* cstr, size_t pos = 0) const;
        
        
    public:
        static const size_t npos = -1;
        
        // dodatki operujące na c-stringach
        static size_t       length(const char * src);
        static char *       cstrcopy(char * desc, const char * src, size_t num);
        static char *       cstrappend(char * desc, const char * src, size_t num);
        static char *       cstrtrim(const char * src);
        static size_t       indexof(const char * src, char c);
    };

} // namespace mm 

#endif /* STRING_H */

