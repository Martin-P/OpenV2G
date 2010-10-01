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
 * @version 0.2
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

#ifndef STRING_TABLE_ENTRIES_H
#define STRING_TABLE_ENTRIES_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/* ==================================== */
/* String Table Structures */

struct exiPartition {
	/* length of array */
	size_t len;
	/* array of string entries */
	const char** entries;
};

struct exiStringTable {
	/* length of both arrays (uris & localNames) */
	size_t len;
	/* URI entries*/
	const char** uris;
	/* localName entries divided by URI */
	struct exiPartition * localNames;
};


/* ==================================== */
/* String Table Population */

extern struct exiStringTable stringTable;

#endif

