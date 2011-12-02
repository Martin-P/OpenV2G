/*
 * Copyright (C) 2007-2011 Siemens AG
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
 * @version 2011-12-02 
 * @contact Joerg.Heuer@siemens.com
 *
 * <p>Code generated by EXIdizer</p>
 ********************************************************************/



#ifdef __cplusplus
extern "C" {
#endif

#include "EXITypes.h"

#ifndef BYTE_STREAM_H
#define BYTE_STREAM_H

int writeBytesToFile(uint8_t* data, uint32_t len, const char * filename);

int readBytesFromFile(const char * filename, uint8_t* data, uint32_t size, uint32_t pos);

#endif


#ifdef __cplusplus
}
#endif
