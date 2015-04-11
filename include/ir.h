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
 * @fn     ir_immediateAddressing(ir_t *ir)
 * @author Romain Failla
 * @brief  Tells if the addressing mode is immediate or not
 * @param  ir_t *ir : the reference to IR register
 * @return u8 : true if immidiate, false else
 */
u8 ir_immediateAddressing(ir_t *ir);

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
