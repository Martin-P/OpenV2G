/*
 * Copyright (C) 2007-2010 Siemens AG
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************
 *
 * @author Daniel.Peintner.EXT@siemens.com
 * @version 0.1
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

#ifndef EXI_CODER_C
#define EXI_CODER_C

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "EXITypes.h"
#include "BitInputStream.h"
#include "BitDecoderChannel.h"

#include "assert.h"
#include "EXICoder.h"
#include "EXIHeader.h"

/*
 size_t exiGetCurrentState(struct exiState* state) {
 return state->grammarStates[state->currentStack];
 // return 0;
 }
 */

int exiPushStack(exi_state_t* state, size_t newState, eqname_t* eqn) {
	if ((state->stackIndex + 1) < EXI_ELEMENT_STACK_SIZE) {
		state->grammarStack[++state->stackIndex] = newState;
		/* copy qname */
		state->elementStack[state->stackIndex].localPart = eqn->localPart;
		state->elementStack[state->stackIndex].namespaceURI = eqn->namespaceURI;
		return 0;
	} else {
		return EXI_ERROR_OUT_OF_BOUNDS;
	}
}

int exiPopStack(exi_state_t* state) {
	if (state->stackIndex >= 1) {
		state->stackIndex--;
		return 0;
	} else {
		return EXI_ERROR_OUT_OF_BOUNDS;
	}
}

#endif

