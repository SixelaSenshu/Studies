#ifndef __MACRO_H__
#define __MACRO_H__

#include "minilib.h"

#define STACK_SIZE 1024
#define GET_CONTEXT(top, bottom) \
    asm("mov %%esp, %0"          \
        "\n\t"                   \
        "mov %%ebp, %1"          \
        : "=r"(top), "=r"(bottom));
        
#define SET_CONTEXT(top, bottom) \
    asm("mov %0, %%esp"          \
        "\n\t"                   \
        "mov %1, %%ebp"          \
        :                        \
        : "r"(top), "r"(bottom));

#define GET_ESP(top)             \
    asm("mov %%esp, %0"           \
       : "=r"(top));

#define GET_EBP(bottom)          \
    asm("mov %%ebp, %0"           \
       : "=r"(bottom));

#define SET_ESP(top)             \
    asm("mov %0, %%esp"          \
    :                            \
    : "r"(top));  

#define SET_EBP(bottom)          \
    asm("mov %0, %%ebp"          \
    :                            \
    : "r"(bottom))    ;      



#define WRITE_LINE(string)       \
    puts(string);                \
    putc('\n');

#define WRITE_LINE_GET(string,res) \
    res = WRITE_LINE(string)

#endif
