/*
 * Copyright (C) 2007-2014 Siemens AG
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
 * @version 0.9 
 * @contact Joerg.Heuer@siemens.com
 *
 * <p>Code generated by EXIdizer</p>
 * <p>Schema: V2G_CI_MsgDef.xsd</p>
 *
 *
 ********************************************************************/



#ifndef STRING_VALUE_TABLE_C
#define STRING_VALUE_TABLE_C

#include <string.h>

#include "StringValueTable.h"

#include "EXIConfig.h"
#include "ErrorCodes.h"
#include "EXIOptions.h"

#if MEMORY_ALLOCATION == DYNAMIC_ALLOCATION
#include "DynamicMemory.h"
#include <stdlib.h>
#endif /* DYNAMIC_ALLOCATION */

#define STRING_TABLE_INIT_VALUE_ENTRY_SIZE 16

int exiInitValueStrings(exi_value_table_t* valueTable) {
	int i;
	int errn = 0;

	valueTable->numberOfGlobalStrings = 0;
#if EXI_OPTION_VALUE_PARTITION_CAPACITY != 0
#if EXI_OPTION_VALUE_MAX_LENGTH != 0
	for(i=0; i<(valueTable->sizeLocalStrings); i++) {
		valueTable->numberOfLocalStrings[i] = 0;
	}
#endif /* EXI_OPTION_VALUE_MAX_LENGTH != 0 */
#endif /* EXI_OPTION_VALUE_PARTITION_CAPACITY != 0 */

	valueTable->valueStringTable->len = 0;

	return errn;
}


static int __exiAddStringValue(exi_value_table_t* valueTable,
		exi_string_t* sv, uint16_t qnameID) {
	int currLen;
	int errn;


#if MEMORY_ALLOCATION == DYNAMIC_ALLOCATION
	exi_value_string_table_entry_t* oldStrs;
	int i;
#endif /* DYNAMIC_ALLOCATION */

	errn = 0;
	currLen = valueTable->valueStringTable->len;

	if( valueTable->valueStringTable->size == currLen ) {
#if MEMORY_ALLOCATION == STATIC_ALLOCATION
		/* no memory left to handle this string */
		errn = EXI_ERROR_STRINGVALUES_OUT_OF_MEMORY;
#endif/* STATIC_ALLOCATION */
#if MEMORY_ALLOCATION == DYNAMIC_ALLOCATION
		/* expand entries */
		if (valueTable->valueStringTable->size == 0) {
			valueTable->valueStringTable->size  = STRING_TABLE_INIT_VALUE_ENTRY_SIZE;
		} else {
			valueTable->valueStringTable->size = (uint16_t)(currLen << 1); /* length * 2 */
		}

		/* old data */
		oldStrs = valueTable->valueStringTable->strs;
		valueTable->valueStringTable->strs = (exi_value_string_table_entry_t*) malloc(valueTable->valueStringTable->size * sizeof(exi_value_string_table_entry_t));

		if(currLen > 0) {
			/* copy old data */
			for(i=0; i<currLen; i++) {
				valueTable->valueStringTable->strs[i].localValueID =  oldStrs[i].localValueID;
				valueTable->valueStringTable->strs[i].qnameID =  oldStrs[i].qnameID;
				valueTable->valueStringTable->strs[i].str.size = oldStrs[i].str.size;
				valueTable->valueStringTable->strs[i].str.len =  oldStrs[i].str.len;
				valueTable->valueStringTable->strs[i].str.characters =  oldStrs[i].str.characters;
			}
			/*free old data */
			free(oldStrs);
		}
#endif /* DYNAMIC_ALLOCATION */
	}

	if (errn == 0) {
		valueTable->valueStringTable->strs[currLen].qnameID = qnameID;
		valueTable->valueStringTable->strs[currLen].localValueID = valueTable->numberOfLocalStrings[qnameID];


#if MEMORY_ALLOCATION == STATIC_ALLOCATION
		/* make sure the str length fits into existing buffer */
		if ( sv->len > valueTable->valueStringTable->strs[currLen].str.size ) {
			errn = EXI_ERROR_STRINGVALUES_OUT_OF_MEMORY;
		}
		/* set new length */
		valueTable->valueStringTable->strs[currLen].str.len = sv->len;
#endif/* STATIC_ALLOCATION */
#if MEMORY_ALLOCATION == DYNAMIC_ALLOCATION
		/* allocate codepoints memory */
		errn = exiAllocateDynamicStringMemory(&valueTable->valueStringTable->strs[currLen].str, sv->len);
		valueTable->valueStringTable->strs[currLen].str.len = sv->len;
#endif /* DYNAMIC_ALLOCATION */

		if(errn == 0) {
			/* copy codepoints */
			if ( memcpy(valueTable->valueStringTable->strs[currLen].str.characters, sv->characters, sv->len*sizeof(uint32_t)) == NULL ) {
				errn = EXI_ERROR_STRINGVALUES_OUT_OF_MEMORY;
			}

			valueTable->valueStringTable->len++;
		}
	}


	return errn;
}



