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

#ifndef OPCODE_H
#define OPCODE_H

#include "ccr.h"
#include "config.h"
#include "ir.h"
#include "memory.h"

extern u8 (* const opcodes[]) (u8*, u16*, ir_t*, ccr_t*, memory_t*);

#endif
