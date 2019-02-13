/* 
 * File:   String.h
 *         String class for embedded systems  
 * Author: mimi
 * Created on luty 2019
 * 
 * License: GNU General Public License v3.0 
 *          <https://www.gnu.org/licenses/lgpl.html>
 */

#include "String/String.h"

using namespace emm;


String::String(const char * buf_ptr)
{
  this->ptr = const_cast<char*>(buf_ptr);  
  this->buffer_size = npos - 1;
  this->buffer_size = length(); 
}


String::String(char * buf_ptr, size_t  buf_size)
{
  this->ptr = buf_ptr;
  this->buffer_size = buf_size;
  clear();  
}


size_t 
String::length ()
{
    len = String::length(ptr);
    if( len > buffer_size) len = buffer_size;
    return len;
}


/* Erases the string, making it empty.
 */
void 
String::clear ()
{ 
  erase(0);
  this->len = 0;
}

String& 
String::erase(size_t at) 
{
    if(at < buffer_size) {
        this->len = at;
        for(at; at < buffer_size; at++) {
            ptr[at] = 0; 
        }
    }
    return *this;
}


/* Provides access to the data contained in the %string.
 * param __n The index of the character to access.
 */ 
char 
String::at( size_t n) const
{
  if( n>= buffer_size) return 0;
  return (ptr[n]);
}

/* Set value to contents of a C string.
 */ 
String & 
String::assign(const char* cstr)
{
  erase(0);
  if(cstr) {
      _copy_chars(this->ptr, cstr, this->buffer_size );
      len = length();
  }
  return *this;
}
        

String & 
String::assign(size_t pos, char c)
{
  if(pos < this->buffer_size) {
      this->ptr[pos-1] = c;
      this->ptr[pos] = 0;
  }
  len = length();
  return *this;
}



/* Append a C string
 */
String & 
String::append(const char * cstr, size_t n)
{
  if(len < this->buffer_size) {
      if(n > buffer_size - len)  n = buffer_size - len;
      _copy_chars( ptr + len, cstr, n);
  }
  len = length();
  return *this;
}
  
String & 
String::append(const char * cstr)
{
  if(len < this->buffer_size)  _copy_chars( ptr + len, cstr, buffer_size - len);
  len = length();
  return *this;
}

String & 
String::append(char c)
{
  if(len < this->buffer_size) assign(++len, c);
  len = length();
  return *this;
}

/* remove specyfing char from string 
 */
void
String::trimLeft(char c)
{
    char * p = ptr;
    while( *p == c && *p != 0) p++;
    if(p>ptr) _copy_chars(ptr, p, buffer_size);
    len = length();
}


void 
String::trimRight(char c) 
{
    char * p = ptr + len;
    p--;
    while( *p == c && len > 0) {
        *p = 0;
        p--;
        len--;
    }
}

void 
String::trimLeftTo(size_t n) 
{
    char * p = ptr + n;
    if(p>ptr) _copy_chars(ptr, p, buffer_size);
    len = length();
}


/* Find content in string
 */ 
size_t  
String::find(const char* cstr, size_t pos) const
{
    while( pos <= this->len ) {
        pos = find( *cstr, pos);
        if(pos == npos) break;
        if( _cmp_chars(cstr, pos) ) break;
        pos++;
    }
    if(pos > this->len) pos = npos;
    return pos;
}

size_t  
String::find(char c, size_t pos) const
{
    for(pos; pos <= this->len ; pos++) {
       if( ptr[pos] == c)  break;
    }   
    if(pos > this->len) pos = npos;
    return pos;
}


/* compare one char at position
 * 
 */
bool
String::compare(char c, size_t pos) const
{
    return( ptr[pos] == c);
}

/* compare string
 */ 
bool 
String::compare(const char* cstr, size_t pos) const 
{
    return compare(cstr, pos, npos);
}

bool 
String::compare(const char* cstr, size_t pos, size_t n) const 
{
    bool is = false;
    for(pos; n && (pos <= this->len); pos++) {
        is = ( ptr[pos] == *cstr);
        if(!is)  break;
        if(*cstr ==0) break;
        cstr++;
        n--;
    }   
    return is;
}


/* replace occurrence of char 
 */
String& 
String::replace(size_t at, char f, char c) 
{
    size_t pos = find(f, at);
    if(c && pos < len) {
        ptr[pos] = c;
        if(c==0) length();
    }
    return *this;
}


String& 
String::replace(size_t pos, char c)
{
    pos--;
    if(c && pos < len) {
        ptr[pos] = c;
        if(c==0) length();
    }
    return *this;
}


/*  
 */
char * 
String::cstrcopy(char* desc, const char* src, size_t num)
{
    _copy_chars(desc, src, num);
    return desc;
}


/* ---------------------------------------------------------------------------------------------------- 
 * protected method 
 */

void 
String::init(const char * cstr)
{
    if(cstr) _copy_chars(this->ptr, cstr, this->buffer_size );
    len = length();
}


void 
String::_copy_chars (char* desc, const char* src, char delimiter, size_t num)
{
    if(!src) return;
    while( *src != delimiter) {
        num--;
        if(num == 0) break;
        *desc = *src;
        desc++;
        src++;
        if(*src == 0) break;
    }
    *desc = 0;
}

void 
String::_copy_chars (char* desc, const char* src, size_t num)
{
    if(src) _copy_chars(desc, src, 0, num);
}

bool 
String::_cmp_chars(const char* cstr, size_t pos) const 
{
    bool is = false;
    for(pos; pos <= this->len && *cstr; pos++) {
        is = ( ptr[pos] == *cstr);
        if(!is)  break;
        cstr++;
    }   
    return is;
}

size_t 
String::length(const char* src) 
{
    size_t strlen;
    for(strlen=0; src[strlen] && strlen <= String::npos; strlen++);
    return strlen;
}

char* 
String::cstrtrim(const char * src) 
{
    while( *src==' ') src++;
    return const_cast<char*>(src);
}

size_t 
String::indexof(const char* src, char c) 
{
    size_t pos = npos;
    for(pos = 0; src[pos]; pos++) {
       if( src[pos] == c)  break;
    }   
    if(src[pos]==0) pos = npos;
    return pos;
}
