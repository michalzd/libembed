/* 
 *  UCI    (U)Micro Configuration Interface
 * Author: mimi
 *
 * Created  luty 2019
 * License: GNU General Public License v3.0 
 *          <https://www.gnu.org/licenses/lgpl.html>
 */

#include "UciSection.h"
#include "debug_print.h"

#include <iostream>

using namespace fs;

static const char   identyfikator[] = "config ";
static const size_t identyfikatorLen = sizeof(identyfikator) - 1;
static const char   tokenDelimiter   = ' ';
static const char   commentDelimiter = ';';

emm::StringBuffer<UCI_SECTION_LINE_MAX_SIZE> UciSection::line;


UciSection::UciSection(Uci& uci_) 
{
    this->uci = &uci_;
    this->begpos = 0;
    this->endpos = 0;
    this->optpos = 0;
    this->name.clear();
}

UciSection::UciSection(const UciSection& orig) 
{
    this->uci = orig.uci;
    this->begpos = orig.begpos;
    this->endpos = orig.endpos;
    this->optpos = 0;
    this->name.clear();
}

UciSection::~UciSection() {
    this->begpos = 0;
    this->endpos = 0;
    this->optpos = 0;
    this->name.clear();
}


uci_status 
UciSection::getNext()
{
    uint32_t currpos;
    
    this->name.clear();
    
    if(!uci->available() ) return Uci::Status::UCI_ERR_NOTAVAILABLE;
    uci->setPosition(this->begpos);
    this->endpos =0;
    
    size_t n = _getsectionline(line);    
    if(n) { 
        _setName(line);
        currpos = uci->getPosition();
        this->begpos = currpos;   
        n = _getsectionline(line);
        currpos = uci->getPosition();
        this->endpos = currpos - n;
        this->endpos--;
    }
    
    if(this->begpos == 0) return Uci::Status::UCI_ERR_NOTFOUND;
    return Uci::Status::UCI_OK;
    
}


const char *
UciSection::getName() const
{
    return name.c_str();
}

uci_status 
UciSection::find(const char* section_name) 
{
    uint32_t currpos;
    
    this->name.clear();
    this->begpos = 0;
    this->endpos = 0;
    
    uci->setPosition(0);
    if(!uci->available() ) return Uci::Status::UCI_ERR_NOTAVAILABLE;
    size_t n=1;
    size_t len = emm::String::length(section_name);
    while(n) {
        n = _getsectionline(line);
        currpos = uci->getPosition();
        if( n && _comparename(line, section_name, len) ) {
            _setName(line);
            this->begpos = currpos;   
            n = _getsectionline(line);
            currpos = uci->getPosition();
            this->endpos = currpos - n;
            this->endpos--;
            break;
        }       
    }
    if(this->begpos == 0) return Uci::Status::UCI_ERR_NOTFOUND;
    return Uci::Status::UCI_OK;
    
}


const char *
UciSection::getNextOption(const char * domain)
{
    uint32_t currpos = this->nxoptpos;
    this->optpos = 0;
    uci->setPosition(currpos);
    if(!uci->available() ) return nullptr;
    const char * optionln = nullptr;
    size_t delimiterpos;  
    
    line.clear();
    while( uci->available() && currpos < (this->endpos) ) {
        currpos = uci->getPosition();
        _readLn(line);
        delimiterpos = line.find(tokenDelimiter);
        if(delimiterpos && _comparekeydomain(line, domain) ) { 
            this->optpos = currpos;
            optionln = line.c_str();   
            break;            
        }         
    }
    this->nxoptpos = uci->getPosition();
    return optionln;
    
}


/* zwraca wartosc wg nazwy klucza w sekcji
 */
const char* 
UciSection::getValue(const char* key_name) 
{
    uci->setPosition(this->begpos);
    if(!uci->available() ) return nullptr;
    return _getoptionvalue( _findoption( line, key_name) ); 
}


emm::String &
UciSection::getValue(emm::String & key_value, const char* key_name) 
{
    key_value = getValue(key_name);  
    return key_value;
}

