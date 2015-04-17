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

#include "chip.h"
#include "config.h"

#define BYTE      0x0
#define HALF_WORD 0x1
#define WORD      0x2

/**
 * @struct memory_t
 * @author Romain Failla
 * @brief  It symbolizes the memory that is accessed by the BUSC16 processor.
 *         It has a SRAM of 64 kio access, the MBR and MAR register and a filename in order to have a program writed on it.
 *		   For now, the first half of the memory is reserved for the Assembler code and the second half is reserved for local variables.
 */
typedef struct {
	chip_t chips[4];
	u32 mbr;
	u32 mar;
	char *filename;
	u8 wordMode;
} memory_t;

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
 * @fn     memory_setWordMode(memory_t *m, u8 wordMode)
 * @author Romain Failla
 * @brief  Set the word mode of the memory
 * @param  memory_t *m : the reference to the memory
 * @param  u8 wordMode : the new word mode
 */
void memory_setWordMode(memory_t *m, u8 wordMode);

/**
 * @fn     memory_write(memory_t *m, u16 address, u32 *content)
 * @author Romain Failla
 * @brief  Write a content of a given address
 * @param  memory_t *m : the reference to the memory
 * @param  u16 address : the address where write
 * @param  u32 *content : the reference to the content to write
 * @return u8 : true if success, false else
 */
u8 memory_write(memory_t *m, u16 address, u32 *content);

/**
 * @fn     memory_read(memory_t *m, u16 address)
 * @author Romain Failla
 * @brief  Read the content of a given address
 * @param  memory_t *m : the reference to the memory
 * @param  u16 address : the address to read
 * @return u32 : the content of the word
 */
u32 memory_read(memory_t *m, u16 address);

/**
 * @fn     memory_MAR_read(memory_t *m, u16 address)
 * @author Romain Failla
 * @brief  Put the content of a given address in MAR register
 * @param  memory_t *m : the reference to the memory
 * @param  u16 address : the address to read
 * @return u8 : true if success, false else
 */
u8 memory_MAR_read(memory_t *m, u16 address);

/**
 * @fn     memory_MAR_write(memory_t *m, u16 address)
 * @author Romain Failla
 * @brief  Put the content of MAR register to the given address
 * @param  memory_t *m : the reference to the memory
 * @param  u16 address : the address where write
 * @return u8 : true if success, false else
 */
u8 memory_MAR_write(memory_t *m, u16 address);

/**
 * @fn     memory_MBR_read(memory_t *m, u16 address)
 * @author Romain Failla
 * @brief  Put the content of a given address in MBR register
 * @param  memory_t *m : the reference to the memory
 * @param  u16 address : the address to read
 * @return u8 : true if success, false else
 */
u8 memory_MBR_read(memory_t *m, u16 address);

/**
 * @fn     memory_MBR_write(memory_t *m, u16 address)
 * @author Romain Failla
 * @brief  Put the content of MBR register to the given address
 * @param  memory_t *m : the reference to the memory
 * @param  u16 address : the address where write
 * @return u8 : true if success, false else
 */
u8 memory_MBR_write(memory_t *m, u16 address);

void memory_write_prime(memory_t *m);

#endif
