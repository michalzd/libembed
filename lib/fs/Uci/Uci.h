/* 
 *  UCI    (U)Micro Configuration Interface
 * Author: mimi
 *
 * Created  luty 2019
 * License: GNU General Public License v3.0 
 *          <https://www.gnu.org/licenses/lgpl.html>
 */


#ifndef FS_UCI_H
#define FS_UCI_H

#include <fstream>
#include "String/StringBuffer.h"

#define  UCI_DIRECTORY_NAME_MAX_SIZE        16
#define  UCI_CONFIG_FILE_NAME_MAX_SIZE      16
#define  UCI_CONFIG_FILE_FULLNAME_MAX_SIZE  24
#define  UCI_SECTION_LINE_MAX_SIZE          64
#define  UCI_SECTION_NAME_MAX_SIZE          24
#define  UCI_DOMAIN_NAME_MAX_SIZE            8
#define  UCI_KEY_NAME_MAX_SIZE              16

typedef uint8_t uci_status;

namespace fs
{
    
    
    class Uci 
    {
    public:
      
        enum Status{
          UCI_OK = 0,
          UCI_ERR_MEM,
          UCI_ERR_INVAL,
          UCI_ERR_NOTAVAILABLE,
          UCI_ERR_NOTFOUND,
          UCI_ERR_IO,
          UCI_ERR_PARSE,
          UCI_ERR_DUPLICATE,
          UCI_ERR_UNKNOWN,
          UCI_ERR_LAST
        };
        
        struct Ctx{
            char   config [UCI_CONFIG_FILE_NAME_MAX_SIZE];
            char   section[UCI_SECTION_NAME_MAX_SIZE];
            char   domain [UCI_DOMAIN_NAME_MAX_SIZE]; 
            char   option [UCI_KEY_NAME_MAX_SIZE]; 
        };

      
        Uci();
        Uci(const char * directory);
        virtual ~Uci();

        /* open/close uci file */
        uci_status  open(const char * uci_config_file, bool mode_write = false);
        void        close()           { file.close();          };
        bool        available() const { return (file.is_open() && !file.eof() ); };  
        
        // read file 
        uci_status  setPosition(uint32_t pos);
        uint32_t    getPosition();
        
        uint8_t     readLn(char *buffer, uint8_t buffer_size);
        uint8_t     readLn(emm::String & line);
        
        uci_status  getContext(struct Ctx &ctx, const char * contextstr);
        
    protected:
        std::fstream  file;
        uint32_t      filesize;
        char          path[UCI_DIRECTORY_NAME_MAX_SIZE];
        uint32_t      status;
    
    protected: // methods:
        void        _setdir(const char * directory);
        uint32_t    _getfilesize();
        uint8_t     _readBytesUntil(char terminator, char *buffer, uint8_t length);
        
    };

}   // namespace fs

#endif /* UCI_H */

