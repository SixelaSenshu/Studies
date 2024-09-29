#include "gdt.h"
#include "idt.h"
#include "minilib.h"
#include "irq.h"

extern void app_main(void);

/* multiboot entry-point with datastructure as arg. */
void main(unsigned int * mboot_info)
{
    /* clear the screen */
    clear_screen();
    puts("Early boot.\n"); 

    /* Initialize the memory */
    puts("\t-> Setting up the GDT... ");
    gdt_init_default();
    puts("OK\n");

    /* Initializa the Interrupt Descriptor Table */
    puts("\t-> Setting up the IDT... ");
    setup_idt();
    puts("OK\n");

    puts("\n\n");

    /* Installs two empty handlers for the timer (0) and the keyboard (1) */
    idt_setup_irq_handler(0, empty_irq);
    idt_setup_irq_handler(1, empty_irq);

    /* Enables interrupts */ 
    __asm volatile("sti");

    /* minimal setup done ! */
    app_main();
    
    puts("Going idle\n");
    for(;;) ; /* nothing more to do... really nothing ! */
}


