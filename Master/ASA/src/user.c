#include "user.h"
#include "sys.h"

int getpid(){
	int pid = 0;
	asm volatile ("movl %0, %%edx" "\n\t"
        "movl %1, %%eax" "\n\t"
        "int $87" 
        : : "r"(&pid),"r"(SYS_GET_PID) : "edx", "eax");
    return pid;
}

void puts(char *s){
    asm volatile ("movl %0, %%edx" "\n\t"
        "movl %1, %%eax" "\n\t"
        "int $87" 
        : : "r"(s),"r"(SYS_PUTS) : "edx", "eax");
}

void putud(unsigned int nb){
    unsigned int saved_edx, saved_eax;
    asm volatile ("movl %%edx, %0" : "=r"(saved_edx));
    asm volatile ("movl %%eax, %0" : "=r"(saved_eax));
    
    asm volatile (
        "movl %0, %%edx" "\n\t"
        "movl %1, %%eax" "\n\t"
        "int $87" 
        : : "r"(nb),"r"(SYS_PUTUD) : "edx", "eax"
    );
    
    asm volatile ("movl %0, %%edx" : : "r"(saved_edx));
    asm volatile ("movl %0, %%eax" : : "r"(saved_eax));
}


void puthex(unsigned int nb){
    asm volatile ("movl %0, %%edx" "\n\t"
        "movl %1, %%eax" "\n\t"
        "int $87" 
        : : "r"(nb),"r"(SYS_PUTHEX) : "edx", "eax");
}

void putc(char c){
    asm volatile("movl %0, %%edx" "\n\t"
        "movl %1, %%eax" "\n\t"
        "int $87" 
        : : "r"((int)c), "r"(SYS_PUTC) : "edx", "eax");
}

void clear_screen(){
	asm volatile("movl %0, %%eax \n\t" 
    "int $87"
    : : "r"(SYS_CLEAR_SCREEN) : "eax");
}

int fork(){
	int pid = 0;
	asm volatile ("movl %0, %%edx" "\n\t"
        "movl %1, %%eax" "\n\t"
        "int $87" 
        : : "r"(&pid),"r"(SYS_FORK) : "edx", "eax");
    return pid;
}



void yield(){
	asm volatile("movl %0, %%eax \n\t" 
    "int $87"
    : : "r"(SYS_YIELD) : "eax");

}

void f_consume()
{
	char buffer[1024] = {};
	putc('.');
}

static void f_consume2(int i)
{
	if(i > 0){
		char buffer[1024] = {};
		putc('.');
		f_consume2(i - 1);
	}
}

void user_main(){
    // clear_screen(); // Fonctionne
	int pid = getpid();
	puts("Context pid :");
	puthex(pid);
	puts("\n\0");
    puts("Hello from userland\n\0"); 
    puts("Write succeeded!\n\0");
	puts("Start to consume buffer!\n\0");
	putc('\n');
	f_consume2(60);
	puts("Fork : \n\0");
	int fork_pid = fork();
	puthex(fork_pid);
	if(!fork_pid)
	puts("\nYield Begin : \n\0");
	yield();
	puts("Yield End : \n\0");
	puts("End of user");
	for(;;){

	}
}