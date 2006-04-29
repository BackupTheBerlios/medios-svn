/*
 * @ingroup dcplaya_math_devel
 * @file    math_int.h
 * @author  benjamin gerard
 * @date    2002/02/12
 * @brief   Integer mathematic support.
 *
 * $Id: math_int.h,v 1.1 2006/03/04 17:20:22 vincentp Exp $
 */

#ifndef _MATH_INT_H_
#define _MATH_INT_H_

#include "common.h"

EXTERN_C_START

/** @name Integer mathematic basics.
 *  @ingroup dcplaya_math_devel
 *  @{
 */

/** Small Bijection for calculate a square root.
 *  @param x value
 *  @return square root of x
 */
unsigned int int_sqrt (unsigned int x);

/** @} */

EXTERN_C_END


#endif /* #ifndef _MATH_INT_H_ */
