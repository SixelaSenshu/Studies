#ifndef _BINPACK_H_
#define _BINPACK_H_

#include "./backpack.h"

/**
 * @brief
 *
 */
typedef struct _Binpack_
{
    int size;
    int limit;
    Backpack **items;

} Binpack;

/**
 * @brief
 *
 * @param nbobjs
 * @param maxWeigth
 * @param nbsacs
 * @return Backpack*
 */
Binpack *Binpack_create(int nbobjs, int maxWeigth, int nbsacs);

/**
 * @brief
 *
 * @param binpack
 */
void Binpack_free(Binpack *binpack);

/**
 * @brief
 *
 * @param binpack
 * @param item
 * @return int
 */
int Binpack_add(Binpack *binpack, Backpack *backpack);

/**
 * @brief
 *
 * @param binpack
 */
void Binpack_toString(Binpack *binpack, int k);

#endif //!_BINPACK_H_