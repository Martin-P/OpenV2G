
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
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************
 *
 * @author Sebastian.Kaebisch.EXT@siemens.com
 * @version 0.4
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DOIP_H_
#define DOIP_H_

/* generic DoIP header length */
#define DOIP_HEADER_LENGTH 8

/* define DoIP Version */
#define DOIP_VERSION 0x01
#define DOIP_VERSION_INV 0xFE

/* define DoIP payload types*/
#define DOIP_NEGATIVE_ACKNOWLEDGE 0x0000
#define DOIP_EXI_TYPE 0xC350 /* == 50000 */


/* Generic DoIP Header NACK codes */
#define DOIP_INCORRECT_PATTERN_FORMAT 0x00
#define DOIP_UNKNOWN_PAYLOAD_TYPE 0x01
#define DOIP_MESSAGE_TOO_LARGE 0x02
#define DOIP_OUT_OF_MEMORY 0x03
#define DOIP_INVALID_PAYLOAD_LENGTH 0x04

/* EXI NACK code */
#define DOIP_INVALID_EXI_MESSAGE 0x05


/* DoIP methods */
int write_doIPNack(uint8_t* outStream, uint16_t* outStreamLength, uint8_t nackCode);

int write_doIPHeader(uint8_t* outStream, uint16_t* outStreamLength, uint16_t payloadType);

int read_doIPHeader(uint8_t* inStream, uint16_t inStreamLength, uint16_t* payloadLength);

#endif /* DOIP_H_ */

#ifdef __cplusplus
}
#endif
