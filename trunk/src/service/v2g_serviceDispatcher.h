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
 * @author Sebastian.Kaebisch.EXT@siemens.com
 * @version 0.2
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef V2GSERVER_H_
#define V2GSERVER_H_

#include "v2g_serviceDataTypes.h"


int init_v2gservice(struct v2gService* service,bytes_t bytes, string_ucs_t string);
int messageDispatcher(struct v2gService* service, uint8_t* inStream, size_t sizeInStream, size_t* inPos, uint8_t* outStream, size_t sizeOutStream, size_t* outPos);

#endif /* V2GSERVER_H_ */

#ifdef __cplusplus
}
#endif
