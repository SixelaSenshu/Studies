#include "mmu.h"

/*--- Global Variables --------------------------------*/
Page_Directory_s page_directories;
Page_Table_s kernel_page_table;
Page_Table_s dynamic_page_table_user;
Free_Pages_List_t free_page_list;
void * stack_address_top;
int current_dynamic_up;

/*--- Extern Variables --------------------------------*/

extern char _begin_of_user_space;
extern char _end_of_user_space;
extern char _begin_of_kernel_stack;
extern char _end_of_kernel_stack;

/*--- Declarations Functions --------------------------------*/

static void display_error(uint32_t eip,unsigned int cr2,unsigned int err);
static void set_virtual_memory(Page_Directory_s *page_dir);
static void* get_stack_address_top();
static void* get_stack_address_bottom();
static void* GET_CR2();
void set_parameters_kernel();
void unset_parameters_kernel();

/*--- Prototypes Functions --------------------------------*/

static void display_error(uint32_t eip,unsigned int cr2,unsigned int err){
	PRINTHEX("EIP : 0x",eip);
    PRINTHEX("Page Fault at address: 0x", cr2);
    PRINTHEX("Error code: 0x", err);
}

/*******************************************       Registers functions      **/
static void set_virtual_memory(Page_Directory_s *page_dir){          
    asm("mov %0, %%cr3" :: "r"(page_dir));               
}

void set_parameters_kernel(){     
	unsigned int cr0;
	asm("mov %%cr0,%0 " : "=r"(cr0));
	cr0 = cr0 | FLAG_CR0_FAULT_KERNEL_READ_ONLY | FLAG_CR0_ACTIVATE;  
    asm("mov %0, %%cr0" :: "r"(cr0));              
}

void unset_parameters_kernel(){
	unsigned int cr0;
	asm("mov %%cr0,%0 " : "=r"(cr0));
	cr0 = 0;  
    asm("mov %0, %%cr0" :: "r"(cr0));   
}

static void * GET_CR2(){
	 unsigned int fault_address;
     asm volatile("mov %%cr2, %0" : "=r" (fault_address));
	 return (void *)fault_address;
}

static void* get_stack_address_top() {
    return page_to_addr(2 * PAGE_TABLE_SIZE) - 4;
}

static void* get_stack_address_bottom(){
	int num_page = (2 * PAGE_TABLE_SIZE) - current_dynamic_up;
    return page_to_addr(num_page) - 4;
}


/*******************************************       MMU functions      **/
void setup_mmu(){
    int pos_start_user = addr_to_page(&_begin_of_user_space) % PAGE_TABLE_SIZE;
    int pos_end_user = addr_to_page(&_end_of_user_space) % PAGE_TABLE_SIZE;
    int pos_kernel_stack_deb = addr_to_page(&_begin_of_kernel_stack) % PAGE_TABLE_SIZE;
    int pos_kernel_stack_end = addr_to_page(&_end_of_kernel_stack) % PAGE_TABLE_SIZE;

	putc('\n');
	puts("Stack_kernel : ");
	puthex( addr_to_page(&_begin_of_kernel_stack) % PAGE_TABLE_SIZE);
	puts(" to : ");
	puthex( addr_to_page(&_end_of_kernel_stack) % PAGE_TABLE_SIZE);
	putc('\n');
	puts("User_space : ");
	puthex( addr_to_page(&_begin_of_user_space) % PAGE_TABLE_SIZE);
	puts(" to : ");
	puthex( addr_to_page(&_end_of_user_space) % PAGE_TABLE_SIZE);
	putc('\n');
	

	current_dynamic_up = 0;
    free_page_list.first_empty_idx = 0;
    stack_address_top = get_stack_address_top();

    // Initialisation des entrées des dossiers
    for(int i = 0; i < PAGE_DIRECTORY_SIZE; i++){ 
        page_directories.entries[i].present = 0;
    }

    // Initialisation de la page table pour le kernel
    for(int i = 0; i < PAGE_TABLE_SIZE; i++){
        kernel_page_table.entries[i].present = 1;
        kernel_page_table.entries[i].frame = i;
        kernel_page_table.entries[i].acces_mode = 0;
        kernel_page_table.entries[i].read_write = 0;
        free_page_list.pages[free_page_list.first_empty_idx++] = -1;
    }

    // Paramètres des pages_directories
    // Page table kernel
    page_directories.entries[0].present = 1;
    page_directories.entries[0].acces_mode = 0;
    page_directories.entries[0].table = ((unsigned int)&kernel_page_table >> 12); 

    // Page table utilisateur
    page_directories.entries[1].present = 1; 
    page_directories.entries[1].read_write = 1;
    page_directories.entries[1].acces_mode = 1;
    page_directories.entries[1].table = ((unsigned int)&dynamic_page_table_user >> 12);

	// Initialisation des pages pour le stack kernel
    for(int i = pos_kernel_stack_deb; i <= pos_kernel_stack_end; i++){ 
        dynamic_page_table_user.entries[i].present = 1;
        dynamic_page_table_user.entries[i].frame = (i + 1024);
        dynamic_page_table_user.entries[i].acces_mode = 0;
        dynamic_page_table_user.entries[i].read_write = 1;
        free_page_list.pages[free_page_list.first_empty_idx++] = -1;
    }

    // Initialisation des pages pour le code utilisateur
    for(int i = pos_start_user; i < pos_end_user; i++){ 
        dynamic_page_table_user.entries[i].present = 1;
        dynamic_page_table_user.entries[i].frame = (i + 1024);
        dynamic_page_table_user.entries[i].acces_mode = 1;
        dynamic_page_table_user.entries[i].read_write = 1;
        free_page_list.pages[free_page_list.first_empty_idx++] = -1;
    }
	
 	// Mis à jour des adresses virtuelles
    for(int i = free_page_list.first_empty_idx ; i < MAX_PAGES ;i++){
        free_page_list.pages[i] = i + 1;
    }

    free_page_list.pages[MAX_PAGES - 1] = -1;

	// Mise à jour de l'adressage et du mode de configuration de la mmu
    set_virtual_memory(&page_directories);
    set_parameters_kernel();

}


