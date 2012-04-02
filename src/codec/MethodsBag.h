/*
 * Copyright (C) 2007-2012 Siemens AG
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
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************
 *
 * @author Daniel.Peintner.EXT@siemens.com
 * @version 0.6 
 * @contact Joerg.Heuer@siemens.com
 *
 * <p>Code generated by EXIdizer</p>
 ********************************************************************/



#ifndef METHODS_BAG_H
#define METHODS_BAG_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/**
 * Returns the number of bits to identify the characteristics.
 *
 * @param characteristics
 * @param codingLength (return value)
 *
 */
int exiGetCodingLength(uint32_t characteristics, uint16_t* codingLength);

/**
 * Returns the least number of 7 bit-blocks that is needed to represent the
 * int <param>n</param>. Returns 1 if <param>n</param> is 0.
 *
 * @param n
 *            integer value
 *
 */
uint8_t numberOf7BitBlocksToRepresent(uint32_t n);


#endif
