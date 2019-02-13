/* 
 * File:   String.h
 *         TokenString class for embedded systems  
 *                  
 * Author: mimi
 * Created on luty 2019
 * 
 * License: GNU General Public License v3.0 
 *          <https://www.gnu.org/licenses/lgpl.html>
 */

#include "TokenString.h"
 
using namespace emm;


TokenString::TokenString(char * buf_ptr, size_t  buf_size) 
: String(buf_ptr, buf_size) 
{
    delimiter = ';' ;
}

TokenString::TokenString(const char* buf_ptr) 
: String(buf_ptr)
{
    delimiter = ';' ;
}


TokenString::TokenString(const TokenString& orig) 
: String(orig.ptr, orig.buffer_size)
{
    delimiter = orig.delimiter ;
    init(orig.c_str());
}



void
TokenString::setDelimiter(char token_delimiter)
{
    delimiter = token_delimiter;
}


bool 
TokenString::getToken(emm::String& dest, uint8_t idx)
{
    bool is = false; 
    dest.clear();
    size_t pos = _getposition(idx);
    if(pos != npos) _copy_token( dest.data(), pos, dest.max_size() );
    dest.length();
    return is;
}


bool
TokenString::getToken(char* dest, uint8_t idx, size_t n) 
{
    bool is = false; 
    *dest = 0;
    size_t pos = _getposition(idx);
    if(pos != npos) _copy_token(dest, pos, n);
    return is;
}


bool
TokenString::getTokens(char* dest, uint8_t idx, size_t n) 
{
    bool is = false; 
    *dest = 0;
    size_t pos = _getposition(idx);
    if(pos != npos) {
        if(pos < len)  _copy_chars( dest, (ptr + pos), 0, n ); 
    }
    return is;
}



size_t  
TokenString::_getposition(size_t idx)
{
    size_t pos = 0; 
    while(idx) {
        idx--;
        if(idx==0) break;
        pos = find(delimiter, pos);
        if(pos == npos) break; 
        if( *(ptr + pos) == delimiter) pos++;
    }
    return pos;
}


void 
TokenString::_copy_token(char* desc, size_t pos, size_t n) 
{
    if( *(ptr + pos) == delimiter) pos++;
    if(pos < len)  _copy_chars( desc, (ptr + pos), delimiter, n );
}
