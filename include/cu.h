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

#ifndef UC_H
#define UC_H

#include "ccr.h"
#include "config.h"
#include "ir.h"
#include "memory.h"

/**
 * @struct cu_t
 * @author Romain Failla
 * @brief  Symbolize the central unit of the BUSC16 processor
 */
typedef struct {
	ccr_t ccr;
	ir_t *ir;
	memory_t *ram;
	u8 d0;
	u16 pc;
} cu_t;

/**
 * @fn     cu_init(const char *filename)
 * @author Romain Failla
 * @brief  Initialize the central unit of the BUSC16
 * @param  const char *filename : the file that contains the memory
 * @return cu_t* : the reference to the new central unit
 */
cu_t *cu_init(const char *filename);

/**
* @fn     cu_free(cu_t *cu)
* @author Romain Failla
* @brief  Free a central unit of the memory
* @param  cu_t *cu : the reference to the central unit to free
*/
void cu_free(cu_t *cu);

/**
 * @fn     cu_run(cu_t *cu)
 * @author Romain Failla
 * @brief  Run the central unit
 * @param  cu_t *cu : the central unit to run
 * @return u8 : return 0 if everything was good, 1 else
 */
u8 cu_run(cu_t *cu);

#endif
