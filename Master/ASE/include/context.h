#ifndef _CONTEXT_H_
#define _CONTEXT_H_

/***************************************************************
 * 
 *                          Include
 * 
 ***************************************************************
*/

#include "minilib.h"
#include "macro.h"
#include "list.h"

/***************************************************************
 * 
 *                          Macro
 * 
 ***************************************************************
*/

#define SIZE_CTX 10

#define WAIT_1SEC 1000000
#define WAIT() for (uint32_t i = 0; i < WAIT_1SEC; i++){}


/***************************************************************
 * 
 *                          Typedef
 * 
 ***************************************************************
*/

typedef int(* funct_int)(int);
typedef void(*funct_void)(void *);
typedef char(*funct_char)(char);
typedef unsigned int size_t;
typedef struct ctx_s
{
    void * esp;
    void * ebp;
    int isLaunched;
    funct_void funct; 
    void *args;
    int stack[STACK_SIZE];
    struct list_head ctx_head;
} ctx_s;


typedef struct ctx_l
{
    struct ctx_s ctx[SIZE_CTX];
    int nb_ctxs;
    int last;
}ctx_l;

/***************************************************************
 * 
 *                          Extern
 * 
 ***************************************************************
*/


extern struct list_head head;
extern int value;

/***************************************************************
 * 
 *                          Try & Throw
 * 
 ***************************************************************
*/

int try(ctx_s *ctx, funct_int f, int arg);

int throw(ctx_s * ctx, int r);

/***************************************************************
 * 
 *                          Switch_context
 * 
 ***************************************************************
*/


void init_ctx(struct ctx_s * newcontext,  funct_void f, void *args);

void switch_context(struct ctx_s * restored_ctx);

void print_context(ctx_s *ctx);

/***************************************************************
 * 
 *                          Scheduler
 * 
 ***************************************************************
*/

int create_ctx(funct_void f, void *args);

void yield();


#endif // !_CONTEXT_H_