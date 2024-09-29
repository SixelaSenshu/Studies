#ifndef _CERTIFICATE_H_
#define _CERTIFICATE_H_

#include "binpack.h"

/**
 * @brief
 *
 * @param nbSac
 * @param nbobjs
 * @param maxWeights
 * @param maxValue
 * @return Binpack*
 */
Binpack *generateCertificate(int nbSac, int nbobjs, int maxWeights, int maxValue);

/**
 * @brief
 *
 * @param certificate
 * @return true
 * @return false
 */
bool verifyCertificate(Binpack *certificate);

#endif
