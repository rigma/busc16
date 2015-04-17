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

static u8 stop(u32 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	*pc = (u16) (MEMORY_SIZE >> 1);

	return TRUE;
}

static u8 brz(u32 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	*pc = ccr_Z(ccr) ? ir_getOperand(ir) * 3 : *pc + 3;

	return TRUE;
}

static u8 brn(u32 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	*pc = ccr_N(ccr) ? ir_getOperand(ir) * 3 : *pc + 3;

	return TRUE;
}

static u8 brc(u32 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	*pc = ccr_C(ccr) ? ir_getOperand(ir) * 3 : *pc + 3;

	return TRUE;
}

static u8 brv(u32 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	*pc = ccr_V(ccr) ? ir_getOperand(ir) * 3 : *pc + 3;

	return TRUE;
}

static u8 bra(u32 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	*pc = ir_getOperand(ir) * 3;

	return TRUE;
}

static u8 lda(u32 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	if (ir_immediateAddressing(ir))
		*d0 = (u32) ir_getOperand(ir);
	else
	{
		memory_setWordMode(m, WORD);
		if (!memory_MBR_read(m, ir_getOperand(ir)))
			return FALSE;

		*d0 = m->mbr;
	}

	*pc += 3;

	return TRUE;
}

static u8 sta(u32 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	memory_setWordMode(m, WORD);

	m->mbr = (u32) *d0;
	if (!memory_MBR_write(m, ir_getOperand(ir)))
		return FALSE;

	*pc += 3;

	return TRUE;
}

static u8 add(u32 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	u16 tmp = 0;
	u32 input = 0;

	if (ir_immediateAddressing(ir))
		input = (u32) ir_getOperand(ir);
	else
	{
		memory_setWordMode(m, WORD);
		if (!memory_MBR_read(m, ir_getOperand(ir)))
			return FALSE;

		input = m->mbr;
	}

	tmp = *d0 + input;

	*d0 = (u32) (tmp & 0xffffffff);

	ccr_reset(ccr);

	if (tmp > 0xff)
		ccr_setC(ccr);

	*pc += 3;

	return TRUE;
}

static u8 sub(u32 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	long tmp = 0;
	u32 input = 0;

	if (ir_immediateAddressing(ir))
		input = (u32) ir_getOperand(ir);
	else
	{
		memory_setWordMode(m, WORD);
		if (!memory_MBR_read(m, ir_getOperand(ir)))
			return FALSE;

		input = m->mbr;
	}

	tmp = (long) *d0 - (long) input;

	*d0 = (u32) (tmp & 0xffffffff);

	ccr_reset(ccr);

	if (!tmp)
		ccr_setZ(ccr);
	else if (tmp < 0x0)
		ccr_setN(ccr);

	*pc += 3;

	return TRUE;
}

static u8 mul(u32 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	u64 tmp = 0;
	u32 input = 0;

	if (ir_immediateAddressing(ir))
		input = (u32) ir_getOperand(ir);
	else
	{
		memory_setWordMode(m, WORD);
		if (!memory_MBR_read(m, ir_getOperand(ir)))
			return FALSE;

		input = m->mbr;
	}

	tmp = *d0 * input;

	*d0 = (u32) (tmp & 0xffffffff);

	ccr_reset(ccr);

	if (tmp > 0xff)
		ccr_setV(ccr);

	*pc += 3;

	return TRUE;
}

static u8 div(u32 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	u16 tmp = 0;
	u32 input = 0;

	if (ir_immediateAddressing(ir))
		input = (u32) ir_getOperand(ir);
	else
	{
		memory_setWordMode(m, WORD);
		if (!memory_MBR_read(m, ir_getOperand(ir)))
			return FALSE;

		input = m->mbr;
	}

	tmp = *d0 / input;

	*d0 = (u32) (tmp & 0xffffffff);
	
	ccr_reset(ccr);

	if (tmp > 0xff)
		ccr_setV(ccr);

	*pc += 3;

	return TRUE;
}

static u8 cmp(u32 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	long tmp = 0;
	u32 input = 0;

	if (ir_immediateAddressing(ir))
		input = (u32) ir_getOperand(ir);
	else
	{
		memory_setWordMode(m, WORD);
		if (!memory_MBR_read(m, ir_getOperand(ir)))
			return FALSE;

		input = m->mbr;
	}

	tmp = (long) *d0 - (long) input;

	ccr_reset(ccr);

	if (!tmp)
		ccr_setZ(ccr);
	else if (tmp < 0x0)
		ccr_setN(ccr);

	*pc += 3;

	return TRUE;
}

static u8 dsp(u32 *d0, u16 *pc, ir_t *ir, ccr_t *ccr, memory_t *m)
{
	if (ir_immediateAddressing(ir))
		printf("%u\n", ir_getOperand(ir));
	else
	{
		memory_setWordMode(m, WORD);
		if (!memory_MBR_read(m, ir_getOperand(ir)))
			return FALSE;

		printf("%u\n", m->mbr);
	}

	*pc += 3;

	return TRUE;
}

u8 (*const opcodes[])(u32*, u16*, ir_t*, ccr_t*, memory_t*) = {
	stop, brz, brn, brc, brv, bra, lda, sta,
	add, sub, mul, div, cmp, dsp, (void*) 0x0, (void*) 0x0
};
