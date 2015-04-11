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

#include <ccr.h>

ccr_t ccr_init()
{
	// ccr = 0000 0000
	return (ccr_t) 0x00;
}

ccr_t ccr_reset(ccr_t *ccr)
{
	*ccr = (ccr_t) 0x00;

	return *ccr;
}

u8 ccr_Z(ccr_t *ccr)
{
	// return 0000 xxxx & 0000 1000
	return (ccr != NULL) ? (u8) (*ccr & 0x08) >> 3 : FALSE;
}

void ccr_changeValueZ(ccr_t *ccr, u8 value)
{
	if (ccr == NULL)
		return;

	// do ccr = 0000 xxxx | 0000 1000 or 0000 xxxx & 0000 0111
	*ccr = (value) ? *ccr | 0x08 : *ccr & 0x07;
}

u8 ccr_N(ccr_t *ccr)
{
	// return 0000 xxxx & 0000 0100
	return (ccr != NULL) ? (u8) (*ccr & 0x04) >> 2 : FALSE;
}

void ccr_changeValueN(ccr_t *ccr, u8 value)
{
	if (ccr == NULL)
		return;

	// do ccr = 0000 xxxx | 0000 0100 or 0000 xxxx & 0000 1011
	*ccr = (value) ? *ccr | 0x04 : *ccr & 0x0b;
}

u8 ccr_C(ccr_t *ccr)
{
	// return 0000 xxxx & 0000 0010
	return (ccr != NULL) ? (u8) (*ccr & 0x02) >> 1 : FALSE;
}

void ccr_changeValueC(ccr_t *ccr, u8 value)
{
	if (ccr == NULL)
		return;

	// do ccr = 0000 xxxx | 0000 0010 or 0000 xxxx & 0000 1101
	*ccr = (value) ? *ccr | 0x02 : *ccr & 0x0d;
}

u8 ccr_V(ccr_t *ccr)
{
	// return 0000 xxxx & 0000 0001
	return (ccr != NULL) ? (u8) (*ccr & 0x01) : FALSE;
}

void ccr_changeValueV(ccr_t *ccr, u8 value)
{
	if (ccr == NULL)
		return;

	// do ccr = 0000 xxxx | 0000 0001 or 0000 xxxx & 0000 1110
	*ccr = (value) ? *ccr | 0x01 : *ccr & 0x0e;
}
