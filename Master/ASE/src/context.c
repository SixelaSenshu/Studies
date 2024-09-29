#include "context.h"
#include "idt.h"
#include "list.h"

ctx_s *current_ctx;
ctx_s context;
int value;

struct ctx_l ctx_list = {{}, -1};
LIST_HEAD(head);

/***************************************************************
 *
 *                          Try & Throw
 *
 ***************************************************************
 */

int try(ctx_s *ctx, funct_int f, int arg)
{
    GET_EBP(ctx->ebp);
    GET_ESP(ctx->esp);
    value = f(arg);
    puts("FLAG after f(arg)\n");
    print_context(ctx);
    return value;
}

int throw(ctx_s * ctx, int r)
{
    value = r;
    SET_EBP(ctx->ebp);
    SET_ESP(ctx->esp);
    puts("FLAG after set_context\n");
    print_context(ctx);
    return value;
}

/***************************************************************
 *
 *                          Switch_context
 *
 ***************************************************************
 */

void init_ctx(struct ctx_s *newcontext, funct_void f, void *args)
{
    newcontext->funct = f;
    newcontext->args = args;
    newcontext->isLaunched = 0;
    newcontext->ebp = &newcontext->stack[STACK_SIZE - 4];
    newcontext->esp = &newcontext->stack[STACK_SIZE - 4];
}

void switch_context(struct ctx_s *restored_ctx)
{

    // 1. sauvegardr le contexte dans courant
	irq_disable();
    if (current_ctx != NULL)
    {
        GET_ESP(current_ctx->esp);
        GET_EBP(current_ctx->ebp);
    }

    // 2 . current = ctx
    current_ctx = restored_ctx;
    // 3. restaurer le contexte dans current
    SET_ESP(current_ctx->esp);
    SET_EBP(current_ctx->ebp);
    if (current_ctx->isLaunched == 0)
    {
        current_ctx->isLaunched = 1;
		irq_enable();
		end_of_interrupt();
        current_ctx->funct(current_ctx->args);
    }else{
		irq_enable();
	}
}

void print_context(ctx_s *ctx)
{
    puts("ESP value of the registered context : ");
    puthex((int)ctx->esp);
    puts("\nEBP value of the registered context : ");
    puthex((int)ctx->ebp);
    puts("\nReturned value of the registered context : ");
    puthex(value);
    putc('\n');
}

/***************************************************************
 *
 *                          Scheduler
 *
 ***************************************************************
 */

int create_ctx(funct_void f, void *args)
{
    int old = ctx_list.last;
    ++ctx_list.last;
    struct ctx_s *context = ctx_list.ctx + ctx_list.last;
    init_ctx(context, f, args);
    INIT_LIST_HEAD(&context->ctx_head);
    if (ctx_list.last >= SIZE_CTX - 1)
    {   return 1; // TODO Error
    }
    list_add(&context->ctx_head, &head);
    return 0;
}

void yield()
{
	if(!list_empty(&head)){
		struct ctx_s *headC = list_first_entry(&head, struct ctx_s, ctx_head);
		struct ctx_s *tailC = list_last_entry(&head, struct ctx_s, ctx_head);
		list_move(&headC->ctx_head, &tailC->ctx_head);
		switch_context(headC);
	}
	WAIT();
}
