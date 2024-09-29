#ifndef _CTX_HEADER_
#define _CTX_HEADER_

/**
 *######################################################################
 *#                                                                    #
 *#                                Macro                               #
 *#                                                                    #
 *######################################################################
 */

#define MAX_CTX 30

/**
 *######################################################################
 *#                                                                    #
 *#                               Structs                              #
 *#                                                                    #
 *######################################################################
 */

typedef struct ctx_s{
	unsigned int pid;
	void * cr3;
	void * esp;
	void * ebp;
	struct ctx_s * next;
}Ctx_s;

/**
 *######################################################################
 *#                                                                    #
 *#                             Prototypes                             #
 *#                                                                    #
 *######################################################################
 */


/**
 * @brief 
 * 
 */
void init_ctx_s();

/**
 * @brief 
 * 
 * @return Ctx_s* 
 */
Ctx_s * alloc_ctx();

/**
 * @brief 
 * 
 * @param ctx 
 */
void free_ctx(Ctx_s *ctx);

/**
 * @brief 
 * 
 * @param ctx 
 */
void switch_context(Ctx_s *ctx);

#endif // !_CTX_HEADER