/*
 * Copyright (C) 2007-2013 Siemens AG
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
 * @author Sebastian.Kaebisch@siemens.com
 * @version 0.8
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef V2GSERVER_H_
#define V2GSERVER_H_

#include "v2g_dataTypes.h"


/** 
 * \brief Init the v2g service data structure
 * \param	service   struct EXIService* Service data structure
 * \param	bytes   bytes_t setted up byte data structure
 * \param	string_ucs_t   setted up string data structure
 * \param	transportHeaderOffset uint16_t Transport protocol offset
 * \return  0 = 0K; -1 = ERROR
 */
int init_v2gservice(struct EXIService* service, exi_bytes_t service_bytes, exi_string_ucs_t service_string, uint16_t transportHeaderOffset);

/** 
 * \brief Takes the EXI stream, invokes the called service method, and provides the response EXI stream
 * \param	service   struct EXIService* Represent the service data structure
 * \param	inStream   uint8_t* EXI in stream
 * \param	sizeInStream   uint16_t Length of the inStream
 * \param	outStream   uint8_t* Represent the out stream
 * \param	sizeOutStream   uint16_t Size of the out stream
 * \param	outStreamLength   uint16_t* Length of the stream
 * \return  0 = 0K; -1 = ERROR
 */
int messageDispatcher(struct EXIService* service, uint8_t* inStream, uint16_t sizeInStream, uint8_t* outStream, uint16_t sizeOutStream, uint16_t* outStreamLength);

#endif /* V2GSERVER_H_ */

#ifdef __cplusplus
}
#endif
