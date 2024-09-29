#include "sys.h"

extern Ctx_s * current_ctx;
static unsigned char *video_memory = (unsigned char *) 0xB8000;

static int cursor_x=0;				
static int cursor_y=0;	

void __assert__(int x, char *f, unsigned line)
{
    if (!x) {
        kputs("Assert violated: ");
        kputs("File ");
        kputs(f);
        kputs(" at line ");
        kputud(line);
        for(;;);
    }
}

/*******************************************       Func display      **/


void kclear_screen() {
  int i;
  for(i=0;i<80*25;i++) { 			
    video_memory[i*2+1]=0x0F;		
    video_memory[i*2]=(unsigned char)' '; 
  }
}

void kputs(char *aString) {
  char *current_char=aString;
  while(*current_char!=0) {
    kputc(*current_char++);
  }
}

char *hex_digit="0123456789ABCDEF";
void kputhex(unsigned aNumber) {
  int i;
  int started=0;
  for(i=28;i>=0;i-=4) {
    int k=(aNumber>>i)&0xF;
    if(k!=0 || started) {
      kputc(hex_digit[k]);
      started=1;
    }
  }
  if(!started) kputc('0');
}

void kputud(unsigned aNumber)
{
    char s[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int i = 0;
    while (aNumber > 0) {
        s[i] = '0' + (aNumber % 10);
        i++;
        aNumber /= 10;
    }
    while (i > 0) 
        kputc(s[--i]);
}		

void ksetCursor()
{
  int cursor_offset = cursor_x+cursor_y*80;
  _outb(0x3d4,14);
  _outb(0x3d5,((cursor_offset>>8)&0xFF));
  _outb(0x3d4,15);
  _outb(0x3d5,(cursor_offset&0xFF));
}

void kputc(char c)
{
  if(cursor_x>79) {
    cursor_x=0;
    cursor_y++;
  }
  if(cursor_y>24) {
    cursor_y=0;
    kclear_screen();
  }
  switch(c) {		
    case '\r': cursor_x=0; break;		
    case '\n': cursor_x=0; cursor_y++; break; 		
    case 0x8 : if(cursor_x>0) cursor_x--; break;
    case 0x9 : cursor_x=(cursor_x+8)&~7; break;
    default  : 
      video_memory[(cursor_x+80*cursor_y)*2]=c;
      cursor_x++;
      break;
  }
  ksetCursor();
}

/*******************************************       Func ctx      **/

void kyield(){
	Ctx_s * next_ctx = current_ctx->next;
	switch_context(next_ctx);
}

int kfork(){
	switch_context(NULL);	
	return current_ctx->pid;
}

int kgetpid(){
	return current_ctx->pid;
}

/*******************************************       Sys handler      **/


void sys_call_handler_irq(int_regs_t *r){
	switch (r->eax)
	{
	case SYS_PUTS: 
		kputs((char*)r->edx);
		break;
	case SYS_PUTC: 
		kputc((char )r->edx);
		break;
	case SYS_CLEAR_SCREEN:
		kclear_screen();
		break;
	case SYS_GET_PID:
		int current_pid = kgetpid();
		asm volatile ("movl %0, %%edx" :: "r" (current_pid));
		break;
	case SYS_PUTUD:
		kputud(r->edx);
		break;
	case SYS_PUTHEX:
		kputhex(r->edx);
		break;
	case SYS_YIELD:
		kyield();
		break;
	case SYS_FORK:
		int fork_pid = kfork();
		asm volatile ("movl %0, %%edx" :: "r" (fork_pid));
		break;
	default:
		kputs("Error : default case for syscall");
		break;
	}
}
