#include "irq.h"

extern sem_s mutex;

void empty_irq(int_regs_t *r) {
}

void time_handler_irq(int_regs_t *r){
	sem_up(&mutex);
	yield();
	sem_down(&mutex);
}

void keyboard_handler_irq(int_regs_t *r){
	sem_up(&mutex);
	char keycode = get_keyboard_input();
	if(keycode != 0)
		putc(keycode);
	sem_down(&mutex);
}
