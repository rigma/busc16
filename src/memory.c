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
	u8 i = 0;
	
	// Trying to allocate the memory
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
			for (i = 0 ; i < 4 ; i++)
				m->chips[i] = chip_init(0, f);

			fclose(f);
		}
		else
		{
			for (i = 0 ; i < 4 ; i++)
				m->chips[i] = chip_init(0, NULL);
		}

		m->filename = (char*) malloc((strlen(filename) + 1) * sizeof(char));
		if (m->filename != NULL)
			strcpy(m->filename, filename);
	}
	else
	{
		// Otherwise, we just reset the whole program part
		for (i = 0; i < 4; i++)
			m->chips[i] = chip_init(0, NULL);

		m->filename = NULL;
	}

	// Setting MAR and MBR to the 0 position
	memory_setWordMode(m, WORD);

	m->mar = memory_read(m, (u16) 0);
	m->mbr = memory_read(m, (u16) (MEMORY_SIZE - 1));

	return m;
}

void memory_free(memory_t *m)
{
	FILE *f = NULL;
	u8 i = 0;

	if (m == NULL)
		return;

	// Trying to open the file of save
	if (m->filename != NULL)
	{
		f = fopen(m->filename, "wb");
		if (f != NULL)
		{
			// Writing the content of the memory on the file
			for (i = 0; i < 4; i++)
				chip_save(m->chips[i], f);

			fclose(f);
		}
	}

	// FREE THEM ALL !!!!
	free(m->filename);
	free(m);
}

void memory_setWordMode(memory_t *m, u8 wordMode)
{
	m->wordMode = wordMode & 0x3;
}

u8 memory_write(memory_t *m, u16 address, u32 *content)
{
	u8 chipSelect = 0;

	if (m == NULL || content == NULL)
		return FALSE;

	chipSelect = address & 0x3;

	if (m->wordMode & 0x2)
	{
		m->chips[3][address >> 2] = (u8) ((*content & 0xff000000) >> 24);
		m->chips[2][address >> 2] = (u8) ((*content & 0x00ff0000) >> 16);
		m->chips[1][address >> 2] = (u8) ((*content & 0x0000ff00) >> 8);
		m->chips[0][address >> 2] = (u8) (*content & 0x000000ff);
	}
	else if ((m->wordMode & 0x1) && !(chipSelect & 0x2))
	{
		m->chips[1][address >> 2] = (u8) ((*content & 0x0000ff00) >> 8);
		m->chips[0][address >> 2] = (u8) (*content & 0x000000ff);
	}
	else if ((m->wordMode & 0x1) && !(chipSelect & 0x2))
	{
		m->chips[3][address >> 2] = (u8) ((*content & 0xff000000) >> 24);
		m->chips[2][address >> 2] = (u8) ((*content & 0x00ff0000) >> 16);
	}
	else if (!(chipSelect & 0x2) && !(chipSelect & 0x1))
		m->chips[0][address >> 2] = (u8) (*content & 0x000000ff);
	else if (!(chipSelect & 0x2) && (chipSelect & 0x1))
		m->chips[1][address >> 2] = (u8) (*content & 0x000000ff);
	else if ((chipSelect & 0x2) && !(chipSelect & 0x1))
		m->chips[2][address >> 2] = (u8) (*content & 0x000000ff);
	else if ((chipSelect & 0x2) && (chipSelect & 0x1))
		m->chips[3][address >> 2] = (u8) (*content & 0x000000ff);

	return TRUE;
}

u32 memory_read(memory_t *m, u16 address)
{
	u8 chipSelect = address & 0x3;

	if (m == NULL)
		return 0;

	if (m->wordMode & 0x2)
		return (((u32) m->chips[3][address >> 2]) << 24) + (((u32) m->chips[2][address >> 2]) << 16) + (((u32) m->chips[1][address >> 2]) << 8) + (u32) (m->chips[0][address >> 2]);
	else if ((m->wordMode & 0x1) && !(chipSelect & 0x2))
		return (((u32) m->chips[1][address >> 2]) << 8) + ((u32) m->chips[0][address >> 2]);
	else if ((m->wordMode & 0x1) && !(chipSelect & 0x2))
		return (((u32) m->chips[3][address >> 2]) << 8) + ((u32) m->chips[2][address >> 2]);
	else if (!(chipSelect & 0x2) && !(chipSelect & 0x1))
		return (u32) m->chips[0][address >> 2];
	else if (!(chipSelect & 0x2) && (chipSelect & 0x1))
		return (u32) m->chips[1][address >> 2];
	else if ((chipSelect & 0x2) && !(chipSelect & 0x1))
		return (u32) m->chips[2][address >> 2];
	else if ((chipSelect & 0x2) && (chipSelect & 0x1))
		return (u32) m->chips[3][address >> 2];

	return 0;
}

u8 memory_MAR_read(memory_t *m, u16 address)
{
	if (m == NULL)
		return FALSE;

	m->mar = memory_read(m, address);

	return TRUE;
}

u8 memory_MAR_write(memory_t *m, u16 address)
{
	if (m == NULL)
		return FALSE;

	return memory_write(m, address, &m->mar);
}

u8 memory_MBR_read(memory_t *m, u16 address)
{
	if (m == NULL)
		return FALSE;

	m->mbr = memory_read(m, MEMORY_SIZE - (address * 4) - 1);

	return TRUE;
}

u8 memory_MBR_write(memory_t *m, u16 address)
{
	if (m == NULL)
		return FALSE;

	return memory_write(m, MEMORY_SIZE - (address * 4) - 1, &m->mbr);
}

void memory_write_prime(memory_t *m)
{
	u8 prime[] = {
		0x16, 0x00, 0x02, 0x07, 0x00, 0x00, 0x1c, 0x00, 0x65, 0x02, 0x00, 0x05, 0x00, 0x00, 0x00, 0x19,
		0x00, 0x01, 0x07, 0x00, 0x02, 0x16, 0x00, 0x02, 0x07, 0x00, 0x01, 0x0c, 0x00, 0x02, 0x02, 0x00,
		0x10, 0x0d, 0x00, 0x00, 0x06, 0x00, 0x00, 0x18, 0x00, 0x01, 0x07, 0x00, 0x00, 0x05, 0x00, 0x02,
		0x06, 0x00, 0x00, 0x0b, 0x00, 0x01, 0x0a, 0x00, 0x01, 0x07, 0x00, 0x03, 0x06, 0x00, 0x00, 0x0c,
		0x00, 0x03, 0x01, 0x00, 0x1b, 0x06, 0x00, 0x01, 0x18, 0x00, 0x01, 0x07, 0x00, 0x01, 0x05, 0x00,
		0x09, 0x05, 0x00, 0x0d, 0x00
	};
	u8 i = 0;

	memory_setWordMode(m, BYTE);

	for (i = 0; i < 85; i++)
	{
		m->mar = (u32) prime[i];
		
		memory_MAR_write(m, (u16) i);
	}
}
