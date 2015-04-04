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

#ifndef MEMORY_H
#define MEMORY_H

#include "config.h"

/**
 * @struct memory_t
 * @author Romain Failla
 * @brief  It symbolizes the memory that is accessed by the BUSC16 processor.
 *         It has a SRAM of 64 kio access, the MBR and MAR register and a filename in order to have a program writed on it.
 *		   For now, the first half of the memory is reserved for the Assembler code and the second half is reserved for local variables.
 */
typedef struct {
	u8 ram[MEMORY_SIZE];
	u8 *mbr;
	u8 *mar;
	char *filename;
} memory_t; // TODO : adding a ROM system for storing the program, I think it'll be better.

/**
 * @fn     memory_init(const char *filename)
 * @author Romain Failla
 * @brief  Initialize the memory with a file or not
 * @param  const char *filename : the name of the file where a BUSC16 SRAM is saved.
 * @return memory_t* : the reference to the memory
 */
memory_t *memory_init(const char *filename);

/**
 * @fn     memory_free(memory_t *m)
 * @author Romain Failla
 * @brief  Try to save the memory in the file specified at the initialization and free it.
 * @param  memory_t *m : the reference to the memory which has to be freed
 */
void memory_free(memory_t *m);

/**
* @fn     memory_setMarPos(memory_t *m, u16 address)
* @author Romain Failla
* @brief  Set the position of the MAR on the SRAM
* @param  memory_t *m : the reference of the memory
* @param  u16 address : the positionning address
* @return u8* : the new position of MAR register
*/
u8 *memory_setMarPos(memory_t *m, u16 address);

/**
 * @fn     memory_setMbrPos(memory_t *m, u16 address)
 * @author Romain Failla
 * @brief  Set the position of the MBR on the SRAM
 * @param  memory_t *m : the reference of the memory
 * @param  u16 address : the positionning address
 * @return u8* : the new position of MBR register
 */
u8 *memory_setMbrPos(memory_t *m, u16 address);

#endif
