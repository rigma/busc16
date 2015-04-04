/**
 * BUSC16 - An emulator of a theorical processor for lessons
 * Copyright (C) 2015 Romain Failla
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CCR_H
#define CCR_H

#include "config.h"

typedef unsigned char ccr_t;

/**
 * @fn     ccr_init()
 * @author Romain Failla
 * @brief  Return the initial value of CCR register
 * @return ccr_t : the initial value
 */
ccr_t ccr_init();

/**
 * @fn     ccr_Z(ccr_t *ccr)
 * @author Romain Failla
 * @brief  Return the value of the Z bit of CCR register
 * @param  ccr_t *ccr : the reference of CCR register
 * @return u8 : the value of the bit
 */
u8 ccr_Z(ccr_t *ccr);

/**
 * @fn     ccr_changeValueZ(ccr_t *ccr, u8 value)
 * @author Romain Failla
 * @brief  Change the value of the Z bit of CCR register
 * @param  ccr_t *ccr : the reference of CCR register
 */
void ccr_changeValueZ(ccr_t *ccr, u8 value);

/**
* @fn     ccr_N(ccr_t *ccr)
* @author Romain Failla
* @brief  Return the value of the N bit of CCR register
* @param  ccr_t *ccr : the reference of CCR register
* @return u8 : the value of the bit
*/
u8 ccr_N(ccr_t *ccr);

/**
* @fn     ccr_changeValueN(ccr_t *ccr, u8 value)
* @author Romain Failla
* @brief  Change the value of the N bit of CCR register
* @param  ccr_t *ccr : the reference of CCR register
*/
void ccr_changeValueN(ccr_t *ccr, u8 value);

/**
* @fn     ccr_C(ccr_t *ccr)
* @author Romain Failla
* @brief  Return the value of the C bit of CCR register
* @param  ccr_t *ccr : the reference of CCR register
* @return u8 : the value of the bit
*/
u8 ccr_C(ccr_t *ccr);

/**
* @fn     ccr_changeValueC(ccr_t *ccr, u8 value)
* @author Romain Failla
* @brief  Change the value of the C bit of CCR register
* @param  ccr_t *ccr : the reference of CCR register
*/
void ccr_changeValueC(ccr_t *ccr, u8 value);

/**
* @fn     ccr_V(ccr_t *ccr)
* @author Romain Failla
* @brief  Return the value of the V bit of CCR register
* @param  ccr_t *ccr : the reference of CCR register
* @return u8 : the value of the bit
*/
u8 ccr_V(ccr_t *ccr);

/**
* @fn     ccr_changeValueV(ccr_t *ccr, u8 value)
* @author Romain Failla
* @brief  Change the value of the V bit of CCR register
* @param  ccr_t *ccr : the reference of CCR register
*/
void ccr_changeValueV(ccr_t *ccr, u8 value);

#define ccr_setZ(ccr) ccr_changeValueZ(ccr, TRUE)
#define ccr_setN(ccr) ccr_changeValueN(ccr, TRUE)
#define ccr_setC(ccr) ccr_changeValueC(ccr, TRUE)
#define ccr_setV(ccr) ccr_changeValueV(ccr, TRUE)

#define ccr_resetZ(ccr) ccr_changeValueZ(ccr, FALSE)
#define ccr_resetZ(ccr) ccr_changeValueN(ccr, FALSE)
#define ccr_resetC(ccr) ccr_changeValueC(ccr, FALSE)
#define ccr_resetV(ccr) ccr_changeValueV(ccr, FALSE)

#endif
