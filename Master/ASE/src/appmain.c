#include "context.h"
#include "list.h"
#include "sem.h"
#include "keyboard.h"
#include "sched.h"


/**
 * Variables ****************************************/

extern ctx_s context;
extern ctx_s * current_ctx;
ctx_s context_pong;
ctx_s context_ping;
int count = 0;
sem_s mutex;

/**
 * Prototype ****************************************/

void pong(void *args);
void ping(void *args);
void id_get_context(void *arg);
int id_throw(int arg);
int id(int arg);
void empty(void *args);	

/** Test ********************************************/

void try_process();
void throw_process();
void switch_context_process();
void yield_process();
void irq_process();
void sem_process();
void keyboard_process();

/**
 * App **********************************************/
void app_main()
{
	puts("Hello World\n");
	keyboard_process();
}

/**
 * Tests ****************************************/

void try_process(){
    puts("Test id :\n");
     int val = try(&context, id, 5);
    puts("Final return : ");
    putud(val);
    putc('\n');
}

void throw_process(){
    puts("Test id_throw :\n");
    int val = try(&context, id_throw, 5);
    puts("Final return : ");
    putud(val);
    putc('\n');
}

void switch_context_process(){
    current_ctx = NULL;
    puts("Test init_context :\n");
    init_ctx(&context_pong,pong,NULL);
    print_context(&context_pong);
    init_ctx(&context_ping,ping,NULL);
    print_context(&context_ping);
    puts("Test switch_context :\n");
    switch_context(&context_pong);
}

void yield_process(){
    current_ctx = NULL;
    puts("Test init_list :\n");
    create_ctx(pong,NULL);
    create_ctx(ping,NULL);
    puts("Test switch_context :\n");
    yield();
}

void irq_process(){
	current_ctx = NULL;
	create_ctx(pong,NULL);
    create_ctx(ping,NULL);
	start_sched();
	puts("Test irq :\n");
}

void sem_process(){
	puts("Set a caracter to continue\n");
	sem_init(&mutex,1);
	current_ctx = NULL;
	start_sched();
}

void keyboard_process(){
	current_ctx = NULL;
	current_ctx = NULL;
	create_ctx(pong,NULL);
    create_ctx(ping,NULL);
	start_sched();
}

/**
 * Function ****************************************/

void empty(void *args){
}

int id(int arg)
{
    puts("\nReturned value of the registered context : ");
    return arg;
}

void id_get_context(void *arg){
    char buffer[120];
    GET_EBP(context.ebp);
    GET_ESP(context.esp); 
}

int id_throw(int arg)
{
    throw(&context, 2);
    return arg;
}

void ping(void *args){
    while(1){
        putc('a');
        yield();
        putc('b');
        yield();
        putc('c');
        yield();
    }
}

void pong(void *args){
    while(1){
        putc('1');
        yield();
        putc('2');
        yield();
    }
}