int exiAddStringValue(exi_value_table_t* valueTable, exi_string_t* sv, uint16_t qnameID) {
	int errn = 0;
#if EXI_OPTION_VALUE_PARTITION_CAPACITY != 0
#if EXI_OPTION_VALUE_MAX_LENGTH != 0
	/* increment global string count */
#if EXI_OPTION_VALUE_PARTITION_CAPACITY < 0
	valueTable->numberOfGlobalStrings++;
#else /* EXI_OPTION_VALUE_PARTITION_CAPACITY < 0 */
	if (valueTable->numberOfGlobalStrings < EXI_OPTION_VALUE_PARTITION_CAPACITY) {
		valueTable->numberOfGlobalStrings++;
	}
#endif /* EXI_OPTION_VALUE_PARTITION_CAPACITY < 0 */
	/* increment local string count */
	if (qnameID < valueTable->sizeLocalStrings) {
#if MEMORY_ALLOCATION == DYNAMIC_ALLOCATION
		errn = __exiAddStringValue(valueTable, sv, qnameID);
#endif /* DYNAMIC_ALLOCATION */
		valueTable->numberOfLocalStrings[qnameID]++;
		/* printf("\tSV %d:  lv=%d  and gv=%d \n", qnameID, state->numberOfLocalStrings[qnameID], state->numberOfGlobalStrings);*/
	} else {
		/* currently we do support a set of qnames only */
		errn = EXI_ERROR_OUT_OF_QNAMES;
	}
#endif /* EXI_OPTION_VALUE_MAX_LENGTH != 0 */
#endif /* EXI_OPTION_VALUE_PARTITION_CAPACITY != 0 */

	return errn;
}




int exiGetNumberOfLocalStringValueEntries(exi_value_table_t* valueTable,
		uint16_t qnameID, uint16_t* numberOfEntries) {
	/* TODO number of local entries and next id must not match, e.g, if string-table is restricted in number of entries */
	int i;
	int errn = 0;
	*numberOfEntries = 0;
	for(i=0; i<valueTable->valueStringTable->len; i++) {
		if( valueTable->valueStringTable->strs[i].qnameID == qnameID ) {
			(*numberOfEntries)++;
		}
	}

	return errn;
}

int exiGetGlobalStringValue(exi_value_table_t* valueTable,
		uint16_t globalID, exi_string_t* sv) {
	int errn = 0;

	if( valueTable->valueStringTable->len > globalID) {
		*sv = valueTable->valueStringTable->strs[globalID].str;
	} else {
		errn = EXI_ERROR_STRINGVALUES_OUT_OF_BOUND;
	}
	return errn;
}

int exiGetLocalStringValue(exi_value_table_t* valueTable,
		uint16_t qnameID, uint16_t localID, exi_string_t* sv) {
	int i;
	int errn = EXI_ERROR_STRINGVALUES_OUT_OF_BOUND;

	/* walk over all entries. Note that if number of entries is restricted the local ID may be larger than the number of global entries */
	for(i=0; i<valueTable->valueStringTable->len && errn != 0; i++) {
		if( valueTable->valueStringTable->strs[i].qnameID == qnameID && valueTable->valueStringTable->strs[i].localValueID == localID  ) {
			*sv = valueTable->valueStringTable->strs[i].str;
			errn = 0;
		}
	}

	return errn;
}


#endif

