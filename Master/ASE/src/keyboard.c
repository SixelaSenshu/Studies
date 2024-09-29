#include "keyboard.h"

char buffer[SIZE_BUFFER_KEYBOARD];
int size_buffer = 0;

void write_keyboard(){
	for(int i = 0; i < size_buffer; i++){
		putc(buffer[i]);
	}
}

void flush_keyboard(){
	for(int i = 0; i < size_buffer; i++){
		buffer[i] = 0;
	}
	size_buffer = 0;
}

char get_keyboard_input(){
	unsigned char scancode = _inb(0x60);
	unsigned char regis = _inb(0x64);
	char keycode = keyboard_map(scancode);
	if(keycode == '\n'){
		// write_keyboard();
		flush_keyboard();
		return keycode;
	}
	else if(keycode != 0){
		return keycode;
	}else{
		return 0;
	}
}

char keyboard_map(unsigned int scancode){
	char character = 0;
	switch (scancode)
	{
	case 0x1E :
		character = 'q';
		break;
	case 0x30 :
		character = 'b';
		break;
	case 0x2E :
		character = 'c';
		break;
	case 0x20 :
		character = 'd';
		break;
	case 0x12 :	
		character = 'e';
		break;
	case 0x21 :
		character = 'f';
		break;
	case 0x22 :	
		character = 'g';
		break;		
	case 0x23 :
		character = 'h';
		break;
	case 0x17 :
		character = 'i';
		break;
	case 0x24 :
		character = 'j';
		break;
	case 0x25 :	
		character = 'k';
		break;
	case 0x26 :	
		character = 'l';
		break;
	case 0x27 :
		character = 'm';
		break;
	case 0x31 :
		character = 'n';
		break;
	case 0x18 :
		character = 'o';
		break;
	case 0x19 :
		character = 'p';
		break;
	case 0x10 :
		character = 'a';
		break;
	case 0x13 :
		character = 'r';
		break;
	case 0x1F :
		character = 's';
		break;
	case 0x14 :	
		character = 't';
		break;
	case 0x16 :
		character = 'u';
		break;
	case 0x2F :
		character = 'v';
		break;
	case 0x11 :
		character = 'z';
		break;
	case 0x2d :
		character = 'x';
		break;
	case 0x15 :
		character = 'y';
		break;
	case 0x2C :
		character = 'w';
		break;
	case 0x39 :
		character = ' ';
		break;
	case 0x1C :
		character = '\n';
		break;
	default:
		character = 0;
		break;
	}
	if(size_buffer < SIZE_BUFFER_KEYBOARD){
		buffer[size_buffer] = character;
		size_buffer++;
	}
	else{
		for(int i = 0; i < SIZE_BUFFER_KEYBOARD; i++){
			buffer[i] = 0;
		}
		size_buffer = 0;
	}
	return character;

}

char getc(){
	char res = 0;
	while (res == 0)
	{
		res = get_keyboard_input();
	}
	return res; 
}