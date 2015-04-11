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
#include <time.h>

#include <cu.h>
#include <opcodes.h>

cu_t *cu_init(const char *filename)
{
	cu_t *cu = (cu_t*) malloc(sizeof(cu_t));
	if (cu == NULL)
		return NULL;

	cu->ram = memory_init(filename);
	cu->ir = ir_init();
	cu->ccr = ccr_init();
	cu->d0 = 0;
	cu->pc = 0;

	return cu;
}

void cu_free(cu_t *cu)
{
	if (cu == NULL)
		return;

	ir_free(cu->ir);
	memory_free(cu->ram);

	free(cu);
}

u8 cu_run(cu_t *cu)
{
	u8 stop = FALSE;

	if (cu == NULL)
		return FALSE;

	while (cu->pc < MEMORY_SIZE && !stop)
	{
		if (cu->pc == MEMORY_SIZE)
		{
			stop = TRUE;

			break;
		}

		if (!ir_loadInstruction(cu->ir, cu->pc, cu->ram) && cu->pc > 0)
		{
			printf("ERROR : can not load next instruction !\n");
			cu_free(cu);
			exit(EXIT_FAILURE);

			return FALSE; // Just in case
		}

		if (!opcodes[ir_getOpcode(cu->ir)](&cu->d0, &cu->pc, cu->ir, &cu->ccr, cu->ram))
		{
			printf("ERROR : something wrong happened during the execution !\n");
			cu_free(cu);
			exit(EXIT_FAILURE);

			return FALSE; // Just in case
		}
	}

	return TRUE;
}
