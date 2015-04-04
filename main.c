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

#include <ccr.h>
#include <opcodes.h>

int main(int argc, char **argv)
{
	// Some bullshit tests :P
	ccr_t ccr = ccr_init();
	u8 d0 = 15;

	printf("Initial value d0 = %u\n", d0);
	printf("Z = %u | N = %u | C = %u | V = %u\n\n", ccr_Z(&ccr), ccr_N(&ccr), ccr_C(&ccr), ccr_V(&ccr));

	ccr_reset(&ccr);
	opcodes[8](&d0, 8, &ccr);

	printf("d0 = %u\n", d0);
	printf("Z = %u | N = %u | C = %u | V = %u\n\n", ccr_Z(&ccr), ccr_N(&ccr), ccr_C(&ccr), ccr_V(&ccr));

	ccr_reset(&ccr);
	opcodes[9](&d0, 24, &ccr);

	printf("d0 = %u\n", d0);
	printf("Z = %u | N = %u | C = %u | V = %u\n\n", ccr_Z(&ccr), ccr_N(&ccr), ccr_C(&ccr), ccr_V(&ccr));

	ccr_reset(&ccr);
	opcodes[8](&d0, 24, &ccr);
	opcodes[10](&d0, 24, &ccr);

	printf("d0 = %u\n", d0);
	printf("Z = %u | N = %u | C = %u | V = %u\n\n", ccr_Z(&ccr), ccr_N(&ccr), ccr_C(&ccr), ccr_V(&ccr));

	system("pause");

	return EXIT_SUCCESS;
}
