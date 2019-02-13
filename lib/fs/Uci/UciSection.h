/* 
 *  UCI    (U)Micro Configuration Interface
 * Author: mimi
 *
 * Created  luty 2019
 * License: GNU General Public License v3.0 
 *          <https://www.gnu.org/licenses/lgpl.html>
 */

#ifndef UCISECTION_H
#define UCISECTION_H

#include <stddef.h>
#include "fs/Uci/Uci.h"
#include "String/TokenString.h"
#include "String/TokenBuffer.h"

namespace fs
{
    
    class UciSection
    {
            
    public:
      UciSection (Uci&  uci_);
      UciSection (const UciSection& orig);
      virtual ~UciSection ();
      
      // section
      uci_status    getNext();
      uci_status    getFirst()     { this->begpos; return getNext(); }
      uci_status    find(const char * section_name);
      const char *  getName() const; 
      
      // option in section
      const char *  getNextOption (const char * domain);
      const char *  getFirstOption(const char * domain) {  this->nxoptpos = this->begpos; return getNextOption(domain); }
      const char *  getNextOption ()   {  return getNextOption( nullptr); }
      const char *  getFirstOption()   {  this->nxoptpos = this->begpos; return getNextOption(nullptr); }
      
      const char  *  getValue(const char * key_name);
      emm::String &  getValue(emm::String & key_value, const char * key_name);
      
      //uci_status    setValue(const char * key_name, const char * key_value);      
      //uci_status    addOption(const char * key_name, const char * key_value);
      
    protected:
      Uci * uci;
      uint32_t  begpos;
      uint32_t  endpos;
      uint32_t  optpos;
      uint32_t  nxoptpos;
      
      emm::StringBuffer<UCI_SECTION_NAME_MAX_SIZE>        name;
      static emm::StringBuffer<UCI_SECTION_LINE_MAX_SIZE> line;
      
      uint8_t        _readLn (emm::String & ln);
      void           _setName(emm::String & ln);
      size_t         _getsectionline( emm::String & ln);
      emm::String &  _findoption(emm::String & tokenln, const char * key_name);
      const char *   _getoptionvalue(emm::String & optionln);
      
      bool    _comparename(emm::String & section_ln, const char * section_name, size_t namelen);
      bool    _comparekey (emm::String & tokenln, emm::String & key);
      bool    _comparekeydomain(emm::String & tokenln, const char * domain);
      
    };
  
} // namespace fs

#endif /* UCISECTION_H */

