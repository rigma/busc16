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
#include <string.h>

#include <chip.h>

chip_t chip_init(u8 reset, FILE *f)
{
	chip_t chip = NULL;
	size_t i = 0;

	chip = (chip_t) malloc(CHIP_SIZE * sizeof(u8));
	if (chip == NULL)
		return NULL;

	if (f != NULL)
		fread((void*) chip, sizeof(u8), (size_t) CHIP_SIZE, f);
	else if (reset)
	{
		for (i = 0 ; i < CHIP_SIZE ; i++)
			chip[i] = (u8) 0x0;
	}

	return chip;
}

void chip_free(chip_t chip)
{
	if (chip == NULL)
		return;

	free(chip);
}

u8 chip_save(chip_t chip, FILE *f)
{
	if (chip == NULL || f == NULL)
		return FALSE;

	return (fwrite((void*) chip, sizeof(u8), (size_t) CHIP_SIZE, f) == 0) ? FALSE : TRUE;
}
