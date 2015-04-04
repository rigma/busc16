#ifndef IR_H
#define IR_H

#include "config.h"
#include "memory.h"

/**
 * @struct ir_t
 * @author Romain Failla
 * @brief  Symbolize the IR register.
 *		   The OPCODE is written on 1 byte (only 5 bits are used).
 *		   The OPEREAND is written on 2 bytes (all bits are used).
 */
typedef struct {
	u8  opcode;
	u16 operand;
} ir_t;

/**
 * @fn     ir_init()
 * @author Romain Failla
 * @brief  Initialize a new IR register
 * @return ir_t* : the reference of the register
 */
ir_t *ir_init();

/**
 * @fn     ir_free(ir_t *ir)
 * @author Romain Failla
 * @brief  Free an IR register
 * @param  ir_t *ri : the reference of the IR register to free
 */
void ir_free(ir_t *ir);

/**
 * @fn     ir_loadInstruction(ir_t *ir, u16 pc, memory_t *m)
 * @author Romain Failla
 * @brief  Load an instruction (OPCODE and OPERAND) in IR register
 * @param  ir_t *ir : the reference to the destination
 * @param  u16 pc : the address to load
 * @param  memory_t *m : the reference to the memory
 * @return u8 : returns TRUE if success, else FALSE
 */
u8 ir_loadInstruction(ir_t *ir, u16 pc, memory_t *m);

/**
 * @fn     ir_getOpcode(ir_t *ir)
 * @author Romain Failla
 * @brief  Get the OPCODE stored in IR register
 * @param  ir_t *ir : the reference to IR register
 * @return u8 : the OPCODE
 */
u8 ir_getOpcode(ir_t *ir);

/**
 * @fn     ir_getOperand(ir_t *ir)
 * @author Romain Failla
 * @brief  Get the OPERAND stored in IR register
 * @param  ir_t *ir : the reference to IR register
 * @return u16 : the OPERAND
 */
u16 ir_getOperand(ir_t *ir);

#endif
