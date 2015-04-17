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

#include <ir.h>

ir_t *ir_init()
{
	// Trying to allocate the register
	ir_t *ir = (ir_t*) malloc(sizeof(ir_t));
	if (ir == NULL)
		return NULL;

	// Reset ir->opcode and ir->operand
	ir->opcode = (u8) 0x0;
	ir->operand = (u16) 0x0;

	return ir;
}

void ir_free(ir_t *ir)
{
	if (ir == NULL)
		return;

	// FREE IT !
	free(ir);
}

u8 ir_loadInstruction(ir_t *ir, u16 pc, memory_t *m)
{
	if (ir == NULL || m == NULL)
		return FALSE;

	memory_setWordMode(m, BYTE);

	// Loading the opcode in the register
	memory_MAR_read(m, pc);

	ir->opcode = (u8) m->mar & 0x000000ff;

	// Loading the operand in the register
	memory_MAR_read(m, ++pc);

	ir->operand = (u16) ((m->mar << 8) & 0x0000ff00);

	memory_MAR_read(m, ++pc);

	ir->operand |= (u16) (m->mar & 0x000000ff);

	return TRUE;
}

u8 ir_immediateAddressing(ir_t *ir)
{
	if (ir == NULL)
		return FALSE;

	return (ir->opcode & 0x10) ? TRUE : FALSE;
}

u8 ir_getOpcode(ir_t *ir)
{
	if (ir == NULL)
		return FALSE;

	// Returns the 4 low weight bits
	return (u8) (ir->opcode & 0x0f);
}

u16 ir_getOperand(ir_t *ir)
{
	if (ir == NULL)
		return FALSE;

	return ir->operand;
}
