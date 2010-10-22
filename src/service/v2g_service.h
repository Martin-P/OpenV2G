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

#ifndef V2G_SERVICE_H_
#define V2G_SERVICE_H_

#include "v2g_serviceDataTypes.h"
#include "EXITypes.h"

struct uniqueIDPath
{
	int id[10];
	size_t pos;
};


struct v2gService
{
	/* in-/ out-stream */
	bitstream_t inStream;
	bitstream_t outStream;

	/* EXI */
	exi_state_t stateDecode;
	exi_state_t stateEncode;
	exi_event_t event;
	eqname_t eqn;
	exi_value_t val;

	/* v2g message data structure */
	struct AnonType_V2G_Message v2gMsg;

	/* unique id for ambiguous elements */
	struct uniqueIDPath idPath;
};



#endif /* V2G_SERVICE_H_ */

#ifdef __cplusplus
}
#endif