/*******************************************       Handler functions      **/

void page_fault_handler_idt(int_regs_t *r) {
    unsigned int error_code = r->err_code;
	void *fault_address = GET_CR2();
    int pos_cr2 = addr_to_page(fault_address);
    int pos_stack_user = addr_to_page(get_stack_address_bottom());
    if (pos_cr2 == pos_stack_user) {
		int pos_end_user = addr_to_page(&_end_of_user_space);
		if(pos_stack_user != pos_end_user){
			void* allocated_address = alloc_page();
			int pos_allocated = pos_cr2 % 1024;
			dynamic_page_table_user.entries[pos_allocated].frame = addr_to_page(allocated_address);
			dynamic_page_table_user.entries[pos_allocated].present = 1;
			dynamic_page_table_user.entries[pos_allocated].acces_mode = 1;
			dynamic_page_table_user.entries[pos_allocated].read_write = 1;
			current_dynamic_up++;
			if (allocated_address != NULL) {
				PRINTHEX("Allocated resource: 0x", (unsigned int)allocated_address);
				WAIT;
			}else {
            	PRINTF("Error to allocate\n", "");
				WAIT_INFINITE;
        	}
		}else{
			PRINTF("Stack overflow\n", "");
			WAIT_INFINITE;
		}
	}else{
		display_error(r->eip, (unsigned int)GET_CR2(),error_code);
		WAIT_INFINITE;
	}

}

/*******************************************       Page functions      **/

void *page_to_addr(int page){
	return (void *)(page * PAGE_SIZE);
}

int addr_to_page(void *addr){
	return ((int)addr / PAGE_SIZE);
}

void *alloc_page() {
    if (free_page_list.first_empty_idx != -1) {
        void *allocated_address = page_to_addr(free_page_list.first_empty_idx);
        int allocated_page = free_page_list.first_empty_idx;
        free_page_list.first_empty_idx = free_page_list.pages[allocated_page]; 
		free_page_list.pages[allocated_page] = -1;
        return allocated_address;
    } else {
        return NULL;
    }
}

void free_page( void *page_addr) {
    int page_index = addr_to_page(page_addr);
    if (page_index >= 0 && page_index < MAX_PAGES) {
        free_page_list.pages[page_index] = free_page_list.first_empty_idx; 
        free_page_list.first_empty_idx = page_index;
		int local_page = page_index % PAGE_TABLE_SIZE;
        dynamic_page_table_user.entries[local_page].present = 0;

    }
}

void page_copy(char *pg_src, char *pg_dst){

    while (*pg_src != '\0') {
        *pg_dst = *pg_src;
        pg_src++;
        pg_dst++;
    }
    *pg_dst = '\0'; 
}

/*******************************************       Dir functions      **/

Directory_Entry_s *clone_page_directory(Directory_Entry_s *src_pd) {
	unset_parameters_kernel();
    Directory_Entry_s * cloned_page_dir = alloc_page();
	if(cloned_page_dir == NULL){
		return NULL;
	}
	
    Page_Table_s *cloned_page_table = alloc_page();
	if(cloned_page_table == NULL){
		free_page(cloned_page_dir);
		return NULL;
	}

    Page_Table_s *source_page_table = (Page_Table_s *)(src_pd);
    cloned_page_dir->present = src_pd->present;
    cloned_page_dir->read_write = src_pd->read_write;
    cloned_page_dir->acces_mode = src_pd->acces_mode;
    cloned_page_dir->table = (unsigned int)cloned_page_table >> 12;


    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        Page_Entry_s source_entry = source_page_table->entries[i];
        cloned_page_table->entries[i].present = source_entry.present;
		cloned_page_table->entries[i].read_write = source_entry.read_write;
		cloned_page_table->entries[i].acces_mode = source_entry.acces_mode;
		if(source_entry.present){
			page_copy((char*)(source_page_table->entries[1].frame >> 12),(char*)(cloned_page_table->entries[i].frame >> 12));
	        cloned_page_table->entries[i].frame = source_entry.frame + 1024; 
		}
    }
	set_parameters_kernel();
    return cloned_page_dir;
}

void free_page_directory(Directory_Entry_s *src_pd) {
    Page_Table_s *source_page_table = (Page_Table_s *)(src_pd);
	if(src_pd->acces_mode != 0){
		for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
			Page_Entry_s source_entry = source_page_table->entries[i];
			free_page(page_to_addr(source_entry.frame));
    	}
	}
}

