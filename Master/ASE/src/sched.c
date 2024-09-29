#include "sched.h"
#include "idt.h"
#include "irq.h"

void start_sched(){
	idt_setup_irq_handler(0,time_handler_irq);
	idt_setup_irq_handler(1,keyboard_handler_irq);
}