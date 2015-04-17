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

#ifndef CHIP_H
#define CHIP_H

#include <stdio.h>

#include "config.h"

typedef u8* chip_t;

/**
 * @fn     chip_init(u8 reset, FILE *f)
 * @author Romain Failla
 * @brief  Init a chip bar of the memory from a file, if it available
 * @param  u8 reset : tells if we reset the whole new memory
 * @param  FILE *f : the file which contains the content of the chip
 * @return chip_t : the reference to the new chip
 */
chip_t chip_init(u8 reset, FILE *f);

/**
 * @fn     chip_free(chip_t chip)
 * @author Romain Failla
 * @brief  Free a chip of the memory
 */
void chip_free(chip_t chip);

/**
 * @fn     chip_save(FILE *f)
 * @author Romain Failla
 * @brief  Save the chip in a file
 * @param  chip_t chip : the chip to save
 * @param  FILE *f : the file of save
 * @return u8 : TRUE if success, FALSE else
 */
u8 chip_save(chip_t chip, FILE *f);

#endif
