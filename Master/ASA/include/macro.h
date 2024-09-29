#ifndef __MACRO_H__
#define __MACRO_H__

#include "sys.h"

#define STACK_SIZE 1024

#define GET_ESP(top)               \
    asm("mov %%esp, %0"            \
       : "=r"(top));

#define GET_CR3(reg)               \
    asm("mov %%cr3, %0"            \
       : "=r"(reg));

#define GET_EBP(bottom)            \
    asm("mov %%ebp, %0"            \
       : "=r"(bottom));

#define SET_ESP(top)               \
    asm("mov %0, %%esp"            \
    :                              \
    : "r"(top));  

#define SET_CR3(reg)               \
    asm("mov %0, %%esp"            \
    :                              \
    : "r"(reg));  
 

#define SET_EBP(bottom)            \
    asm("mov %0, %%ebp"            \
    :                              \
    : "r"(bottom))    ;      

#define WRITE_LINE(string)          \
    kputs(string);                  \
    kputc('\n');

#define WRITE_LINE_GET(string,res) \
    res = WRITE_LINE(string)

#define PRINTF(string, value)       \
    do {                            \
        kputs(string);				\
        kputs(value);               \
        kputc('\n');                \
    } while(0);

#define PRINTHEX(string, value)     \
    do {                            \
        kputs(string);              \
        kputhex(value);              \
        kputc('\n');                \
    } while(0);

#define WAIT_1SEC 100000000
#define WAIT for (uint32_t i = 0; i < WAIT_1SEC; i++){}
#define WAIT_INFINITE for (uint32_t i = 0; i < 100; i++){WAIT;}

#endif
