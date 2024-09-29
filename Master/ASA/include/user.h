#ifndef _USER_LAND_H_
#define _USER_LAND_H_

#include "sys.h"
#include "macro.h"

/**
 * @brief 
 * 
 * @return int 
 */
int getpid();

/**
 * @brief 
 * 
 * @param s 
 */
void puts(char *s);

/**
 * @brief 
 * 
 * @param c 
 */
void putc(char c);

/**
 * @brief 
 * 
 * @param nb 
 */
void putud(unsigned int nb);

/**
 * @brief 
 * 
 * @param nb 
 */
void puthex(unsigned int nb);

/**
 * @brief 
 * 
 */
void clear_screen();

/**
 * @brief 
 * 
 * @return int 
 */
int fork();


/**
 * @brief 
 * 
 */
void user_main();

#endif // !_USER_LAND_H_