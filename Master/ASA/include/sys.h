#ifndef _SYSCALL_HEADER_H_
#define _SYSCALL_HEADER_H_

#include "user.h"
#include "macro.h"
#include "idt.h"
#include "ioport.h"
#include "ctx.h"
#include "mmu.h"

/**
 *######################################################################
 *#                                                                    #
 *#                                Macro                               #
 *#                                                                    #
 *######################################################################
 */

#define SYS_PUTS            0
#define SYS_PUTC            1
#define SYS_CLEAR_SCREEN    2
#define SYS_GET_PID 		3
#define SYS_PUTUD           4
#define SYS_PUTHEX          5
#define SYS_YIELD           6
#define SYS_FORK  			7

#ifndef NULL
#define NULL ((void*)0)
#endif

extern void __assert__(int x, char *f, unsigned line);
#define assert(x) __assert__(x, __FILE__, __LINE__) 

/**
 *######################################################################
 *#                                                                    #
 *#                             Prototypes                             #
 *#                                                                    #
 *######################################################################
 */

/*******************************************       Func display      **/
/**
 * @brief 
 * 
 */

void kclear_screen();	

/**
 * @brief 
 * 
 * @param aChar 
 * @return * void 
 */

/**
 * @brief 
 * 
 * @param aChar 
 */
void kputc(char aChar);	

/**
 * @brief 
 * 
 * @param aString 
 */
void kputs(char *aString);

/**
 * @brief 
 * 
 * @param aNumber 
 */
void kputhex(unsigned aNumber);	

/**
 * @brief 
 * 
 * @param aNumber 
 * @return * void 
 */
void kputud(unsigned aNumber);      

/*******************************************       Func sys      **/

/**
 * @brief 
 * 
 * @return int 
 */
int kgetpid();

/**
 * @brief 
 * 
 */
void kyield();

/**
 * @brief 
 * 
 * @return int 
 */
int kfork();

/*******************************************       Handler      **/

/**
 * @brief 
 * 
 * @param r 
 */
void sys_call_handler_irq(int_regs_t *r);

#endif // !_SYSCALL_HEADER_H_