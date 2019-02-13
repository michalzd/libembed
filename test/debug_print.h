/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   debug_print.h
 * Author: mimi
 *
 * Created on 7 lutego 2019, 11:37
 */

#ifndef DEBUG_PRINT_H
#define DEBUG_PRINT_H

#include <iostream> 

static inline void     print( const char * ln)     { std::cout << ln ; }
static inline void     print( char c)              { std::cout << c;   }
static inline void     print( int  n)              { std::cout << n;   }
static inline void     println( const char * ln)   { std::cout << ln << std::endl; }
static inline void     println(int  n)             { std::cout << n << std::endl;  }
static inline void     println()                   { std::cout << std::endl;       }




#endif /* DEBUG_PRINT_H */

