#ifndef _IRQ_HEADER_
#define _IRQ_HEADER_
#include "sem.h"
#include "idt.h"
#include "minilib.h"
#include "context.h"
#include "ioport.h"
#include "keyboard.h"

void empty_irq(int_regs_t *r);

void time_handler_irq(int_regs_t *r);

void keyboard_handler_irq(int_regs_t *r);

#endif // !_IRQ_HEADER_