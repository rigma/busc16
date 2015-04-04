#include <stdlib.h>
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
		return NULL;

	// FREE IT !
	free(ir);
}

u8 ir_loadInstruction(ir_t *ir, u16 pc, memory_t *m)
{
	u8 *mar = NULL;

	if (ir == NULL || m == NULL)
		return FALSE;

	// Moving MAR position
	mar = m->mar;
	if (mar == memory_setMarPos(m, pc))
		return FALSE;

	// Copying the new instruction
	memcpy(ir, m->mar, sizeof(*ir));

	return TRUE;
}

u8 ir_getOpcode(ir_t *ir)
{
	// Returns the 5 low weight bits
	return (u8) (ir->opcode & 0x1f);
}

u16 ir_getOperand(ir_t *ir)
{
	return ir->operand;
}
