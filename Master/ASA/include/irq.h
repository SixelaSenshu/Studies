#ifndef _IRQ_HEADER_
#define _IRQ_HEADER_
#include "idt.h"

/**
 * @brief 
 * 
 * @param r 
 */
void empty_irq(int_regs_t *r);

/**
 * @brief 
 * 
 * @param r 
 */
void time_handler_irq(int_regs_t *r);

#endif // !_IRQ_HEADER_