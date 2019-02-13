/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: mimi
 *
 * Created on 13 lutego 2019, 09:26
 */

#include <cstdlib>
#include <iostream> 

#include "debug_print.h"


#include "String/String.h"
#include "String/StringBuffer.h"

using namespace std;


void test_replace(emm::String & mystring);

/* 
 * test template < size_t __size > class StringBuffer
 * 
 * uzycie wzorca klasy StringBuffer 
 * wymaga dołączenia tylko "String/StringBuffer.h"
 * 
 */
void test_class_StringBuffer()
{
    emm::StringBuffer<64> mystring("utworzony za pomoca konstruktora");
    std::cout << mystring.max_size() << ", " << mystring.length() <<  std::endl;
    std::cout << "123456789012345678901234567890123456789" << std::endl;
    std::cout << mystring.c_str () << std::endl;
    
    emm::StringBuffer<64> sndstring(mystring);
    sndstring = "wartosc podana operatorem przypisania";
    std::cout << sndstring.max_size() << ", " << sndstring.length() <<  std::endl;
    std::cout << "123456789012345678901234567890123456789" << std::endl;
    std::cout << sndstring.c_str () << std::endl;
   
}

/* 
 * test class String
 */
void test_class_String()
{
    // obiekt klasy String
    // kontruktor inicjuje tylko wkaznik na podany string
    // brak kopiowania oraz własnego bufora
    char externalbuff[] = "utworzony w buforze jako zmienna lokalna";
    
    emm::String mystring(externalbuff);
    std::cout << mystring.max_size() << ", " << mystring.length() <<  std::endl;
    std::cout << "123456789012345678901234567890123456789" << std::endl;
    std::cout << mystring.c_str () << std::endl;
    
    test_replace(mystring);
    std::cout << mystring.max_size() << ", " << mystring.length() <<  std::endl;
    std::cout << "123456789012345678901234567890123456789" << std::endl;
    std::cout << mystring.c_str () << std::endl;
    
    mystring.erase(10);
    std::cout << mystring.max_size() << ", " << mystring.length() <<  std::endl;
    std::cout << "123456789012345678901234567890123456789" << std::endl;
    std::cout << mystring.c_str () << std::endl;
     
}



void test_replace(emm::String & mystring)
{
    mystring.replace(2, 'X');
    mystring.replace(0, 'y', 'Y');
}


void test_staticstring_two ()
{
//    std::cout << "test static string" << std::endl;
//    
//    mm::StringBuffer<64> mystring("  utworzony za pomoca   ");
//    
//    std::cout << mystring.max_size() << ", " << mystring.size() <<  std::endl;
//    std::cout << "12345678901234567890123456789012" << std::endl;
//    std::cout << mystring.c_str () << '.' << std::endl;
//    
//    std::cout << "trim string" << std::endl;
//    
//    mystring.trimLeft();
//    std::cout << mystring.max_size() << ", " << mystring.size() <<  std::endl;
//    std::cout << "12345678901234567890123456789012" << std::endl;
//    std::cout << mystring.c_str () << '.' << std::endl;
//    
//    mystring.trimRight();
//    std::cout << mystring.max_size() << ", " << mystring.size() <<  std::endl;
//    std::cout << "12345678901234567890123456789012" << std::endl;
//    std::cout << mystring.c_str () << '.' << std::endl;
//    
//    mystring.replace(2, 'X');
//    mystring.replace(0, 'y', 'Y');
//    std::cout << mystring.max_size() << ", " << mystring.size() <<  std::endl;
//    std::cout << "12345678901234567890123456789012" << std::endl;
//    std::cout << mystring.c_str () << '.' << std::endl;
//    
//    mystring.erase(10);
//    std::cout << mystring.max_size() << ", " << mystring.size() << ", " << mystring.length() << std::endl;
//    std::cout << "12345678901234567890123456789012" << std::endl;
//    std::cout << mystring.c_str () << '.' << std::endl;
//    
//    
    
//    size_t idx = 0;
//    
//    idx = mystring.find("pomoca"); 
//    
//    
//    std::cout << "find " << idx << " cmp" << mystring.compare("pomoca", idx) << std::endl;
//    std::cout << "    cmp" << mystring.compare("utworzony za pomoca konstruktor") << std::endl;
//    
    
}

void test_staticstring_three()
{
//    char ss[] = "to string staly do ucinania";
//    mm::String  mystring(ss);
//    
//    std::cout << mystring.max_size() << ", " << mystring.size() << ", " << mystring.length() << std::endl;
//    std::cout << "12345678901234567890123456789012" << std::endl;
//    std::cout << mystring.c_str () << '.' << std::endl;
//    
//    //mystring.trimLeftTo(3);
//    //std::cout << mystring.c_str () << '.' << std::endl;
//    
//    //mystring.trimRightFrom(10);
//    //std::cout << mystring.c_str () << '.' << std::endl;
//    
//    size_t idx = 0;
//    
//    idx = mystring.find('s', 0); 
//    std::cout << "find " << idx << std::endl;
//    
//    idx = mystring.find('s', ++idx); 
//    std::cout << "find " << idx << std::endl;
//    
//    idx = mm::String::indexof(ss, 's');
//    std::cout << "find " << idx << std::endl;
//    
//    //std::cout << " cmp"  << mystring.compare("pomoca", idx) << std::endl;
//    //std::cout << "    cmp" << mystring.compare("utworzony za pomoca konstruktor") << std::endl;
//    
}





/*
 * 
 */
int main(int argc, char** argv) {

    test_class_StringBuffer();
    test_class_String();
    
    return 0;
}

