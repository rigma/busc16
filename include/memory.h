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

typedef struct {
	u8 ram[MEMORY_SIZE];
	u8 *mbr;
	u8 *mar;
	char *filename;
} memory_t;

memory_t *memory_init(const char *filename);
void memory_free(memory_t *m);

u8 *memory_setMbrPos(memory_t *m, u16 address);
u8 *memory_setMarPos(memory_t *m, u16 address);

#endif
