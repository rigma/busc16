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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/memory.h"

memory_t *memory_init(const char *filename)
{
	FILE *f = NULL;
	memory_t *m = NULL;
	short i = 0;
	
	// Trying to allocating the memory
	m = (memory_t*) malloc(sizeof(memory_t));
	if (m == NULL)
		return NULL;

	// If the filename is here
	if (filename != NULL)
	{
		// Trying to open the file in binary reading mode
		f = fopen(filename, "rb");
		if (f != NULL)
		{
			// Reading the file content
			fread((void*) m->ram, sizeof(u8), MEMORY_SIZE, f);
			fclose(f);
		}
	}
	else
	{
		// Otherwise, we just reset the whole program part
		for (i = 0; i <= (u16) (MEMORY_SIZE / 2); i++)
			m->ram[i] = (u8) 0;
	}

	// Copying the filename
	if (filename != NULL)
	{
		m->filename = (char*)malloc(sizeof(filename) * sizeof(char));
		if (m->filename == NULL)
		{
			free(m);

			return NULL;
		}

		strcpy(m->filename, filename);
	}
	else
		m->filename = NULL;

	// Setting MAR and MBR to the 0 position
	m->mar = (u8*) m->ram;
	m->mbr = (u8*) (m->ram + MEMORY_SIZE - 1);

	return m;
}

void memory_free(memory_t *m)
{
	FILE *f = NULL;

	// Trying to open the file of save
	if (m->filename != NULL)
	{
		f = fopen(m->filename, "wb");
		if (f != NULL)
		{
			// Writing the content of the memory on the file
			fwrite((void*) m->ram, sizeof(u8), MEMORY_SIZE, f);
			fclose(f);
		}
	}

	// FREE THEM ALL !!!!
	free(m->filename);
	free(m);
}

u8 *memory_setMarPos(memory_t *m, u16 address)
{
	// If the positionning address is greater or equal to MEMORY_SIZE / 2, then we set position else, we do nothing
	m->mar = (address <= MEMORY_SIZE >> 1) ? (u8*)m->ram + address : m->mar;

	return m->mar;
}

u8 *memory_setMbrPos(memory_t *m, u16 address)
{
	// If the positionning address is lesser than MEMORY_SIZE / 2, then we set position else, we do nothing
	m->mbr = (address < MEMORY_SIZE >> 1) ? (u8*) (m->ram + MEMORY_SIZE - address - 1) : m->mbr;

	return m->mbr;
}
