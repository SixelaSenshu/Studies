#ifndef _MMU_H
#define _MMU_H

#include "idt.h"
#include "sys.h"
#include "macro.h"

/**
 *######################################################################
 *#                                                                    #
 *#                                Macro                               #
 *#                                                                    #
 *######################################################################
 */

#define PAGE_SIZE 4096
#define PAGE_DIRECTORY_SIZE 1024
#define PAGE_TABLE_SIZE 1024
#define PAGE_SECTION 0x400000
#define STACK_DYNAMIC_SIZE 4
#define MAX_PAGES STACK_DYNAMIC_SIZE * PAGE_TABLE_SIZE
#define INVALID_PAGE -1
#define FLAG_CR0_ACTIVATE 0x80000000
#define FLAG_CR0_FAULT_KERNEL_READ_ONLY 0x00008000
/**
 *######################################################################
 *#                                                                    #
 *#                               Structs                              #
 *#                                                                    #
 *######################################################################
 */

/**
 * @brief Défini les informations et les droits d'accès d'une page qui contient une adresse physique
 */
typedef struct page_entry_s{
	/* data */
	unsigned int present : 1;  // (1) Présent (0) Absent
	unsigned int read_write : 1;  // (1) Lecture et écriture (0) Lecture seule
	unsigned int acces_mode : 1;  // (0) Utilisateur (1) Kernel 
	unsigned int cache_mode : 1;  // (0) Write-through (1) Write back
	unsigned int cache_enable : 1;  // (0) Désactivé (1) Activé
	unsigned int used_by_mmu : 1;  // (0) Non utilisé par le MMU (1) Utilisé par le MMU
	unsigned int dirty_bit : 1; // (1) Page modifiée (0) Page non modifiée
	unsigned int cache_management : 1; // Non utilisé
	unsigned int global_page : 1; // (0) Non global (1) Global
	unsigned int available : 3; // Non utilisé
	unsigned int frame : 20; // Adresse physique de la page
}Page_Entry_s;

/**
 * @brief Contient un ensemble de page_entry
 * 
 */
typedef struct page_table_s{
	/* data */
	Page_Entry_s entries[PAGE_TABLE_SIZE] __attribute__((aligned(PAGE_SIZE))); // idx2
}Page_Table_s;


/**
 * @brief Définie les informations et les droits d'accès d'une table de pages
 * 
 */
typedef struct directory_entry_s
{	
	unsigned int present : 1;  // (1) Présent (0) Absent
	unsigned int read_write : 1;  // (1) Lecture et écriture (0) Lecture seule
	unsigned int acces_mode : 1;  // (0) Utilisateur (1) Kernel 
	unsigned int cache_mode : 1;  // (0) Write-through (1) Write back
	unsigned int cache_enable : 1;  // (0) Désactivé (1) Activé
	unsigned int used_by_mmu : 1;  // (0) Non utilisé par le MMU (1) Utilisé par le MMU
	unsigned int reserved : 1; // Non utilisé
	unsigned int size_page : 1; // (0) 4Ko (1) 4Mo
	unsigned int available : 4; // Non utilisé
	unsigned int table : 20; // Adresse physique de la table de pages

}Directory_Entry_s;

/**
 * @brief Contient un ensemble de directory_entry
 * 
 */
typedef struct page_directory_s{
	/* data */
	Directory_Entry_s entries[PAGE_DIRECTORY_SIZE] __attribute__((aligned(PAGE_SIZE))); //idx1
}Page_Directory_s;

/**
 * @brief 
 * 
 */
typedef struct free_Pages_List_t{
	unsigned int pages[STACK_DYNAMIC_SIZE * PAGE_TABLE_SIZE];
	unsigned int first_empty_idx;
}Free_Pages_List_t;


/**
 *######################################################################
 *#                                                                    #
 *#                             Prototypes                             #
 *#                                                                    #
 *######################################################################
 */

/*******************************************       MMU functions      **/
/**
 * @brief 
 * 
 */
void setup_mmu();

/**
 * @brief Set the parameters kernel object
 * 
 */
void set_parameters_kernel();

/**
 * @brief 
 * 
 */
void unset_parameters_kernel();

/*******************************************       Handler functions      **/

/**
 * @brief 
 * 
 * @param r 
 */
void page_fault_handler_idt(int_regs_t *r);

/*******************************************       Page functions      **/

/**
 * @brief 
 * 
 * @param page 
 * @return void* 
 */
void *page_to_addr(int page);

/**
 * @brief 
 * 
 * @param addr 
 * @return int 
 */
int addr_to_page(void *addr);

/**
 * @brief 
 * 
 * @return void* 
 */
void *alloc_page();

/**
 * @brief 
 * 
 * @param page_addr 
 */
void free_page(void *page_addr);

/**
 * @brief 
 * 
 * @param pg_src 
 * @param pg_dst 
 */
void page_copy(char *pg_src, char *pg_dst);

/*******************************************       Dir functions      **/

/**
 * @brief 
 * 
 * @param src_pd 
 * @return Directory_Entry_s* 
 */
Directory_Entry_s *clone_page_directory(Directory_Entry_s *src_pd);

/**
 * @brief 
 * 
 * @param src_pd 
 */
void free_page_directory(Directory_Entry_s *src_pd);

#endif // !_MMU_H