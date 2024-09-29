#include "gdt.h"
#include "idt.h"
#include "call_user.h"
#include "irq.h"
#include "user.h"
#include "mmu.h"
#include "ctx.h"
#include "sys.h"

extern void * stack_address_top;
extern Ctx_s * current_ctx;

/* multiboot entry-point with datastructure as arg. */
void main(unsigned int * mboot_info)
{
    /* clear the screen */
    kclear_screen();
    kputs("Early boot.\n"); 

    /* Initialize the memory */
    kputs("\t-> Setting up the GDT... ");
    gdt_init_default();
    kputs("OK\n");

    /* Initialize the Interrupt Descriptor Table */
    kputs("\t-> Setting up the IDT... ");
    setup_idt();
    kputs("OK\n");

    idt_setup_irq_handler(0, time_handler_irq);
    idt_setup_irq_handler(1, empty_irq);

	idt_setup_int_handler(14,page_fault_handler_idt);
	idt_setup_int_handler(87,sys_call_handler_irq);


	init_ctx_s();
	Ctx_s * main_context = alloc_ctx();
	current_ctx = main_context;
	main_context->next = main_context;

    /* Enables interrupts */ 
    __asm volatile("sti");

	/* Initialize The Memory Management Unit */
	kputs("\t-> Setting up the MMU... ");
	setup_mmu();
	kputs("OK\n");
	
    /* minimal setup done ! */
	call_user(user_main,stack_address_top);
    
    kputs("Going idle\n");
    for(;;) ; /* nothing more to do... really nothing ! */
}


