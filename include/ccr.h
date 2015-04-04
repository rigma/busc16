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

#ifndef CCR_H
#define CCR_H

#include "config.h"

typedef unsigned char ccr_t;

ccr_t ccr_init();

u8 ccr_Z(ccr_t *ccr);
void ccr_setZ(ccr_t *ccr, u8 value);

u8 ccr_N(ccr_t *ccr);
void ccr_setN(ccr_t *ccr, u8 value);

u8 ccr_C(ccr_t *ccr);
void ccr_setC(ccr_t *ccr, u8 value);

u8 ccr_V(ccr_t *ccr);
void ccr_setV(ccr_t *ccr, u8 value);

#endif