//uci_status 
//UciSection::setValue(const char* key_name, const char* key_value) 
//{
//    emm::StringBuffer<UCI_SECTION_LINE_MAX_SIZE> optionline;
//    
//    uci->setPosition(this->begpos);
//    if(!uci->available() ) return Uci::Status::UCI_ERR_NOTAVAILABLE;
//    _findoption( line, key_name);
//    if(line.size()==0) return Uci::Status::UCI_ERR_NOTFOUND;
//    optionline =  key_name;
//    optionline += "  ";
//    optionline += key_value; 
//    
//    print(" jest ");
//    print( (int)optpos);
//    print(' ');
//    print( (int)nxoptpos);
//    print(' ');
//    print( line.c_str());
//    print(' ');
//    println( optionline.c_str() );
//    
//    return Uci::Status::UCI_OK;
//}
//
//uci_status 
//UciSection::addOption(const char* key_name, const char* key_value) 
//{
//    uint32_t newpos;
//    emm::StringBuffer<UCI_SECTION_LINE_MAX_SIZE> optionline;
//    uci->setPosition(this->begpos);
//    if(!uci->available() ) return Uci::Status::UCI_ERR_NOTAVAILABLE;
//    optionline =  key_name;
//    optionline += "  ";
//    optionline += key_value; 
//    newpos = this->endpos;
//    
//    print(" addOption ");
//    print( (int)optpos);
//    print(' ');
//    print( (int)nxoptpos);
//    print(' ');
//    print( (int)newpos);
//    print(' ');
//    
//    println( optionline.c_str() );
//    
//    return Uci::Status::UCI_OK;
//}



uint8_t 
UciSection::_readLn(emm::String& ln) 
{
    uci->readLn( const_cast<char*>( ln.c_str() ), ln.max_size() );
    ln.length();
    ln.trimLeft();
    // erase comment from line if exist
    size_t delimiterpos = ln.find(commentDelimiter);
    if(commentDelimiter) ln.erase(delimiterpos);
    ln.trimRight();
    return ln.size();
}



/* zwraca linię rozpoczynającą kolejne sekcje
 * jako return value jest ilość znaków w linii pomijając znak \n
 */
size_t 
UciSection::_getsectionline( emm::String & ln ) 
{
    size_t n=0; 
    ln.clear();
    while( uci->available() ) {
        n = _readLn(ln);
        if( ln.compare(identyfikator, 0, identyfikatorLen) ) break;
    }
    return n;
}


emm::String &
UciSection::_findoption(emm::String& tokenln, const char* key_name) 
{
    const char* option; 
    bool iskey = false;
    emm::String  key(key_name);  
    
    option = getFirstOption();
    while(option) {
        iskey = _comparekey( tokenln, key ); 
        if(iskey) break;   
        option = getNextOption();
    }
    if(!iskey) tokenln.clear();    
    return tokenln;
}



void 
UciSection::_setName(emm::String& ln) 
{
    this->name = ln.c_str() + identyfikatorLen;
    name.trimLeft();
    name.trimRight();
}


/* porównuje nazwę sekcji
 */
bool 
UciSection::_comparename(emm::String & section_ln, const char* section_name, size_t namelen) 
{
    size_t namefirstchar;
    char c;
    namefirstchar = section_ln.find(section_name, identyfikatorLen);
    if(namefirstchar == emm::String::npos) return false;
    c = section_ln.at(namefirstchar + namelen);
    if( c!=0 && c!=' ') return false;
    return true;
}


/* sprawdza, czy token zawiera nazwę klucza
 */
bool
UciSection::_comparekey(emm::String& tokenln,  emm::String & key)
{
    if( !key.compare( tokenln.c_str(), 0, key.size() ) ) return false;
    char nextc = tokenln.at( key.size() );
    if(nextc==' ' or nextc==tokenDelimiter) return true;
    return false;
}

/*  sprawdza, czy nazwa opcji (klucz) zaczyna się podaną domeną
 */
bool
UciSection::_comparekeydomain(emm::String& tokenln, const char* domain) 
{
   if(domain==nullptr) return true;
   size_t len = emm::String::length(domain);
   if(!tokenln.compare(domain, 0, len)) return false;
   if( tokenln.at(len) != '.') return false;
   return true;
}


/* odcina ze stringu wartosc 
 */
const char *
UciSection::_getoptionvalue(emm::String& optionln)
{
    const char* value = nullptr;
    if(optionln.size()) {
        size_t delimiterpos = optionln.find(tokenDelimiter);
        if(delimiterpos== emm::String::npos) delimiterpos = 0;
        value = optionln.c_str() + delimiterpos + 1;
        value = emm::String::cstrtrim( value ); 
    }    
    return value;
}


