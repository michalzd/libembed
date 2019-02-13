/* 
 * File:   main.cpp
 * Author: mimi
 *
 * Created on 13 lutego 2019
 */

#include <cstdlib>
#include <iostream> 


using namespace std;


/* 
 * test class String
 * test template < size_t __size > class StringBuffer
 */
void test_class_String();
void test_class_StringBuffer();

/*
 * UCI class test
 * UCI command test
 */
int uci_test(int argc, char ** argv);
int uci_command(int argc, char ** argv);


/*
 * 
 */
int main(int argc, char** argv) {

    test_class_StringBuffer();
    test_class_String();
    
    return 0;
}

