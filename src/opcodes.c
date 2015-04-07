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

#include <stdio.h>
#include <opcodes.h>

static u8 stop(u8 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	*pc = MEMORY_SIZE + 1;

	return TRUE;
}

static u8 brz(u8 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	*pc = ccr_Z(ccr) ? ir_getOperand(ir) : *pc + 1;

	return TRUE;
}

static u8 brn(u8 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	*pc = ccr_N(ccr) ? ir_getOperand(ir) : *pc + 1;

	return TRUE;
}

static u8 brc(u8 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	*pc = ccr_C(ccr) ? ir_getOperand(ir) : *pc + 1;

	return TRUE;
}

static u8 brv(u8 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	*pc = ccr_V(ccr) ? ir_getOperand(ir) : *pc + 1;

	return TRUE;
}

static u8 bra(u8 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	*pc = ir_getOperand(ir);

	return TRUE;
}

static u8 lda(u8 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	u8 *mbr = (void*) 0x0;

	if (ir_immediateAddressing(ir))
		*d0 = (u8) ir_getOperand(ir);
	else
	{
		mbr = m->mbr;
		if (mbr == memory_setMbrPos(m, ir_getOperand(ir)))
			return FALSE;

		*d0 = *m->mbr;
	}

	*pc++;

	return TRUE;
}

static u8 sda(u8 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	u8 *mbr = m->mbr;

	if (mbr == memory_setMbrPos(m, ir_getOperand(ir)))
		return FALSE;

	*m->mbr = *d0;
	*pc++;

	return TRUE;
}

static u8 add(u8 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	u16 tmp = 0;
	u8 *mbr = (u8*) 0x0, input = 0;

	if (ir_immediateAddressing(ir))
		input = (u8) ir_getOperand(ir);
	else
	{
		mbr = m->mbr;
		if (mbr == memory_setMbrPos(m, ir_getOperand(ir)))
			return FALSE;

		input = *m->mbr;
	}

	tmp = *d0 + input;

	*d0 = (u8) (tmp & 0xff);
	if (tmp > 0xff)
		ccr_setC(ccr);

	*pc++;

	return TRUE;
}

static u8 sub(u8 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	short tmp = 0;
	u8 *mbr = (u8*) 0x0, input = 0;

	if (ir_immediateAddressing(ir))
		input = (u8) ir_getOperand(ir);
	else
	{
		mbr = m->mbr;
		if (mbr == memory_setMbrPos(m, ir_getOperand(ir)))
			return FALSE;

		input = *m->mbr;
	}

	tmp = (short) *d0 - (short) input;

	*d0 = (u8) (tmp & 0xff);

	if (!tmp)
		ccr_setZ(ccr);
	else if (tmp < 0x0)
		ccr_setN(ccr);

	*pc++;

	return TRUE;
}

static u8 mul(u8 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	u16 tmp = 0;
	u8 *mbr = (u8*) 0x0, input = 0;

	if (ir_immediateAddressing(ir))
		input = (u8) ir_getOperand(ir);
	else
	{
		mbr = m->mbr;
		if (mbr == memory_setMbrPos(m, ir_getOperand(ir)))
			return FALSE;

		input = *m->mbr;
	}

	tmp = *d0 * input;

	*d0 = (u8) (tmp & 0xff);
	if (tmp > 0xff)
		ccr_setV(ccr);

	*pc++;

	return TRUE;
}

static u8 div(u8 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	u16 tmp = 0;
	u8 *mbr = (u8*) 0x0, input = 0;

	if (ir_immediateAddressing(ir))
		input = (u8) ir_getOperand(ir);
	else
	{
		mbr = m->mbr;
		if (mbr == memory_setMbrPos(m, ir_getOperand(ir)))
			return FALSE;

		input = *m->mbr;
	}

	tmp = *d0 / input;

	*d0 = (u8) (tmp & 0xff);
	if (tmp > 0xff)
		ccr_setV(ccr);

	*pc++;

	return TRUE;
}

static u8 cmp(u8 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	short tmp = 0;
	u8 *mbr = (u8*) 0x0, input = 0;

	if (ir_immediateAddressing(ir))
		input = (u8) ir_getOperand(ir);
	else
	{
		mbr = m->mbr;
		if (mbr == memory_setMbrPos(m, ir_getOperand(ir)))
			return FALSE;

		input = *m->mbr;
	}

	tmp = (short) *d0 - (short) input;

	if (!tmp)
		ccr_setZ(ccr);
	else if (tmp < 0x0)
		ccr_setN(ccr);

	*pc++;

	return TRUE;
}

static u8 dsp(u8 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	u8 *mbr = (void*) 0x0;

	if (ir_immediateAddressing(ir))
		printf("%u\n", ir_getOperand(ir));
	else
	{
		mbr = m->mbr;
		if (mbr == memory_setMbrPos(m, ir_getOperand(ir)))
			return FALSE;

		printf("%u\n", *m->mbr);
	}

	*pc++;

	return TRUE;
}

u8 (*const opcodes[])(u8*, u16*, ir_t*, ccr_t*, memory_t*) = {
	stop, brz, brn, brc, brv, bra, lda, sda,
	add, sub, mul, div, cmp, dsp, (void*) 0x0, (void*) 0x0
};
