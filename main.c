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

#include <cu.h>

int main(int argc, char **argv)
{
	cu_t *cu = NULL;
	
	printf("Welcome to the BUSC16 emulator v%d.%d !\n", VERSION_MAJOR, VERSION_MINOR);
	printf("Loading Central Unit...\n");

	cu = cu_init("prime.ram");

	printf("Launching...\n");

	if (cu == NULL)
		exit(EXIT_FAILURE);

	cu_run(cu);

	printf("End of program.\n");

	cu_free(cu);

	system("pause");

	return EXIT_SUCCESS;
}
