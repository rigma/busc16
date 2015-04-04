#ifndef OPCODE_H
#define OPCODE_H

#include "ccr.h"
#include "config.h"

extern u8 (* const opcodes[]) (u8 *d0, u8 input, ccr_t *ccr);

#endif
