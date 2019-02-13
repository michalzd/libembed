/* 
 *  UCI    (U)Micro Configuration Interface
 * Author: mimi
 *
 * Created  luty 2019
 * License: GNU General Public License v3.0 
 *          <https://www.gnu.org/licenses/lgpl.html>
 */

#include "fs/Uci/Uci.h"
#include "String/StringBuffer.h"
#include "String/TokenString.h"

using namespace fs;


Uci::Uci() 
{ 
  _setdir("/etc/");
  status = Uci::Status::UCI_OK;
}

Uci::Uci (const char* directory) 
{
  _setdir(directory);
  status = Uci::Status::UCI_OK;
}



Uci::~Uci() {
  close();
}


void 
Uci::_setdir (const char* directory)
{
    emm::String::cstrcopy(this->path, directory, UCI_DIRECTORY_NAME_MAX_SIZE);
}

/*
 * 
 */
uci_status 
Uci::open(const char * uci_config_file, bool mode_write)
{
    std::ios_base::openmode mode;
    emm::StringBuffer<UCI_CONFIG_FILE_FULLNAME_MAX_SIZE> _ucifile;
    _ucifile = this->path;
    _ucifile += uci_config_file;
    
    mode = std::ios::in;
    if(mode_write) mode = std::ios::in | std::ios::out;
    
    file.open(_ucifile.c_str(), mode);
    if(!file.is_open()) return Uci::Status::UCI_ERR_NOTFOUND;
    filesize = _getfilesize();
    
    return Uci::Status::UCI_OK;
}


/* get context struct from context string
 */
uci_status  
Uci::getContext(struct Ctx &ctx, const char * contextstr)
{
    emm::TokenString argctx(contextstr);
    *ctx.config = 0;
    *ctx.section = 0;
    *ctx.domain = 0;
    *ctx.option = 0;
    if( argctx.size()==0) return Uci::Status::UCI_ERR_INVAL;
    if( argctx.at(0)=='.') return Uci::Status::UCI_ERR_INVAL;
    argctx.setDelimiter('.');
    argctx.getToken(ctx.config,  1, UCI_CONFIG_FILE_NAME_MAX_SIZE);
    argctx.getToken(ctx.section, 2, UCI_SECTION_NAME_MAX_SIZE);
    argctx.getTokens(ctx.domain, 3, UCI_DOMAIN_NAME_MAX_SIZE);
    argctx.getTokens(ctx.option, 3, UCI_KEY_NAME_MAX_SIZE);
    // if option contains delimiter, 
    // get domain from option name
    if( emm::String::indexof(ctx.domain, '.') != emm::String::npos) {
        argctx.getToken(ctx.domain, 3, UCI_DOMAIN_NAME_MAX_SIZE);
    }
    return Uci::Status::UCI_OK; 
}


/* UCI file line 
 */
uint32_t 
Uci::getPosition()
{
    if(not file.is_open() ) return 0;
    if(file.eof()) return filesize;
    return file.tellg();
}

uci_status
Uci::setPosition(uint32_t pos)
{
    if(not file.is_open() ) return Uci::Status::UCI_ERR_NOTAVAILABLE;
    file.clear();
    file.seekp(pos);
    file.seekg(pos);
}


uint8_t  
Uci::readLn(char* buffer, uint8_t buffer_size)
{
    *buffer = 0;
    return _readBytesUntil('\n', buffer, buffer_size);
}

uint8_t Uci::readLn(emm::String & line) 
{
    readLn( const_cast<char*>( line.c_str() ), line.max_size()  ); 
    return line.length();
}




/* 
 */
uint8_t
Uci::_readBytesUntil (char terminator, char* buffer, uint8_t length)
{
  if(length < 1) return 0;
    uint8_t index = 0;
    while(index < length) {
        int c = file.get();
        if(c <= 0 || c == terminator) 
            break;
        *buffer++ = (char) c;
        index++;
    }
    *buffer = 0;
    return index; // return number of characters, not including null terminator
}

uint32_t Uci::_getfilesize() 
{
    file.seekg(0, std::ios::end);
    uint32_t fsize = file.tellg();
    file.seekg(0, std::ios::beg);
    return fsize;
}
