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
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************
 *
 * @author Sebastian.Kaebisch.EXT@siemens.com
 * @@version 0.7
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

#ifndef V2G_SERVER_H_
#define V2G_SERVER_H_

#include "EXITypes.h"

int testV2GService(uint8_t* inStream, uint16_t inStreamLength, uint8_t* outStream,uint32_t* outStreamLength);

#endif /* V2G_SERVER_H_ */
