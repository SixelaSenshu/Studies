#include "ctx.h"
#include "sys.h"
#include "mmu.h"

Ctx_s * current_ctx;
Ctx_s list_ctx[MAX_CTX];
Ctx_s * first_free_ctx;
unsigned int pid;

extern Page_Directory_s page_directories;

void init_ctx_s() {
	pid = 1;
    for (int i = 0; i < MAX_CTX - 1; i++) {
        list_ctx[i].next = &list_ctx[i + 1];
    }
    list_ctx[MAX_CTX - 1].next = NULL;
    first_free_ctx = &list_ctx[0];
}

Ctx_s *alloc_ctx() {
    if (first_free_ctx == NULL) {
        return NULL;
    }
    Ctx_s *ctx = first_free_ctx;
    first_free_ctx = first_free_ctx->next;
    ctx->next = NULL;
    ctx->pid++; 
    return ctx;
}

void free_ctx(Ctx_s *ctx){
	ctx->next = first_free_ctx;
	first_free_ctx = ctx;
}

void switch_context(Ctx_s *ctx){
	irq_disable();
	if(ctx == NULL){
		ctx = alloc_ctx();
        if (ctx != NULL) {
        	ctx->cr3 = clone_page_directory(&page_directories.entries[1]); 
            ctx->next = current_ctx->next;
            current_ctx->next = ctx;
			GET_EBP(ctx->ebp);
			GET_ESP(ctx->esp);
        }
	}else{
		if (current_ctx != NULL)
		{
			GET_EBP(current_ctx->ebp);
			GET_ESP(current_ctx->esp);
			GET_CR3(current_ctx->cr3);
		}
		current_ctx = ctx;
		SET_EBP(current_ctx->ebp);
		SET_ESP(current_ctx->esp);
		SET_CR3(current_ctx->cr3);
	}
	irq_enable();
	end_of_interrupt();
}