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

#ifndef TOKENSTRING_H
#define TOKENSTRING_H

#include "String/String.h" 

namespace emm 
{

    class TokenString : public emm::String
    {
    protected:
        char    delimiter;
    
    public:
        TokenString(char * buf_ptr, size_t  buf_size);
        TokenString(const char * buf_ptr);
        TokenString(const TokenString& orig);
        
        void setDelimiter(char token_delimiter);
        
        // get token by idx
        // returns true if token available
        bool getToken(emm::String &desc, uint8_t idx);
        bool getToken(char * dest, uint8_t idx, size_t n);
        
        // get all tokens from idx to token string end 
        // returns true if token available
        bool getTokens(char * dest, uint8_t idx, size_t n);
            
        // operators
        String&   operator= (char c)                { return assign(1, c); }
        String&   operator= (const char * cstr)     { return assign(cstr); }
        String&   operator= (const String & string) { return assign(string.c_str()); }
        
    protected:
        size_t  _getposition(size_t idx);
        void    _copy_token(char * dest, size_t pos, size_t n);
        
    };

} // namespace mm

#endif /* TOKENSTRING_H */

