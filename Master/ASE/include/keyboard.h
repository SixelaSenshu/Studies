#ifndef _KEYBOARD_HEADER_
#define _KEYBOARD_HEADER_

#include "minilib.h"
#include "context.h"
#include "irq.h"

#define SIZE_BUFFER_KEYBOARD 100

char get_keyboard_input();

char keyboard_map(unsigned int scancode);

void write_keyboard();

void flush_keyboard();

char getc();

#endif // !_KEYBOAR_HEADER_